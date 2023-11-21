# concurrency-cpp-data-flow-hardware-sensors-code-challenge

Note: using pthreads since I ran into this issue using std::thread on MacOS Ventura 13.5. Here is the error message: 
```
/Applications/Xcode-beta.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/thread:288:5: error: attempt to use a deleted function
    _VSTD::__invoke(_VSTD::move(_VSTD::get<1>(__t)), _VSTD::move(_VSTD::get<_Indices>(__t))...);
```
Notice that I am using the latest BETA version of Xcode, so this could be a confounding factor. Nonetheless, pthreads will work jsut as well as std::threads. 

