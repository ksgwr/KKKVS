#include "kkkvs/value_index.hpp"

#include <jni.h>
#include <stdio.h>
#include <string>
#include <vector>

class JValueIndex : public kkkvs::ValueIndex {
public:

    jint add(JNIEnv *env, jstring dataj) {
        const char *data = env->GetStringUTFChars(dataj, NULL);
        if (data == NULL) return -1;
        byte* buf = (byte*)data;
        std::vector<byte> byteData(buf, buf + strlen(data));

        int ret = kkkvs::ValueIndex::add(byteData);

        env->ReleaseStringUTFChars(dataj, data);

        return (jint)ret;
    }

    jstring get(JNIEnv *env, jint ij) {
        int i = (int) ij;
        std::vector<byte> byteData = kkkvs::ValueIndex::get(i);
        return env->NewStringUTF(reinterpret_cast<char*>(byteData.data()));
    }

    static JValueIndex* getInstance(JNIEnv *env, jobject obj) {
        const jclass classj = env->GetObjectClass(obj);
        const jfieldID mHandleFieldID = env->GetFieldID(classj, "mHandle", "J");
        return reinterpret_cast<JValueIndex*>(env->GetLongField(obj, mHandleFieldID));
    }
};

//#ifdef ___cplusplus
extern "C" {
//#endif

JNIEXPORT jlong JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_init(JNIEnv *env, jobject obj)
{
    return reinterpret_cast<jlong>(new JValueIndex());
}

JNIEXPORT jint JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_add(JNIEnv *env, jobject obj, jstring data)
{
    return JValueIndex::getInstance(env, obj)->add(env, data);
}

JNIEXPORT jstring JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_get(JNIEnv *env, jobject obj, jint i)
{
    return JValueIndex::getInstance(env, obj)->get(env, i);
}

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_print(JNIEnv *env, jobject obj)
{
    printf("Hello World! Fuga\n");
    return;
}

//#ifdef ___cplusplus
}
//#endif