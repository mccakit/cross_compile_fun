module;
#include <jni.h>
#include <android/log.h>
#include <string_view>
export module bt;
import std;
import nlohmann.json;
using json = nlohmann::json;

export namespace bt
{
    constexpr std::string_view bt_module {"BT_MODULE"};
    JNIEnv* jni_env {};
    jobject bt_instance {};
    jclass bt_class_global {};

    void info(const std::string_view tag, const std::string_view message)
    {
        __android_log_print(ANDROID_LOG_INFO, tag.data(), "%s", message.data());
    }

    void error(const std::string_view tag, const std::string_view message)
    {
        __android_log_print(ANDROID_LOG_ERROR, tag.data(), "%s", message.data());
    }
    std::string_view clear_exception()
    {
        jni_env->ExceptionDescribe();
        jni_env->ExceptionClear();
        return "{\"error\": \"Exception in Java method\"}";
    }

    void init(JNIEnv* env, jobject activity)
    {
        jni_env = env;
        jclass local_bt_class = jni_env->FindClass("org/mccakit/app/Bt");
        bt_class_global = (jclass)jni_env->NewGlobalRef(local_bt_class);
        jmethodID get_instance_method = jni_env->GetStaticMethodID(local_bt_class, "getInstance", "(Landroid/content/Context;)Lorg/mccakit/app/Bt;");
        jobject instance = jni_env->CallStaticObjectMethod(local_bt_class, get_instance_method, activity);
        bt_instance = jni_env->NewGlobalRef(instance);
        jni_env->DeleteLocalRef(local_bt_class);
        jni_env->DeleteLocalRef(instance);
        info(bt_module, "Bluetooth module initialized");
    }

    json get_paired_devices()
    {
        jmethodID get_paired_method = jni_env->GetMethodID(bt_class_global, "getPairedDevices", "()Ljava/lang/String;");
        jstring jni_out_jstr = (jstring)jni_env->CallObjectMethod(bt_instance, get_paired_method);
        if(jni_env->ExceptionCheck())
        {
            return json::parse(clear_exception());
        }
        const char* jni_out_chr {jni_env->GetStringUTFChars(jni_out_jstr, nullptr)};
        std::string jni_out_str{jni_out_chr};
        jni_env->ReleaseStringUTFChars(jni_out_jstr, jni_out_chr);
        jni_env->DeleteLocalRef(jni_out_jstr); // Also good practice to delete this local ref
        info(bt_module, "Successfully retrieved paired devices");
        json result {json::parse(jni_out_str)};
        return result[0]["devices"];
    }
    bool connect(const std::string& mac_address)
    {
        jmethodID connect_method = jni_env->GetMethodID(bt_class_global, "connectToDevice", "(Ljava/lang/String;)Z");
        jstring jni_mac = jni_env->NewStringUTF(mac_address.c_str());
        jboolean result = jni_env->CallBooleanMethod(bt_instance, connect_method, jni_mac);
        jni_env->DeleteLocalRef(jni_mac);
        if(jni_env->ExceptionCheck())
        {
            clear_exception();
            return false;
        }
        if(result)
        {
            info(bt_module, std::string("Successfully connected to device: ") + mac_address);
        }
        else
        {
            error(bt_module, std::string("Failed to connect to device: ") + mac_address);
        }

        return result;
    }
    void disconnect()
    {
        jmethodID disconnect_method = jni_env->GetMethodID(bt_class_global, "disconnect", "()V");
        jni_env->CallVoidMethod(bt_instance, disconnect_method);
        if(jni_env->ExceptionCheck())
        {
            clear_exception();
        }
        else
        {
            info(bt_module, "Disconnected from device");
        }
    }
    bool is_connected()
    {
        jmethodID is_connected_method = jni_env->GetMethodID(bt_class_global, "isConnected", "()Z");
        jboolean result = jni_env->CallBooleanMethod(bt_instance, is_connected_method);
        if(jni_env->ExceptionCheck())
        {
            clear_exception();
            return false;
        }
        return result;
    }
    std::string buffer()
    {
        jmethodID read_buffer_method = jni_env->GetMethodID(bt_class_global, "readBuffer", "()Ljava/lang/String;");
        jstring jni_out_jstr = (jstring)jni_env->CallObjectMethod(bt_instance, read_buffer_method);

        if(jni_env->ExceptionCheck())
        {
            clear_exception();
            return "";
        }

        if(jni_out_jstr == nullptr)
        {
            return "";
        }

        const char* jni_out_chr = jni_env->GetStringUTFChars(jni_out_jstr, nullptr);
        std::string result{jni_out_chr};
        jni_env->ReleaseStringUTFChars(jni_out_jstr, jni_out_chr);
        jni_env->DeleteLocalRef(jni_out_jstr);

        if(!result.empty())
        {
            info(bt_module, "Read " + std::to_string(result.size()) + " bytes from buffer");
        }

        return result;
    }
}
