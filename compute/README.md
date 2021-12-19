# subgraph compute implementation

create lib.so
```g++ -o libcompute.so -g -shared -fPIC compute.cpp```




export LD_LIBRARY_PATH= libcompute.so path

