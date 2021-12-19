#include "my_delegate/my_delegate_kernel.h"
#include "tensorflow/lite/builtin_ops.h"
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/context_util.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"

#include <iostream>
#include <string.h>
#include <string>

namespace tflite
{
  namespace my
  {

    TfLiteStatus MyDelegateKernel::Init(TfLiteContext *context,
                                        const TfLiteDelegateParams *params)
    {
      my_api_ = MyApiImplementation();
      if (!my_api_->my_exists)
      {
        TF_LITE_KERNEL_LOG(context, "My interface not available.");
        return kTfLiteError;
      }
      std::cout << "\033[33menter delegate init\033[0m" << std::endl;

      for (auto node_index : TfLiteIntArrayView(params->nodes_to_replace))
      {
        nodes_.push_back(node_index); //nodes index
      }

      TF_LITE_ENSURE_STATUS(BuildGraph(context, params->input_tensors, params->output_tensors));

      return kTfLiteOk;
    }

    TfLiteStatus MyDelegateKernel::BuildGraph(TfLiteContext *context,
                                              const TfLiteIntArray *input_tensors,
                                              const TfLiteIntArray *output_tensors)
    {

      // if (my_api_->relay_model(subgraph, context) != 0) {
      //   TF_LITE_KERNEL_LOG(context, "Failed to build graph.");
      //   return kTfLiteError;
      // }
      return kTfLiteOk;
    }

    TfLiteStatus MyDelegateKernel::Prepare(TfLiteContext *context,
                                           TfLiteNode *node)
    {
      std::cout << "\033[33menter delegate prepare\033[0m" << std::endl;
      // my_api_ = MyApiImplementation();
      // if (my_api_ == nullptr){
      //   TF_LITE_KERNEL_LOG(context, "My interface not available, prepare.");
      //   return kTfLiteError;
      // }
      return kTfLiteOk;
    }

    TfLiteStatus MyDelegateKernel::Eval(TfLiteContext *context,
                                        TfLiteNode *node)
    {
      std::cout << "\033[33menter delegate eval\033[0m" << std::endl;
      my_api_ = MyApiImplementation();
      if (my_api_ == nullptr)
      {
        TF_LITE_KERNEL_LOG(context, "My interface not available, eval.");
        return kTfLiteError;
      }

      //get the subgraph input
      TfLiteIntArray *input_tensors = node->inputs;
      int tensor_index = input_tensors->data[0];
      auto &input_tensor = context->tensors[tensor_index];
      auto *input = GetTensorData<int8_t>(&input_tensor);

      TfLiteIntArray *input_dims = input_tensor.dims;
      int input_size = 1;
      for (int i = 0; i < input_dims->size; i++)
      {
        input_size *= input_dims->data[i];
      }
      std::cout << "inpt_tensor_value:" << std::endl;
      for (int i = 0; i < 2; ++i)
      {
        std::cout << float(input[i]) << std::endl;
      }

      //compute   compute

      TfLiteIntArray *output_tensors = node->outputs;
      tensor_index = output_tensors->data[0];
      //write inference result to output tensor
      auto &output_tensor = context->tensors[tensor_index];
      auto *output = GetTensorData<int8_t>(&output_tensor);
      TfLiteIntArray *output_dims = output_tensor.dims;
      int output_size = 1;
      for (int i = 0; i < output_dims->size; i++)
      {
        output_size *= output_dims->data[i];
      }

      for (int i = 0; i < output_size; ++i)
      {
        output[i] = 100;
      }

      int status = 0; //my_api_->myEvalModel();
      if (status != 0)
      {
        TF_LITE_KERNEL_LOG(context, "Failed to execute graph.");
        return kTfLiteError;
      }
      return kTfLiteOk;
    }

    MyDelegateKernel::~MyDelegateKernel()
    {
      if (my_api_ != nullptr)
        my_api_ = nullptr;
    }

  } // namespace my
} // namespace tflite