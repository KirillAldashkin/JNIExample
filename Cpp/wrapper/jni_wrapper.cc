#include <memory>

#include "jni.h"

#include "library/sieve.h"

static_assert(sizeof(void*) <= sizeof(jlong), 
              "Can't fit pointer into Java's \"long\" type");

// java wrapper functions
static jlong CreateSieve(JNIEnv* env, jobject obj, jlong size) {
  auto ptr = new mylib::Sieve(static_cast<jlong>(size));
  return reinterpret_cast<jlong>(ptr);
}

static void DestroySieve(JNIEnv* env, jobject obj, jlong sieve) {
  auto ptr = reinterpret_cast<mylib::Sieve*>(sieve);
  delete ptr;
}

static jlong GetSize(JNIEnv* env, jobject obj, jlong sieve) {
  auto ptr = reinterpret_cast<mylib::Sieve*>(sieve);
  return static_cast<jlong>(ptr->size());
}

static jboolean GetIsPrime(JNIEnv* env, jobject obj, jlong sieve, jlong at) {
  auto ptr = reinterpret_cast<mylib::Sieve*>(sieve);
  bool ret = ptr->operator[](static_cast<std::size_t>(at));
  return static_cast<jboolean>(ret);
}

// Java export table
static JNINativeMethod exports[] = {
	{ "CreateSieve", "(J)J", reinterpret_cast<void*>(&CreateSieve) },
	{ "DestroySieve", "(J)V", reinterpret_cast<void*>(&DestroySieve) },
	{ "GetSize", "(J)J", reinterpret_cast<void*>(&GetSize) },
	{ "GetIsPrime", "(JJ)Z", reinterpret_cast<void*>(&GetIsPrime) }
};

// Class where 'native' functions are defined
constexpr const char* kJavaClassName = "Sieve";

// Java Runtime helpers
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv* env;

  // 1. Resolve JVM interface
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_8) != JNI_OK)
		return -1;

  // 2. Find Java side of this library
	jclass clazz = env->FindClass(kJavaClassName);
	if (clazz == nullptr) return -1;

  // 3. Bind our impletementations to that class
	jint res = env->RegisterNatives(clazz, exports, sizeof(exports) / sizeof(*exports));
	if (res != 0) return -1;

	return JNI_VERSION_1_8;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
	JNIEnv* env;

  // 1. Resolve JVM interface
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_8) != JNI_OK)
		return;
 
  // 2. Find Java side of this library
	jclass clazz = env->FindClass(kJavaClassName);
	if (clazz == nullptr) return;

  // 3. Unbind our impletementations from that class
	env->UnregisterNatives(clazz);
}