package(
    default_visibility = [
        "//visibility:public",
    ],
    licenses = ["notice"],
)



cc_test(
    name = "my_delegate_test",
    size = "small",
    srcs = [
        "my_delegate_test.cc",
    ],
    deps = [
        "//my_delegate:my_implementation",
         "//my_delegate:my_delegate",
        "@org_tensorflow//tensorflow/lite:framework",
        "@org_tensorflow//tensorflow/lite/examples/label_image:bitmap_helpers",
        "@org_tensorflow//tensorflow/lite/kernels:test_util",
        "@com_google_googletest//:gtest",
       
    ],
    linkopts = ['-ldl', '-lm'],
)