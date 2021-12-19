#ifndef TENSORFLOW_LITE_MANASI_TYPES_H_
#define TENSORFLOW_LITE_MANASI_TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include "tensorflow/lite/builtin_ops.h"
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/op_resolver.h"


typedef int (*compute_fn)();

#endif // TENSORFLOW_LITE_MANASI_TYPES_H_