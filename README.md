windows或linux环境下安装好GCC或mingw编译器运行脚本".\build.ps1""sh build.sh"即可

Windows下CMake安装教程
https://blog.csdn.net/u011231598/article/details/80338941

Linux下安装CMake详细教程
https://blog.csdn.net/lhl1124281072/article/details/83188055

MinGW-w64安装教程——著名C/C++编译器GCC的Windows版本
https://zhuanlan.zhihu.com/p/76613134

Linux安装gcc方法（超简单安装）
https://blog.csdn.net/qq_45780190/article/details/114770824

运行效果示例：
============ log_tree running ============

======================
[main] log tree test is running
 |-[functionA] funcA is running, will run func B   
 |  |-[functionB] funcB is running, will run func C
 |  |  |-[functionC] funcC is running, will run func D
 |  |  |  |-[functionD] funcD is running
 |  |  |  |-[functionD] funcD is over
 |  |-[functionB] funcB is run 123456
 |  |-[functionB] funcB is run over
[main] print test
[main] log tree test over

后续计划：
1、优化多线程使用；
2、替代部分标准库，减小FLASH和ROM