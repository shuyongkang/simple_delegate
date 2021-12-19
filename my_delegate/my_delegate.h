#ifndef TENSORFLOW_LITE_MANASI_DELEGATE_H_
#define TENSORFLOW_LITE_MANASI_DELEGATE_H_

#include <memory>
#include "tensorflow/lite/c/common.h"

#ifdef __cpluscplus
extern "C" {
#endif

typedef struct {
  int debug_level;
} MyDelegateOptions;


TfLiteDelegate *
TfLiteMyDelegateCreate(const MyDelegateOptions *options);

void TfLiteMyDelegateDelete(TfLiteDelegate *delegate);

#ifdef __cpluscplus
}
#endif

// A convenient wrapper that returns C++ std::unique_ptr for automatic memory
// management.
inline std::unique_ptr<TfLiteDelegate, void (*)(TfLiteDelegate*)>
TfLiteMyDelegateCreateUnique(const MyDelegateOptions* options) {
  return std::unique_ptr<TfLiteDelegate, void (*)(TfLiteDelegate*)>(
      TfLiteMyDelegateCreate(options), TfLiteMyDelegateDelete);
}

#endif // TENSORFLOW_LITE_MANASI_DELEGATE_H_