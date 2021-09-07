#include "jni_tmain.h"
#include <iostream>

JNIEXPORT void JNICALL Java_jni_tmain_no_1args_1return(JNIEnv *, jobject) {
  std::cout << "Java_jni_tmain_no_1args_1return\n";
}
