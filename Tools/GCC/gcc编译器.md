---
title: "gcc编译器"
author: "Zozo"
date: 2025-08-31
draft: true
---

### gcc编译器
- **gcc编译原理**
    1. 预处理/预编译：	`gcc -E test.c -o test.i`
        1. 将头文件中的内容全部复制过来
        2. 删除注释
        3. 宏替换
        4. 条件编译
        ```bash
            # 查看预处理结果
            cat main.i | head -20
        ``` 
    2. 编译:	`gcc -S test.i -o test.s`
        - 将c语言转换成汇编语言
        ```bash
            # 查看汇编代码
            cat main.s
        ``` 
    3. 汇编:    `gcc -c test.s -o test.o`
        - 将汇编语言转换成二进制码
        ```bash
            # 查看目标文件信息
            file main.o
            nm main.o
        ``` 
    4. 链接：   `gcc test.o -o test`
        - 将程序中需要使用到的所有参数添加到一起 生成一个可执行文件
 
 ```mermaid
 graph LR
    A[源代码.c] --> B[预处理]
    B --> C[编译]
    C --> D[汇编]
    D --> E[链接]
    E --> F[可执行文件]
    
    style B fill:#e1f5fe
    style C fill:#fff3e0
    style D fill:#f3e5f5
    style E fill:#c8e6c9
 ``` 

- **常用编译选项**
基本选项:
```bash
    # 指定输出文件
    gcc -o program main.c

    # 只编译不链接
    gcc -c main.c

    # 显示警告信息
    gcc -Wall main.c -o program

    # 显示所有警告
    gcc -Wall -Wextra main.c -o program
```
优化选项:
```bash
    # 优化级别
    gcc -O0 main.c -o program    # 不优化（调试用）
    gcc -O1 main.c -o program    # 基本优化
    gcc -O2 main.c -o program    # 推荐优化级别
    gcc -O3 main.c -o program    # 激进优化
    gcc -Os main.c -o program    # 优化代码大小

    # 架构特定优化
    gcc -march=native main.c -o program  # 针对本机CPU优化
```

调试选项:
```bash
    # 生成调试信息
    gcc -g main.c -o program

    # 不同级别的调试信息
    gcc -g0 main.c -o program  # 无调试信息
    gcc -g1 main.c -o program  # 最小调试信息
    gcc -g2 main.c -o program  # 默认调试信息
    gcc -g3 main.c -o program  # 最大调试信息
```

包含路径和库选项:
```bash
    # 添加头文件搜索路径
    gcc -Iinclude main.c -o program
    gcc -I/home/user/include main.c -o program

    # 添加库搜索路径
    gcc -Llib main.c -o program
    gcc -L/usr/local/lib main.c -o program

    # 链接库
    gcc main.c -lm -o program      # 数学库
    gcc main.c -lpthread -o program # 线程库
```

- **编译静态链接库**    ==详细例程可参考IO_FILE文件==
1. **生成目标文件 .o**
    `gcc -c libcount.c -o libcount.o`
2. **ar crv [*.a][*.o]**
    `ar cdv libcount.a libcount.o`
3.  **使用静态库 -I 添加头文件**
```bash
    gcc [file.c] [file.a] -o [file]
        gcc count.c libcount.a -o count
``` 

- **编译动态链接文件**  ==详细例程可参考IO_FILE文件==
1. 生成位置无关的.o文件	    `-fPIC` 该参数表示与位置无关
        `gcc -c add.c sub.c mul.c -fPIC`
2. 制作动态库
```bash
    gcc -shared -o lib库名.so xxx.o xxx.o
        gcc -shared -o libMyMath.so add.o sub.o mul.o
    # 创建lib文件 将so文件拷贝进去
``` 
3. 编译程序
`-l` 指定库名
`-L` 指定动态库路径
`-I` 指定头文件
    `gcc main.c -o main -l MyMath -L ./lib/ -I ./inc/`

- **可能报错找不到动态库 解决方案：**
1. 环境变量设置 ： `export LD_LIBRARY_PATH=动态路径 `
    `export LD_LIBRARY_PATH=home/…/…/lib`
2. 修改启动配置文件 `～/.bashrc`
```bash
    vim ~/.bashrc
    export LD_LIBRARY_PATH=home/…/…/lib
    source ~/.bashrc 让配置文件生效
```
3. 将so动态库放入/lib或者/lib/x86_64-linux-gnu

- **交叉编译**
交叉编译选项:
```bash
    # 指定目标架构
    gcc -m32 main.c -o program32    # 编译32位程序
    gcc -m64 main.c -o program64    # 编译64位程序

    # 交叉编译到其他架构
    arm-linux-gnueabi-gcc main.c -o program_arm
    x86_64-w64-mingw32-gcc main.c -o program.exe
```

多架构支持:
```bash
    # 生成多架构代码
    gcc -march=x86-64 -mtune=generic main.c -o program

    # 针对特定微架构优化
    gcc -march=skylake main.c -o program
```
- **环境变量和配置**
编译器环境变量:
```bash
    # 设置编译器路径
    export CC=gcc
    export CXX=g++

    # 设置默认选项
    export CFLAGS="-Wall -O2"
    export CXXFLAGS="-Wall -O2 -std=c++11"
    export LDFLAGS="-L/usr/local/lib"
``` 

配置编译环境:
```bash
    # 查看编译器信息
    gcc --version
    gcc -v              # 显示详细版本信息
    gcc -### main.c     # 显示所有调用的命令

    # 查看目标配置
    gcc -dumpmachine    # 显示目标架构
    gcc -dumpversion    # 显示版本号
```

- **诊断和错误处理**
错误检查:
```bash
    # 将警告视为错误
    gcc -Werror main.c -o program

    # 特定警告视为错误
    gcc -Werror=unused-variable main.c -o program

    # 忽略特定警告
    gcc -Wno-unused-variable main.c -o program
```

代码检查:
```bash
    # 静态分析
    gcc -fanalyzer main.c -o program

    # 内存检查
    gcc -fsanitize=address main.c -o program      # 地址检查
    gcc -fsanitize=undefined main.c -o program    # 未定义行为检查
    gcc -fsanitize=leak main.c -o program         # 内存泄漏检查
```
