This is TfLite My Delegate.
# Build Tutorial

1. Download Bazel(At least 3.7.1).
2. Use following cmd to test my delegate:
   ```
   bazel build my_delegate_test
   ```


 可以把delegate计算的函数库放在 libcompute.so 中，在eval中调用该计算过程

export LD_LIBRARY_PATH= libcompute.so path

g++ -o libcompute.so -g -shared -fPIC compute.cpp