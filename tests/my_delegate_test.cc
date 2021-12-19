#include "my_delegate/my_delegate.h"
#include "tensorflow/lite/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/examples/label_image/bitmap_helpers.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/kernels/test_util.h"
#include "tensorflow/lite/model.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>


int main() {
  char model_path[]  = "/home/shuyongkang/delegate_test/vgg16_int8.tflite";
  bool with_delegate = true;
  std::unique_ptr<tflite::FlatBufferModel> model;
  std::unique_ptr<tflite::Interpreter> interpreter;
  model = tflite::FlatBufferModel::BuildFromFile(model_path);
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder(*model, resolver)(&interpreter);
  // ASSERT_TRUE(interpreter != nullptr);

  if (with_delegate) {
    MyDelegateOptions option;
    //create my delegate
    auto *delegate_ptr = TfLiteMyDelegateCreate(&option);
    // ASSERT_TRUE(delegate_ptr != nullptr);
    auto delegate = tflite::Interpreter::TfLiteDelegatePtr(
        delegate_ptr,
        [](TfLiteDelegate *delegate) { TfLiteMyDelegateDelete(delegate); });
    // Add delegate.
    EXPECT_TRUE(interpreter->ModifyGraphWithDelegate(delegate.get()) !=
                kTfLiteError);
  }
  EXPECT_TRUE(interpreter->AllocateTensors() == kTfLiteOk);

  const std::vector<int> inputs = interpreter->inputs();   //input tensor index
  const std::vector<int> outputs = interpreter->outputs();
  int input_tensor_index = inputs[0]; 
  auto tensor = interpreter->typed_tensor<int8_t>(input_tensor_index);  //会做一个类型检查把
  TfLiteIntArray *input_dims = interpreter->tensor(input_tensor_index)->dims;
  int input_size = 1;
  for (int i = 0; i < input_dims->size; i++) {
    input_size *= input_dims->data[i];
  }
  for (int i = 0; i < input_size; i++) {
    tensor[i] = 66;   //input_data[i];
  }

  
  //gegin inference
  EXPECT_TRUE(interpreter->Invoke() == kTfLiteOk);
  


  //get the output
  int output_tensor_index = outputs[0];
  TfLiteIntArray *output_dims = interpreter->tensor(output_tensor_index)->dims;
  int output_size = 1;
  for (int i = 0; i < output_dims->size; i++) {
    output_size *= output_dims->data[i];
  }

  std::vector<float> quant_output;
  auto data = interpreter->typed_output_tensor<int8_t>(0);
  float output_scale = interpreter->tensor(output_tensor_index)->params.scale;  
  int zero_point = interpreter->tensor(output_tensor_index)->params.zero_point;
  for (int i = 0; i < 2; i++) {
    std::cout<<float(data[i]) <<std::endl;
    quant_output.push_back((data[i] - zero_point) * output_scale);
  }


  
}