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
    void info(const std::string_view tag, const std::string_view message)
    {
        __android_log_print(ANDROID_LOG_INFO, tag.data(), "%s", message.data());
    }
    void error(const std::string_view  tag, const std::string_view message)
    {
        __android_log_print(ANDROID_LOG_ERROR, tag.data(), "%s", message.data());
    }
    std::string_view clear_exception(JNIEnv* jni_env, jclass bt_class)
    {
        jni_env->ExceptionDescribe();
        jni_env->ExceptionClear();
        jni_env->DeleteLocalRef(bt_class);
        return "{\"error\": \"Exception in Java method\"}";
    }
    void init(JNIEnv* env, jobject activity)
    {
        jni_env = env;
        // Find the Bt class and create instance
        jclass bt_class = jni_env->FindClass("org/mccakit/app/Bt");
        jmethodID get_instance_method = jni_env->GetStaticMethodID(bt_class, "getInstance", "(Landroid/content/Context;)Lorg/mccakit/app/Bt;");
        jobject instance = jni_env->CallStaticObjectMethod(bt_class, get_instance_method, activity);
        // Store global reference
        bt_instance = jni_env->NewGlobalRef(instance);
        jni_env->DeleteLocalRef(bt_class);
        jni_env->DeleteLocalRef(instance);
        info(bt_module, "Bluetooth module initialized");
    }
    json get_paired_devices()
    {
        jclass bt_class = jni_env->FindClass("org/mccakit/app/Bt");
        // Get the method ID for getPairedDevices
        jmethodID get_paired_method = jni_env->GetMethodID(bt_class, "getPairedDevices", "()Ljava/lang/String;");
        jstring jni_out_jstr = (jstring)jni_env->CallObjectMethod(bt_instance, get_paired_method);
        if(jni_env->ExceptionCheck())
        {
            clear_exception(jni_env, bt_class);
        }
        const char* jni_out_chr {jni_env->GetStringUTFChars(jni_out_jstr, nullptr)};
        std::string jni_out_str{jni_out_chr};
        jni_env->ReleaseStringUTFChars(jni_out_jstr, jni_out_chr);
        jni_env->DeleteLocalRef(bt_class);
        info(bt_module, "Successfully retrieved paired devices");
        json result {json::parse(jni_out_str)};
        return result[0]["devices"];
    }
}
