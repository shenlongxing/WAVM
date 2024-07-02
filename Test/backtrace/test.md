# 编译 wasm

分别编译带/不带函数名的 wasm。
* sigabrt 抛 wavm 可捕获异常。
* sleep3 等待三秒，模拟超时，vm 侧 raise sigabrt

```sh
emcc -O1 -s STANDALONE_WASM -o sigabrt.wasm sigabrt.c
emcc --profiling-funcs -s STANDALONE_WASM -o sigabrt_pf.wasm sigabrt.c
emcc -O1 -s STANDALONE_WASM -o sleep3.wasm sleep3.c
emcc --profiling-funcs -s STANDALONE_WASM -o sleep3_pf.wasm sleep3.c
```

# 编译 WAVM
用目录下 backtrace_test.cpp 替换 wavm-run.cpp

```sh
mv ../../Programe/wavm/wavm-run.cpp ../../Programe/wavm/wavm-run.cpp-backup && \
cp ./backtrace_test.cpp ../../Programe/wavm/wavm-run.cpp
```

编译 WAVM ，可能需要指定 LLVM 位置

``` sh
pushd ../../ && mkdir build && cd build && cmake .. -DLLVM=/home/docker/xiangjia.xj/LLVM_9.0.1 && make -j
```

# 测试 sigabrt

```sh
./bin/wavm run ../Test/backtrace/sigabrt.wasm
./bin/wavm run ../Test/backtrace/sigabrt_pf.wasm
```

期望结果
* 一个打印 wasm 函数名，一个没有。
* 均可以打印 host 侧 “_” 开头的 C 风格函数名，如 __libc_start_main 。

# 测试 sleep3

```sh
./bin/wavm run ../Test/backtrace/sleep3.wasm
./bin/wavm run ../Test/backtrace/sleep3_pf.wasm
```

期望结果
* 均 core dump ；标准输出无可用信息。
* `gdb ./bin/wavm core-xx`
```sh
gdb > t 2
gdb > bt
```
一个可以看到函数名，一个只有函数索引
