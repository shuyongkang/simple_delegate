#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "my_implementation.h"
#include "my_types.h"



namespace tflite {
namespace my {
void *LoadFunction(void *handle, const char *name, bool optional) {
//   TFLITE_DCHECK(handle != nullptr);
  void *fn = dlsym(handle, name);
  if (fn == nullptr && !optional) {
    // TFLITE_LOG_PROD(tflite::TFLITE_LOG_ERROR, "Function %s is NULL", name);
    std::cout<<"Function "<<name<<" is NULL"<<std::endl;
  }
  return fn;
}

#define LOAD_FUNCTION(handle, name)                                            \
  my_api.name = reinterpret_cast<name##_fn>(                              \
      LoadFunction(handle, #name, /*optional*/ false));

#define LOAD_FUNCTION_OPTIONAL(handle, name)                                   \
  my_api.name = reinterpret_cast<name##_fn>(                               \
      LoadFunction(handle, #name, /*optional*/ true));

const MyApi LoadMyApi() {
  MyApi my_api = {};

  // temporary library path, may change
  static const char my_library_name[] = "libcompute.so";
  void *libmy = dlopen(my_library_name, RTLD_LAZY | RTLD_LOCAL);
  if (libmy == nullptr){
    std::cout<<"dlopen -error- \n"<<dlerror()<<std::endl; 
    return my_api;
  }

  my_api.my_exists = true;
  LOAD_FUNCTION(libmy, compute);
  return my_api;
}

const MyApi *MyApiImplementation() {
  static const MyApi my_api = LoadMyApi();
  return &my_api;
}
} // namespace my
} // namespace tflite