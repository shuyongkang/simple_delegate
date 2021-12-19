#include "my_delegate/my_delegate.h"
#include "my_delegate/my_delegate_kernel.h"
#include "my_delegate/my_delegate_validation.h"
#include "tensorflow/lite/delegates/utils/simple_delegate.h"
#include <iostream>
#include <memory>

namespace tflite
{
  namespace my
  {

    class MyDelegate : public SimpleDelegateInterface
    {
    public:
      explicit MyDelegate(const MyDelegateOptions *options)
          : options_(*options) {}

      bool IsNodeSupportedByDelegate(const TfLiteRegistration *registration,
                                     const TfLiteNode *node,
                                     TfLiteContext *context) const override
      {
         std::cout<<"\033[33m check op is support \033[0m"<<std::endl;
        return Validate(registration, node, context);
      }

      TfLiteStatus Initialize(TfLiteContext *context) override { return kTfLiteOk; }

      const char *Name() const override { return "TfLiteMyDelegate"; }

      std::unique_ptr<SimpleDelegateKernelInterface>
      CreateDelegateKernelInterface() override
      {
        return std::make_unique<MyDelegateKernel>(options_);
      }

      SimpleDelegateInterface::Options DelegateOptions() const override
      {
        auto options = SimpleDelegateInterface::Options();
        return options;
      }

    private:
      MyDelegateOptions options_;
    };

  } // namespace my
} // namespace tflite



TfLiteDelegate *
TfLiteMyDelegateCreate(const MyDelegateOptions *options)
{
  auto delegate = std::make_unique<tflite::my::MyDelegate>(options);
  std::cout<<"\033[33m create delegate\033[0m"<<std::endl;

  return tflite::TfLiteDelegateFactory::CreateSimpleDelegate(
      std::move(delegate));
}

void TfLiteMyDelegateDelete(TfLiteDelegate *delegate)
{
  tflite::TfLiteDelegateFactory::DeleteSimpleDelegate(delegate);
}