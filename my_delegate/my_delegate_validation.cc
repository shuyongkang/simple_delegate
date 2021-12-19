#include "my_delegate/my_delegate_validation.h"
#include "tensorflow/lite/builtin_ops.h"
#include "tensorflow/lite/minimal_logging.h"
#include <iostream>


namespace tflite {
namespace my {


bool ExpectQuant8Operator(const TfLiteContext *context,
                          const TfLiteNode *node) {
  const auto input_type = context->tensors[node->inputs->data[0]].type;
  return input_type == kTfLiteUInt8  || input_type == kTfLiteInt8;  //add kTfLiteInt8 support
}

//
bool Validate(const TfLiteRegistration *registration, const TfLiteNode *node,
              TfLiteContext *context) {
  const auto builtin_code = registration->builtin_code;   //op type

  switch (builtin_code) {
  case kTfLiteBuiltinConv2d:               
  case kTfLiteBuiltinDepthwiseConv2d: {
    // TODO: what about FusedActivation?
    const auto &input_tensor = context->tensors[node->inputs->data[0]];  
    if (input_tensor.type != kTfLiteUInt8 && input_tensor.type != kTfLiteInt8)//add kTfLiteInt8 support
      return false;

    const auto &filter_tensor = context->tensors[node->inputs->data[1]]; 
    if (filter_tensor.type != kTfLiteUInt8 && filter_tensor.type != kTfLiteInt8)//add kTfLiteInt8 support
      return false;

    if (node->inputs->size == 3) {
      const auto bias_tensor = context->tensors[node->inputs->data[2]]; 
      if (bias_tensor.type != kTfLiteInt32) // bias data type must be int32 ??  int16?
        return false;

      if (bias_tensor.params.zero_point != 0)  //bias zeropoint  must be 0
        return false;
    }
    const auto input_scale = input_tensor.params.scale;   
    const auto filter_scale = filter_tensor.params.scale; 
    const auto output_scale =
        context->tensors[node->outputs->data[0]].params.scale; 
    if (input_scale * filter_scale >= output_scale) 
      return false;
    return true;
  }

  case kTfLiteBuiltinAdd: {    //add  op
    const auto input_type_0 = context->tensors[node->inputs->data[0]].type;
    const auto input_type_1 = context->tensors[node->inputs->data[1]].type;
    if ((input_type_0 != kTfLiteUInt8 && input_type_0 != kTfLiteInt8) ||
        input_type_1 != kTfLiteUInt8 && input_type_1 != kTfLiteInt8)
      return false;
    return false;
  }
  case kTfLiteBuiltinRelu:
  case kTfLiteBuiltinRelu6:
  //case kTfLiteBuiltinAveragePool2d:        /not support
  //case kTfLiteBuiltinReshape:         
  //case kTfLiteBuiltinSoftmax:
    return ExpectQuant8Operator(context, node);   
  default:
    TFLITE_LOG_PROD(tflite::TFLITE_LOG_WARNING,
                    "type %d is not supported by My delegate.",
                    builtin_code);  
    return false;
  }
  return false;
}
} // namespace my
} // namespace tflite