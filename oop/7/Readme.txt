测试顺序：
1、vscode打开multiple_allocator，debug调试模式下运行test.cpp，输出完成的三种allocator与std::allocator的性能测试及比较
2、终端打开final_allocator，输入命令make/mingw32-make进行编译，输入命令./test运行可执行程序进行最终性能测试及比较（myallocator_1与std::allocator）