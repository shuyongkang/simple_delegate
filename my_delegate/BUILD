load("@org_tensorflow//tensorflow/lite:build_def.bzl", "tflite_copts")

package(
    default_visibility = [
        "//visibility:public",
    ],
    licenses = ["notice"],
)

cc_library(
    name = "my_delegate_validation",
    srcs = [
        "my_delegate_validation.cc",
    ],
    hdrs = ["my_delegate_validation.h"],
    deps = [
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/core/api",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library(
    name = "my_types",
    hdrs = ["my_types.h"]
)



cc_library(
    name = "my_implementation",
    srcs = ["my_implementation.cc"],
    hdrs = glob(["my_implementation.h"],["tvm/**/*h"]),
    deps = [
        ":my_types",
        "@org_tensorflow//tensorflow/lite:allocation",
        "@org_tensorflow//tensorflow/lite:framework",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        
        
    ],
     linkopts = ['-ldl', '-lm'],
    
)

cc_library(
    name = "my_delegate_kernel",
    srcs = [
        "my_delegate.h",
        "my_delegate_kernel.cc",
    ],
    hdrs = ["my_delegate_kernel.h"],
    deps = [
        ":my_implementation",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/delegates/utils:simple_delegate"
    ],
)

cc_library(
    name = "my_delegate",
    srcs = ["my_delegate.cc"],
    hdrs = ["my_delegate.h"],
    deps = [
        ":my_delegate_kernel",
        ":my_delegate_validation",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/delegates/utils:simple_delegate",
    ],
)




