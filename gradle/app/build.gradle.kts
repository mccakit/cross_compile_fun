plugins {
    id("com.android.application")
}

android {
    namespace = "org.libsdl.app"
    compileSdk = 35

    defaultConfig {
        minSdk = 21
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        externalNativeBuild {
            cmake {
                arguments += listOf("-DANDROID_PLATFORM=android-21", "-DANDROID_STL=c++_static")
                abiFilters += listOf("arm64-v8a")
            }
        }
    }

    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android.txt"), "proguard-rules.pro")
        }
    }

    applicationVariants.all {
        val variantNameCapitalized = name.replaceFirstChar { if (it.isLowerCase()) it.titlecase() else it.toString() }
        tasks.named("merge${variantNameCapitalized}Assets") {
            dependsOn("externalNativeBuild${variantNameCapitalized}")
        }
    }

    if (!project.hasProperty("EXCLUDE_NATIVE_LIBS")) {
        sourceSets["main"].jniLibs.srcDir("libs")
        externalNativeBuild {
            cmake {
                path = file("../../CMakeLists.txt")
                version = "4.0.2"
            }
        }
    }

    lint {
        abortOnError = false
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
}
