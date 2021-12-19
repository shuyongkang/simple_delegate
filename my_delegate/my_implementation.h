#ifndef TENSORFLOW_LITE_MANASI_IMPLEMENTATION_H_
#define TENSORFLOW_LITE_MANASI_IMPLEMENTATION_H_

#include "tensorflow/lite/model.h"

namespace tflite
{
  namespace my
  {
    struct MyApi
    {
      bool my_exists ;
      int sdk_version;

      int (*compute)(); 
    };

    const MyApi *MyApiImplementation();
  } // namespace my
} // namespace tflite
#endif // TENSORFLOW_LITE_MANASI_IMPLEMENTATION_H_
