plugins {
    id("com.android.application")
}

android {
    namespace = "org.libsdl.app"
    compileSdk = 36
    ndkVersion = "29.0.13599879"
    defaultConfig {
        applicationId = "org.mccakit.imgui_sample"
        minSdk = 30
        targetSdk = 36
        versionCode = 1
        versionName = "1.0"
        ndk {
            abiFilters += listOf("arm64-v8a")
        }
    }

    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android.txt"), "proguard-rules.pro")
        }
    }
    sourceSets {
        getByName("main") {
            jniLibs.srcDirs("../../build/apps")
        }
    }

    lint {
        abortOnError = false
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
}
