#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_KKKVS_print(JNIEnv *env, jobject obj)
{
    printf("Hello World!\n");
    return;
}