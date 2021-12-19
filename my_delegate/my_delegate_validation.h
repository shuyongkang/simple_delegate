#ifndef TENSORFLOW_LITE_MANASI_DELEGATE_VALIDATION_H_
#define TENSORFLOW_LITE_MANASI_DELEGATE_VALIDATION_H_

#include "tensorflow/lite/c/common.h"

namespace tflite {
namespace my {
bool Validate(const TfLiteRegistration *registration, const TfLiteNode *node,
              TfLiteContext *context);
} // namespace my
} // namespace tflite
#endif // TENSORFLOW_LITE_MANASI_DELEGATE_VALIDATION_H_