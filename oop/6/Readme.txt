终端打开源码所在目录，输入make/mingw32-make进行编译与生成可执行文件。
输入./Vector执行可执行文件，可见终端输出如下：
Initialize Vector::a //测试 Vector<int> a （默认无参构造）
Push 1 into a //测试 a.push_back(1)
Initialize Vector::b(10) //测试 Vector<int> b(10) （含参构造）
Make b = a //测试 b = a （赋值运算符）
Initialize Vector::c(a)
c comes from Copy Ctor of a //测试 Vector<int> c(a) （拷贝构造）
b[0] is 1 //验证赋值运算是否完成，并测试[]的重载
c[0] is 1 //验证拷贝构造是否完成
The size of a is 1 //测试 a.size()
After a.clear(), the size of a is 0 //测试并验证a.clear()的效果
a is empty: Yes //测试a.empty()
b is empty: No
c is empty: No
a[10] is terminate called after throwing an instance of 'std::out_of_range'
  what():  Vector::range_check: n (which is 10) >= this->size() (which is 0)
//测试a.at(10)