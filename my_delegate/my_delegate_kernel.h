#ifndef TENSORFLOW_LITE_MANASI_DELEGATE_KERNEL_H_
#define TENSORFLOW_LITE_MANASI_DELEGATE_KERNEL_H_

// #include "my/builder/op_builder.h"
#include "my_delegate/my_delegate.h"
#include "my_delegate/my_implementation.h"
#include "tensorflow/lite/delegates/utils/simple_delegate.h"
#include <memory>
#include <vector>

namespace tflite {
namespace my {

class MyDelegateKernel : public SimpleDelegateKernelInterface {
public:
  explicit MyDelegateKernel(const MyDelegateOptions &options)
      : options_(options) {}
  
  TfLiteStatus Init(TfLiteContext *context,
                    const TfLiteDelegateParams *params) override;
  
  TfLiteStatus Prepare(TfLiteContext *context, TfLiteNode *node) override;
  
  TfLiteStatus Eval(TfLiteContext *context, TfLiteNode *node) override;

  ~MyDelegateKernel() override;

private:
  
  TfLiteStatus BuildGraph(TfLiteContext *context,
                          const TfLiteIntArray *input_tensors,
                          const TfLiteIntArray *output_tensors);
  MyDelegateOptions options_;    //
  const MyApi *my_api_;     //
   std::vector<int> nodes_;   //


};

} // namespace my
} // namespace tflite

#endif // TENSORFLOW_LITE_MANASI_DELEGATE_KERNEL_H_