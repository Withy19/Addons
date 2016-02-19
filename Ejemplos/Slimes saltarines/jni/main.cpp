#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>

#include "Substrate.h"

#define LOG_TAG "withy"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

static int (*Slime$getDelayJump_real)(); //Funcion estatica de tipo int ya que queremos un valor en enteros 
static int Slime$getDelayJump_hook(){ 
	return 1; //Retornamos el tiempo en valor ENTERO (int) del delay de salto del slime, de esta manera brincaran como si no hubiese un mañana
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {

	void* Slime$getDelayJump = dlsym(RTLD_DEFAULT, "_ZN5Slime12getJumpDelayEv");	//Simbolo de la funcion
	MSHookFunction(Slime$getDelayJump, (void*) &Slime$getDelayJump_hook, (void**) &Slime$getDelayJump_real);	//Uso de substrate

	return JNI_VERSION_1_2;
}