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

    jint add(JNIEnv *env, jbyteArray dataj) {
        jsize lenj = env->GetArrayLength(dataj);
        jbyte *elements = env->GetByteArrayElements(dataj, NULL);
        if (elements == NULL) return -1;
        std::vector<byte> byteData(elements, elements + (int)lenj);

        int ret = kkkvs::ValueIndex::add(byteData);

        env->ReleaseByteArrayElements(dataj, elements, 0);

        return (jint)ret;
    }

    void put(JNIEnv *env, jint ij, jstring dataj) {
        int i = (int) ij;
        const char *data = env->GetStringUTFChars(dataj, NULL);
        if (data == NULL) return;
        byte* buf = (byte*)data;
        std::vector<byte> byteData(buf, buf + strlen(data));

        kkkvs::ValueIndex::put(i, byteData);

        env->ReleaseStringUTFChars(dataj, data);
    }

    jboolean exists(JNIEnv *env, jint ij) {
        int i = (int) ij;

        bool ret = kkkvs::ValueIndex::exists(i);

        return (jboolean) ret;
    }

    jstring get(JNIEnv *env, jint ij) {
        int i = (int) ij;
        std::vector<byte> byteData = kkkvs::ValueIndex::get(i);
        return env->NewStringUTF(reinterpret_cast<char*>(byteData.data()));
    }

    jbyteArray getAsBytes(JNIEnv *env, jint ij) {
        int i = (int) ij;
        
        std::vector<byte> byteData = kkkvs::ValueIndex::get(i);

        jbyteArray ret = env->NewByteArray(byteData.size());
        jbyte* b = env->GetByteArrayElements(ret, 0);
        for (int i = 0; i < byteData.size(); i++) {
            b[i] = (jbyte) byteData.at(i);
        }

        env->ReleaseByteArrayElements(ret, b, 0);

        return ret;
    }

    void remove(JNIEnv *env, jint ij, jboolean hardj) {
        int i = (int) ij;
        bool hard = (bool) hardj;

        kkkvs::ValueIndex::remove(i, hard);
    }

    void remove(JNIEnv *env, jint ij) {
        int i = (int) ij;

        kkkvs::ValueIndex::remove(i);
    }

    jint getUncheckedRemovedIndex(JNIEnv *env) {
        int ret = kkkvs::ValueIndex::getUncheckedRemovedIndex();

        return (jint) ret;
    }

    void checkRemovedIndex(JNIEnv *env, jint ij) {
        int i = (int) ij;

        kkkvs::ValueIndex::checkRemovedIndex(i);
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

JNIEXPORT jint JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_add2(JNIEnv *env, jobject obj, jbyteArray data)
{
    return JValueIndex::getInstance(env, obj)->add(env, data);
}

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_put(JNIEnv *env, jobject obj, jint i, jstring data)
{
    JValueIndex::getInstance(env, obj)->put(env, i, data);
}

JNIEXPORT jboolean JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_exists(JNIEnv *env, jobject obj, jint i)
{
    return JValueIndex::getInstance(env, obj)->exists(env, i);
}

JNIEXPORT jstring JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_get(JNIEnv *env, jobject obj, jint i)
{
    return JValueIndex::getInstance(env, obj)->get(env, i);
}

JNIEXPORT jbyteArray JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_getAsBytes(JNIEnv *env, jobject obj, jint i)
{
    return JValueIndex::getInstance(env, obj)->getAsBytes(env, i);
}

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_remove(JNIEnv *env, jobject obj, jint i, jboolean hard)
{
    JValueIndex::getInstance(env, obj)->remove(env, i, hard);
}

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_remove2(JNIEnv *env, jobject obj, jint i)
{
    JValueIndex::getInstance(env, obj)->remove(env, i);
}

JNIEXPORT jint JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_getUncheckedRemovedIndex(JNIEnv *env, jobject obj)
{
    return JValueIndex::getInstance(env, obj)->getUncheckedRemovedIndex(env);
}

JNIEXPORT void JNICALL
Java_jp_ksgwr_kkkvs_ValueIndex_checkRemovedIndex(JNIEnv *env, jobject obj, jint i)
{
    return JValueIndex::getInstance(env, obj)->checkRemovedIndex(env, i);
}

//#ifdef ___cplusplus
}
//#endif