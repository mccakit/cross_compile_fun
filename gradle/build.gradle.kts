buildscript {
    repositories {
        mavenCentral()
        google()
    }
    dependencies {
        classpath("com.android.tools.build:gradle:8.9.0")
    }
}
allprojects {
    repositories {
        mavenCentral()
        google()
    }
}
tasks.register<Delete>("clean") {
    delete(rootProject.layout.buildDirectory)
}
tasks.wrapper {
    gradleVersion = "8.11.1"
}