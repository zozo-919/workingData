
### Makefile rule

- Linux下环境搭建：(ubuntu)
  - sudo apt install gcc g++ make	
  - make --version	查看make的版本	

- Makefile 默认文件名："GNUmakefile" 或 "makefile" 或 `Makefile`(**常用**)
    - 也可使用别的文件名书写makefile
      - 指定特定的makefile 使用： make -f Make.Linux 或 make --file Makefile.Win32

- 源文件 -->  编译: object file 中间代码文件(.o)  -->  链接: 执行文件
    - **编译**: 检查语法正确 函数、变量声明正确 一般每个源文件对应一个中间目标文件。

    - **链接**: 链接函数 全局变量
        ```bash
                target ... : prerequisites ...
                        command
                        ...
                        ...

                # target - OBJ (目标中间文件或最终可执行文件)
                # prerequisites - 依赖文件 即: 生成target所需要的文件或目标
                # command - 也就是make需要执行的命令
                # Makefile中的命令必须以【Tab】键开始。
        ```
        - **示例**
        ```bash
                edit : main.o kbd.o command.o display.o insert.o search.o files.o utils.o
                        gcc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o

                main.o : main.c defs.h
                        gcc -c main.c
                kbd.o : kbd.c defs.h command.h
                        gcc -c kbd.c
                command.o : command.c defs.h command.h
                        gcc -c command.c
                display.o : display.c defs.h buffer.h
                        gcc -c display.c
                insert.o : insert.c defs.h buffer.h
                        gcc -c insert.c
                search.o : search.c defs.h buffer.h
                        gcc -c search.c
                files.o : files.c defs.h buffer.h command.h
                        gcc -c files.c
                utils.o : utils.c defs.h
                        gcc -c utils.c
                clean :
                        rm edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o

                # 注释: clean并非一个文件, 而是一个动作, 表示删除edit所产生的文件, clean 最好放在文件最后。
        ```
        - **示例简化版1**
        ```bash
                # 姑且把objs看作一个宏 代表这些.o文件
                OBJS = main.o kbd.o command.o display.o insert.o search.o files.o utils.o

                edit : $(OBJS)
                        gcc -o edit $(OBJS)

                main.o : main.c defs.h
                        gcc -c main.c
                kbd.o : kbd.c defs.h command.h
                        gcc -c kbd.c
                command.o : command.c defs.h command.h
                        gcc -c command.c
                display.o : display.c defs.h buffer.h
                        gcc -c display.c
                insert.o : insert.c defs.h buffer.h
                        gcc -c insert.c
                search.o : search.c defs.h buffer.h
                        gcc -c search.c
                files.o : files.c defs.h buffer.h command.h
                        gcc -c files.c
                utils.o : utils.c defs.h
                        gcc -c utils.c

                clean:
                        rm edit $(OBJS)

        ```
        - **示例简化版2**
        ```bash
                # make的自动推导
                OBJS = main.o kbd.o command.o display.o insert.o search.o files.o utils.o

                edit : $(OBJS)
                        gcc -o edit $(OBJS)

                main.o : defs.h
                kbd.o : defs.h command.h
                display.o : defs.h buffer.h
                insert.o : defs.h buffer.h
                search.o : defs.h buffer.h
                files.o : defs.h buffer.h command.h
                utils.o : defs.h

                # (表示clean是一个伪目标, 并不对应具体的文件)
                .PHONY: clean
                clean:
                        rm edit $(OBJS)
        ```

- **引用其他的Makefile**
    - **include的语法**
        ```bash
                include filename
                # filename可以是当前操作系统shell的文件模式(可以包含路径和通配符)
        ```
      - ‼️ **注意**: include前面可以有空字符, 但**绝不能**`Tab`键开始

    - **示例**
        ```bash
                # 假设有几个Makefile: a.mk 、b.mk 、c.mk ; 还有一个文件叫foo.make 及一个变量$(bar): 其中包含e.mk和f.mk 。
                include foo.make *.mk $(bar)
                # 等价于 :
                include foo.make a.mk b.mk c.mk e.mk f.mk
                

                -include filename  # (- 代表忽略错误)
                # include过程中出现任何错误都不报错继续执行。
        ```

- **make工作步骤**
    1. 读入所有的Makefile
    2. 读入被include的其他Makefile
    3. 初始化文件中的变量
    4. 推导隐晦规则，并分析所有规则
    5. 为所有目标文件创建依赖关系链
    6. 根据依赖关系，决定哪些目标要重新生成
    7. 执行生成命令


- **make支持的通配符**
    `*` , `?`,  `[...]` 
    - `$@：` 当前目标名
    - `$<：` 第一个依赖项
    - `$^：` 所有依赖项
    - `$?：` 比目标新的所有依赖项
      - **示例**
        ```bash
                clean :
                        rm *.o
                #  * 通配符 *.o  表示所有.o结尾的文件

                print : *.c
                        lpr -p $?
                        touch print
                #  目标print依赖于所有.c文件 , $? : 自动化变量

                objects = *.o
                # objects的值是 " *.o " ,并不展开 " *.o "

                # 若是要展开则:
                objects := $(wildcard *.o)
                # 其中 "wildcard" 是一个关键字

        ```

- **文件搜寻**: make永远优先从当前目录开始搜寻文件
    - 变量 `VPATH` : 用于指定makefile搜索路径 其默认值是当前目录
        ```bash
           VPATH = src:../headers
           # 则makefile会搜索 src目录 和 ../headers目录
        ```    
    - 关键字: `vpath`
        1. `vpath pattern directories`
            用于指定搜索路径, pattern是匹配模式, directories是目录列表。
        2. `vpath pattern`
            清除符合模式 <pattern> 的文件搜索目录。
        3. `vpath`
            清除所有已被设置好的文件搜索目录。
           - <pattern> 需要包含 `%` 字符  意为: 匹配零或若干字符。
                ```bash 
                   vpath %.h ../headers
                   # 该语句表示要求make在 ../headers 目录下搜索所有以 .h 结尾的文件。
                ```
                - **示例**
                ```bash
                  vpath %.c src
                  vpath %   blish
                  vpath %.c bar
                  # 表示: 先在src目录下搜索所有以.c结尾的文件, 再在blish,最后是bar目录。

                  vpath %.c src:bar
                  # 表示: 先在src目录下搜索所有以.c结尾的文件, 再在bar目录下搜索。
                ```


- **伪目标**：  伪目标不是一个文件, 只是一个标签。
    - `.PHONY` : 显示的向make指明一个目标是 “伪目标”。
        - 伪目标放在第一个, 可以作为默认目标。
        ```bash
                .PHONY: cleanall cleanobj cleandiff

                cleanall: cleanobj cleandiff
                        rm program

                cleanobj:
                        rm *.o

                cleandiff:
                        rm *.diff

                # 输入make cleanall 、make cleanobj 、make cleandiff 达到清除不同种类文件的目的。

        ```
---
- ==**暂未理解区**==

  - **多目标**
```bash
    bigoutput littleoutput : text.g
            generate text.g -$(subst output,,$@) > $@
    等价于：
    bigoutput : text.g
            generate text.g -big > bigoutput
    littleoutput : text.g
            generate text.g -little > littleoutput

    # -$(subst output,,$@)中 $ 表示执行一个Makefile的函数,函数名为subst,后面的是参数。 $@ 依次取出目标并执行
        
```
---

- **静态模式**:{
```bash
        <targets ...> : <target-pattern>: <prereq-patterns ...>
                <commands>
                ...

        objects = foo.o bar.o
        all: $(objects)
        $(objects): %.o : %.c
                $(CC) -c $(CFLAGS)  $< -o $@

        # 指明我们的目标从 objects 中获取, %.o 表明要所有以.o结尾的目标,即foo.o和bar.o;
        # 依赖模式 %.c 即表示依赖于所有以 .c 结尾的文件,即foo.c和bar.c;
        # $< 表示第一个依赖目标集(foo.c和bar.o); $@ 表示目标集(foo.o和bar.o)。
        # 所以以上等价于：
        foo.o : foo.c
                $(CC) -c $(CFLAGS)  foo.c -o foo.o
        bar.o : bar.c
                $(CC) -c $(CFLAGS)  bar.c -o bar.o
```

- **自动生成依赖性**
  - 假设我们的main.c中有 `#include <defs.h>` 则依赖关系应该是 `main.o : main.c defs.h`
        - `cc -M main.c`     ====>   将自动生成上列依赖关系
          - **-M选项** 自动寻找源文件中的头文件 并生成依赖关系。
          - 为避免将一些标准的头文件包含进来，可用 `-MM` 选项, 它会生成一个makefile依赖文件[ .d ]。
        ```bash
                sources = foo.c bar.c
                include $(sources:.c=.d)
                # ".c=.d"意思是做替换 把变量$(sources)所有的[.c]字串都替换成[.d]。
        ```

---
- ==**暂未理解**==

        一个生成[.d]文件的模式规则：
        %.d: %.c
                @set -e; rm -f $@; /
                $(CC) -M $(CPPFLAGS)  $< > $@.; /
                sed 's, /($*/)/.o[ :]*,/1.o $@ : ,g' < $@. > $@; /
                rm -f $@.
---

- **命令执行**
  - 当依赖目标新于目标时, 即规则的目标需要被更新时,make会一条一条执行其后的命令。如果要让上一条命令的结果应用在下一条命令时,使用 `; `分隔这两条命令
```bash
        exec:
                cd /home/hchen; pwd
        # 当执行“make exec”时, 首先进入/home/hchen目录, 然后打印当前目录的路径。
```


- **命令出错**
 - 每当命令运行完后,make 会检测每个命令的返回码,如果命令返回成功,则make会执行下一条命令, 当规则中所有命令返回成功,这规则就算成功完成.若一个规则中某个命令出错,make就会终止执行当前规则, 这将有可能终止所有规则。
    - 忽略命令出错: 在makefile的命令行前加 `-` 符号即可。
        ```bash
                clean:
                        -rm -f *.o
        ```
    - 全局的办法:
        `make -i` 忽略所有命令出错。
        `make -k` 忽略规则出错, 继续执行剩余的规则。

- **嵌套执行make**
  - 假设子目录subdir, 该目录下有个Makefile文件。则总控的Makefile可以这样书写:
  ```bash
        subsystem:
                cd subdir && $(MAKE)
        # 等价于：
        subsystem:
                $(MAKE) -C subdir

        # $(MAKE)宏变量表示:或许make需要一些参数, 故定义为一个变量利于维护
  ```
  - 若想传递变量到下级Makefile, 则使用这样的声明：`export <variable ...>`
  - 若不想传递变量到下级Makefile, 则使用这样的声明： `unexport <variable ...>`
  ```bash
          export variable = value
          # 等价于:  
          variable = value
          export variable
          #等价于: 
          export variable := value
          # 等价于: 
          variable := value
          export variable
  ```
  - 若要传递所有的变量 则只需要一个 `export` 即可

  - 有两个变量: `SHELL`、`MAKEFLAGS`, **不管是否exprot,总是要传递到下层Makefile中**
    - 尤其MAKEFLAGS是一个系统级的环境变量。若不想往下层传递参数,则可这样：
        ```bash 
                subsystem:
                        cd subdir && $(MAKE) MAKEFLAGS=
        ```

  - make命令中有几个参数并不往下传递: `-f`、 `-c`、 `-h`、 `-o`、 `-w`
    - `make -w` 在make过程中输出一些信息,可看到目前工作的目录。
        - 当使用`-c` 参数指定make下层Makefile时, -w 会自动打开, 若参数中有`-s` 则 `-w` 失效。

- **定义命令包**
  - 如果Makefile中出现一些相同命令序列, 则可以为这些相同命令序列定义一个变量, 以`define`开始以`endef`结束,如
```bash 
        define run-yacc
        yacc $(firstword $^)
        mv y.tab.c $@
        endef
        # 注释: run-yacc是命令包名, $^表示依赖文件集, $@表示目标文件。第一行运行yacc程序,第二行将生成的y.tab.c文件重命名为目标文件名。

        foo.c : foo.y
                $(run-yacc)
        注释: $^ 就是foo.y  $@ 就是foo.c
```     

- **变量的基础**
  - 变量的名字可以包含字符、数字、下划线, 不应含有 : 、 # 、  = 或空字符。
  - 变量在声明时需赋初值, 使用时需加上$符号, 最好用 () 把变量名包括。

- **变量中的变量**
```bash
        foo = $(bar)
        bar = $(baz)
        baz = 123

        all:
                echo $(foo)
        # 我们执行 "make all" 时, 输出 "123" 。

        x := foo
        y := $(x) bar
        x := later
        # 等价于:
        y := foo bar
        x := later
        # 操作符 := 用于将变量的值赋给一个变量, 而不是将变量的名字赋给另一个变量。

        nullstring :=
        space := $(nullstring) # 空格
        # 定义一个空变量 nullstring, 用#注释符来表示变量定义的终止。

        FOO ?= bar
        # 如果FOO没有被定义过 则变量FOO的值为bar 如果定义过 则什么也不做
```


- **变量高级用法**:{
  - **变量值替换** 格式: `$(var:a=b) 或 ${var:a=b}`
  ```bash 
        foo := a.o b.o c.o
        bar := $(foo:.o=.c)
        # 第一行定义一个$(foo)变量,第二行把$(foo)中所有以.o结尾的全部替换为.c  因此,$(bar)的值是 "a.c b.c c.c" 。
        foo := a.o b.o c.o
        bar := $(foo:%.o=%.c)
        # 同eg1
  ```

 - **把变量的值再当做变量**
```bash
        x = y
        y = z
        a := $($(x))
        # 注释:$(x) 的值为y,故$($(x))就是$(y); 而$(y)的值是z,故$(a)的值是z。

        x = y
        y = z
        z = u
        a := $($($(x)))
        # 注释:$(x)的值为y,$($($(x)))就是$($(y));$(y)的值是z, $($(y))就是$(z);$(z)的值是故$(a)的值是u。

        x = $(y)
        y = z
        z = hello
        a :=$($(x))
        # 注释:$(x) 的值为 $(y),$(y) 的值为 z,$(z) 的值为 hello, $($(x))即$($(y));即$(z);故$(a)的值为hello
        
        x = variable1
        variable2 := hello
        y = $(subst 1,2,$(x))
        z = y
        a := $($($(z)))
        # 注释:$(z)的值为y,故$($($(z)))即$($(y))即$($(subst 1,2,$(x)));
                # $(x)的值是variable1,subst函数把variable1中所有的1替换为2,故$(subst 1,2,$(x))即 variable2;
                # $(variable2)的值为hello;故$(a)的值为hello。

        first_second = hello
        a = first
        b = second
        all = $($a_$b)
        # 注释:$(a)的值为first,$(b)的值为second,故$($a_$b)即$($(a)_$(b))即$(first_second)即hello。
```


- **追加变量值**
  - 操作符 ` += `
```bash 
        objects = main.o foo.o bar.o utils.o
        objects += another.o
        # 注释: 等价于 objects = main.o foo.o bar.o utils.o another.o
```

  - 如果变量之前没有定义过,则 `+=`会自动变为 `=`  如果前面有变量定义 则 `+=` 会继承于前次操作的赋值符
```bash
        variable := value
        variable += more
        # 等价于:
        variable := value
        variable := $(variable) more

        # 但是
        variable = value
        variable += more
        # 由于继承 " = " 就不会发生变量的递补归定义,make会自动解决该问题。

```

- **override指示符**
  - 如果有变量是通常make的命令行参数设置的,那么Makefile中对这个变量的赋值会被忽略。
  - 若想在Makefile中设置这类参数的值,那么可以使用override指示符。规则如下:
```bash
        override <variable> = <value>
        override <variable> := <value>
        override <variable> += <more text>   # 追加

        # 对多行定义,用define指示符,在define前,也可用override指示符。如:
        override define foo
        bar
        endef
```

- **多行变量**
  - define关键字设置变量值。
  - define指示符后跟变量名,重起一行定义变量值,以endef关键字结束。变量值可包含函数、命令、文字 或其他变量,命令需【Tab】键开始。
```bash
        define two-lines
        echo foo
        echo $(bar)
        endef
```

- **环境变量**
  - make运行时的系统环境变量可以在make开始运行时被载入Makefile文件中,但如果Makefile中已定义该变量, 或该变量有make命令行带入,则系统的环境变量值将被覆盖。(如果make指定了 -e 参数,那么系统环境变量将覆盖Makefile中定义的变量)
  - Makefile中定义的变量像"全局变量"的特性,系统环境变量像"局部变量"的特性。


- **目标变量**
  - 为某个目标设置局部变量, 作用范围只在该规则及连带规则中,其值只在作用范围内有效,而不影响规则链以外的全局变量的值。格式如下:
```bash
        <target ...> : <variable-assignment>
        <target ...> : override <variable-assignment>
        <variable-assignment> #可以使各种赋值表达式。

        prog : CFLAGS = -g
        prog : prog.o foo.o bar.o
                $CC $(CFLAGS) prog.o foo.o bar.o
        prog.o : prog.c
                $CC -c $(CFLAGS) prog.c
        foo.o : foo.c
                $CC -c $(CFLAGS) foo.c
        bar.o : bar.c
                $CC -c $(CFLAGS) bar.c
        # 注释: 不管全局的$(CFLAGS)的值是什么,在prog目标,及其所引发的规则中,$(CFLAGS)的值都是-g。
```

- **模式变量**
  - 给定一种模式, 把变量定义在符合这种模式的所有目标上。格式同目标变量一样。
  - 给所有以.o结尾的目标定义目标变量: `%.o : CFLAGS = -o`

- **条件判断**
```bash
        ifeq (...)
            ...
        else
            ...
        endif

        # 四个关键字: ifeq 、ifneq、ifdef、ifndef
        # make不允许把整个条件语句分成两部分放在不同文件中
```

- **函数**
  - 函数调用语法:
    - ` $(<function> <arguments>) 或 ${<function> <arguments>} `
        - function函数名, arguments参数,参数间以 ` , ` 分隔,函数名和参数间以空格分隔；函数调用以$开头,用 () 或 {} 将函数名和参数括起。
        ```bash
              comma := ,
              empty :=
              space := $(empty) $(empty)
              foo := a b c
              bar := $(subst $(space),$(comma),$(foo))

              函数subst是一个替换函数,它的第一个参数是被替换的字符,第二个参数是替换后的字符,
              第三个参数是被替换的字符串。故$(bar)的值是"a,b,c"。
        ```

    - 字符串处理函数
        ```bash
                # 格式
                $(subst <from>,<to>,<text>)

                # 格式
                $(patsubst <pattern>,<replacement>,<text>)
                # 示例
                $(patsubst %.c,%.o,x.c.c bar.c)
                # 把字串 "x.c.c bar.c" 符合模式[%.c]的单词替换成[%.o];返回结果是"x.c.o bar.o"。
                

                $(strip <string>)
                # strip: 去空格函数,去掉<string>字串中开头和结尾的空字符;返回被去掉空格的字符串值。
                $(strip a  b  c )
                # 原字串"a b c ", 返回"a b c"。

                $(findstring <find>,<in>)
                # findstring: 查找字符串函数,在字串<in>中查找<find>字串;找到则返回<find>,否则返回空字符串。
                $(findstring a,abc)     # 返回"a"
                $(findstring b,a c)     # 返回空字符串

                $(filter <pattern...>,<text>)
                # filter: 过滤函数,以<pattern>模式过滤<text>字符串中的单词,保留符合模式<pattern>的单词, 可以有多个模式;返回符合模式<pattern>的字串。
                sources := foo.c bar.c baz.s ugh.h
                foo: $(sources)
                        cc $(filter %.c %.s,$(sources)) -o foo
                #注释:$(filter %.c %.s,$(sources))的返回值是"foo.c bar.c baz.s"。

                $(filter-out <pattern...>,<text>)
                # filter-out: 反过滤函数,以<pattern>模式过滤<text>字符串中的单词,去除符合模式<pattern>的单词。返回不符合模式<pattern>的字串。
                objects = main1.o foo.o main2.o bar.o
                mains = main1.o main2.o
                $(filter-out $(mains),$(objects)) # 返回值是"foo.o bar.o"。

                $(sort <list>)
                #sort: 排序函数,给字符串<list>中的单词排序(升序);返回排序后的字符串。
                $(sort foo bar lose)  # 返回 bar foo lose
                # sort函数会去掉<list>中相同的单词。

                $(word <n>,<text>)
                # word: 取单词函数,取字符串<text>中的第n个单词;从1开始计数; 返回字符串<text>中的第n个单词。
                $(word 2,a b c)  # 返回 "b"

                $(wordlist <s>,<e>,<text>)
                # wordlist: 取单词串函数,从字符串<text>中取出<s>开始到<e>的单词串;<s>和<e>是一个数字; 返回字符串<text>中从<s>到<e>的单词串。如果s大于<text>的单词数,则返回空字符串;如果e大于<text>的单词数, 则取到最后一个单词。
                $(wordlist 2,3,foo bar baz)  # 返回 "bar baz"

                $(words <text>)
                # words: 单词个数统计函数,统计<text>字符串中的单词个数;返回单词个数。
                $(words foo bar baz)  # 返回 "3"

                $(firstword <text>)
                # firstword: 首单词函数,取字符串<text>中的第一个单词;返回字符串<text>中的第一个单词。
                $(firstword foo bar baz)  # 返回 "foo"

                override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
                # 注释:若'VPATH'的值是"src:../headers", 则 $(subst :, ,$(VPATH))的返回值是"src ../headers", $(patsubst %,-I%,src ../headers)的返回值是"-Isrc -I../headers"。
        ```

    - 文件名操作函数:{
        ```bash
                $(dir <names...>)
                # dir: 取目录函数,从文件名序列<names>中取出目录部分,目录部分是指最后一个反斜杠之前的部分; 如果没有反斜杠,则返回'./' ;返回文件名序列<names>的目录部分。
                $(dir src/foo.c hacks)   # 返回 src/ ./

                $(notdir <names...>)
                # notdir: 取文件函数,从文件名序列<names>中取出非目录部分,非目录部分是指最后一个反斜杠之后的部分;返回文件名序列<names>中非目录部分
                $(notdir src/foo.c hacks)   # 返回 foo.c hacks

                $(suffix <names...>)
                # suffix: 取后缀函数,从文件名序列<names>中取出后缀部分,返回文件名序列<names>的后缀序列, 如果没有后缀则返回空字串。
                $(suffix src/foo.c src-1.0/bar.c hacks)   # 返回 .c .c

                $(basename <names...>)
                # basename: 取前缀函数,从文件名序列<names>中取出各文件名前缀部分,返回文件名序列<names>的前缀序列,如果没有前缀则返回空字串。
                $(basename src/foo.c src-1.0/bar.c hacks)   # 返回 src/foo src-1.0/bar hacks

                $(addsuffix <suffix>,<names...>)
                # addsuffix: 加后缀函数,把后缀<suffix>加到<names>中的每个单词后面,返回加过后缀的文件名序列。
                $(addsuffix .c,foo bar)   # 返回 foo.c bar.c

                $(addprefix <prefix>,<names...>)
                # addprefix: 加前缀函数,把前缀<prefix>加到<names>中的每个单词前面,返回加过前缀的文件名序列。
                $(addprefix src/,foo bar)   # 返回 src/foo src/bar

                $(join <list1>,<list2>)
                # join: 连接函数,把<list2>中的单词对应的加到<list1>的单词后面,如果<list1>的单词个数比<list2>的多,那么<list1>中多出来的单词保持原样,如果<list1>的单词个数比<list2>的少, 那么多出来的单词复制在后面,返回连接后的单词序列。
                $(join a b c d e f g,1 22 3 4 5 6 7 8)   # 返回 a1 b22 c3 d4 e5 f6 g7 8
        ```

    - foreach函数:   用作循环
      - 格式: `$(foreach <var>,<list>,<text>)`
        - 把参数<list>中的单词逐一取出放到参数<var>所指定的变量里,然后再执行<text>所包含的表达式, 每次<text>会返回一个字符串,循环过程中,<text>所返回的字符串以空格分开,直到循环结束。
        ```bash 
                names := a b c d
                files := $(foreach n,$(names),$(n).o)
                # 注释: $(files)的值是"a.o b.o c.o d.o"  foreach中<var>参数是一个临时变量,在循环结束后自动销毁。
        ```

    - if函数
      - 格式: `$(if <condition>,<then-part>)` 或 `$(if <condition>,<then-part>,<else-part>)`
        - 若<condition>为真,则返回<then-part>的值,否则返回<else-part>的值; 若没有<else-part>,则返回空字符串。

    - call函数
      - 格式: `$(call <expression>,<parm1>,<parm2>,<parm3>...)`
        ```bash
                reverse = $(1) $(2)
                foo = $(call reverse,a,b)
                #  $(foo)的值是"a b"。

                reverse = $(2) $(1)
                foo = $(call reverse,a,b)
                #  $(foo)的值是"b a"。
        ```

    - origin函数:   显示变量的来源
      - 格式: `$(origin <variable>)`  其中<variable>是变量名
        - `undefined`   variable变量未定义
        - `default`     variable变量是默认定义
        - `environment` variable变量是环境变量 并且当Makefile被执行时,-e参数没有被打开
        - `file`        variable变量是Makefile中的定义
        - `command line` variable变量是命令行定义
        - `override`    variable变量是override指示符重新定义
        - `automatic`   variable变量是make自动定义的自动化变量,如$@,$<,$^,$?,$+,$*,$%,$@等

        - 假设有一个Makefile其中包含一个定义文件Make.def,在Make.def中定义了一个变量bletch,而环境中也有一个环境变量bletch,此时若想判断,如果变量来源于环境,就把它重定义,如果源于Make.def或命令行等非环境的,就保持原值,则可以这样写:
        ```bash
                ifdef bletch
                ifeq "$(origin bletch)" "environment"
                bletch = barf, gag, etc.
                endif
                endif
        ```
      

    - shell函数
      - shell函数用来执行shell命令,并返回命令的输出。
        ```bash
                contents := $(shell cat foo.txt)
                files := $(shell echo *.c)
        ```

    - 控制make的函数
      - `$(error <text ...>)` 产生一个致命错误, <text...>是错误信息。error函数不会在一被使用就会产生错误信息,如果把其定义在某变量中,并在后续脚本中使用这个变量也可以的
        ```bash
                ifdef ERROR_001
                $(error error is $(ERROR_001))
                endif
                # 在变量ERROR_001定义后执行时产生error调用。

                ERR = $(error found an error!)
                .PHONY: err
                err: ; $(ERR)
                # 在目录err执行时发生error调用。

                $(warning <text ...>)
                # 产生一个警告信息, <text...>是警告信息。输出一段警告信息,但不会导致make的退出。
        ```

- **make的运行**
  - make的退出码
    - 0: 成功
    - 1: 一般错误
    - 2: 若使用了make -q参数,并且make使得一些目标不需要更新,则退出码为2
  - 指定Makefile
    - 假设有一个Makefile名字是hchen.mk,则运行make命令时可以这样写: `make -f hchen.mk`


  - 指定目标
    - 一般地,make的最终目标是Makefile中的第一个目标,其他目标是由该目标连带出来,这是make的默认行为。
    - 一般makefile中的第一个目标是由许多目标组成,可以指示make完成所指定的目标。在make命令后直接跟目标名,可以指定make的最终目标。任何makefile中的目标都可以被指定为终极目标,除了'-' 开头和包含'='的目标
```bash
        sources = foo.c bar.c
        ifneq ($(MAKECMDGOALS),clean)
        include $(sources:.c=.d)
        endif
        # 只要输入命令不是make clean,则Makefile包含foo.d和bar.d文件。

        .PHONY: all
        all: prog1 prog2 prog3 prog4
        # 定义一个名为all的目标,其包含了四个目标prog1,prog2,prog3,prog4。
                # 可以使用 'make all' 命令来完成所有目标的编译 (如果把all目标放在第一个,则只需执行make),
                # 也可以使用 'make prog1' 来只编译prog1目标。
```
  - `all`       该伪目标是所有目标的目标, 一般是编译所有的目标。
  - `clean`     该伪目标功能是删除所有被make创建的文件。
  - `nstall`    该伪目标是安装已经编译好的程序,即 把目标执行文件拷贝到指定目标中。
  - `print`     该伪目标的功能是列出改变过的源文件。
  - `tar`       该伪目标是把源程序打包备份。
  - `dist`      该伪目标是创建一个压缩文件,一般是把tar文件压成z或gz文件。
  - `TAGS`      该伪目标是更新所有目标,以备完整的重编译使用。
  - `check`和`test`  该伪目标一般用来测试makefile的流程。
    - 🔔 如果要书写这些功能 最好使用这些名字命名目标,规范实用。


- **检查规则**
  - `-n`  `--just-print` `--dry-run` `--recon`
  - 打印命令, 但不执行命令。

  - `-t` `--touch`
  - 只更新目标文件的时间戳, 不重新生成目标文件。

  - `-q` `--question`
  - 找目标,如果目标不存在会打印错误信息。

  - `-W <file>` `--what-if=<file>` `--assume-new=<file>` `--new-file=<file>`
  - 该参数需要指定一个文件 一般是源文件 Make根据规则推导来运行依赖于该文件的命令。一般可以和 -n 参数一起使用 查看该依赖文件所发生的规则命令。


  - make的参数     GNU make 3.80的参数定义
    - `-b`
    - `-m`
      - 注释: 忽略和其它版本make的兼容性。

    - `-B`
    - `--always-make`
      - 注释: 所有的目标都需要更新（重编译）。

    - `-C <dir>`
    - `--directory=<dir>`
      - 注释: 指定读取makefile的目录 如果有多个'-C'参数 则后面的路径以前面的作为相对路径 并以最后的目录作为被指定目录
```bash
        make -C ~hchen/test -C prog
        # 等价于make -C ~hchen/test/prog
```

  - `—debug[=<options>]`
    - 注释: 输出make的调试信息 如果没有参数 那就是输出最简单的调试信息
    - <options>的取值
        - a —— 也就是all          输出所有的调试信息（会非常的多）
        - b —— 也就是basic        只输出简单的调试信息 即输出不需要重编译的目标
        - v —— 也就是verbose      在b选项的级别之上 输出的信息包括哪个makefile被解析 不需要被重编译的依赖文件(或是依赖目标)等
        - i —— 也就是implicit     输出所有的隐含规则
        - j —— 也就是jobs         输出执行规则中命令的详细信息  如命令的PID、 返回码等
        - m —— 也就是makefile     输出 make读取makefile、 更新makefile、 执行makefile的信息
  
  - `-d`  相当于'--debug=a'
  
  - `-e` 、`--environment-overrides` 指明环境变量的值覆盖makefile中定义的变量的值。
  
  - `-f=<file>` `--file=<file>` `--makefile=<file>` 指定需要执行的makefile。
  
  - `-h` `--help` 显示帮助信息。
  
  - `-i` `--ignore-errors` 在执行时忽略所有的错误。
  
  - `-I <dir>` `--include-dir=<dir>` 指定一个被包含makefile的搜索目标 可以使用多个'-I'参数来指定多个目录
  
  - `-j [<jobsnum>]` `--jobs[=<jobsnum>]` 指同时运行命令的个数 如果没有这个参数 make运行命令时能运行多少就运行多少 如果有一个以上的'-j'参数 那么仅最后一个'-j' 才是有效的。 (注意这个参数在MS-DOS中是无用的)
  
  - `-k` `--keep-going` 出错也不停止运行 如果生成一个目标失败了 那么依赖于其上的目标就不会被执行了
  
  - `-l <load>` `--load-average[=<load]` `-max-load[=<load>]` 指定make运行命令的负载
  
  - `-n` `--just-print` `--dry-run` `--recon` 仅输出执行过程中的命令序列 但并不执行
  
  - `-o <file>` `--old-file=<file>` `--assume-old=<file>` 不重新生成指定的<file> 即使这个目标的依赖文件新于它
  
  - `-p` `--print-data-base`  输出makefile中的所有数据 包括所有的规则和变量 这个参数会让一个简单的makefile都会输出一堆信息
    - 如果你只是想输出信息而不想执行makefile 你可以使用'make -qp'命令
    - 如果你想查看执行makefile前的预设变量和规则 你可以使用'make -p -f /dev/null'  该参数输出的信息会包含着makefile文件的文件名和行号
    - 所以用该参数来调试makefile会很有用 特别是当环境变量很复杂时

  - `-q` `--question`  不运行命令 也不输出 仅仅是检查所指定的目标是否需要更新 如果是0则说明要更新 如果是2则说明有错误发生

  - `-r` `--no-builtin-rules` 禁止make使用任何隐含规则

  - `-R` `--no-builtin-variabes`  禁止make使用任何作用于变量上的隐含规则

  - `-s` `--silent` `--quiet`  在命令运行时不输出命令的输出

  - `-S` `--no-keep-going` `--stop` 注释: 取消'-k'选项的作用 因为有些时候 make的选项是从环境变量'MAKEFLAGS'中继承下来的所以你可以在命令行中使用这个参数来让环境变量中'-k'选项失效

  - `-t` `--touch`  相当于UNIX的touch命令 只是把目标的修改日期变成最新的 也就是阻止生成目标的命令运行

  - `-v` `--version` 输出make程序的版本、版权等关于make的信息

  - `-w` `--print-directory`  输出运行makefile之前和之后的信息 这个参数对于跟踪嵌套式调用make时很有用

  - `--no-print-directory`  禁止'-w'选项

  - `-W <file>` `--what-if=<file>` `--new-file=<file>` `--assume-file=<file>`  假定目标<file>需要更新  如果和'-n'选项使用  那么这个参数会输出该目标更新时的运行动作如果没有'-n'那么就像运行UNIX的'touch'命令一样 使得<file>的修改时间为当前时间

  - `--warn-undefined-variables`  只要make发现有未定义的变量  那么就输出警告信息

- **隐含规则**
  - 使用隐含规则
    - 如果要使用隐含规则生成你需要的目标  那么不要写出这个目标的规则 make会试图去自动推导产生这个目标的规则和命令 如果make可以自动推导生成这个目标的规则和命令 那么这个行为就是隐含规则的自动推导 隐含规则是make事先约定好的一些东西。我们有下面的一个Makefile:
```bash
        foo : foo.o bar.o
                cc -o foo foo.o bar.o $(CFLAGS) $(LDFLAGS)
        # 这个Makefile中并没有写下如何生成foo.o和bar.o这两目标的规则和命令
        # 因为make的'隐含规则'功能会自动去推导这两个目标的依赖目标和生成命令
```
  - make会在自己的'隐含规则'库中寻找可以用的规则 如果有就会使用 如果没就会报错在上面的那个例子中 make调用的隐含规则是 把[.o]的目标的依赖文件置成[.c] 并使用C的编译命令'cc -c $(CFLAGS) [.c]'来生成[.o]的目标 所以完全没有必要写下下面的两条规则：
```bash
        foo.o : foo.c
                cc -c foo.c $(CFLAGS)
        bar.o : bar.c
                cc -c bar.c $(CFLAGS)
        # make和我们约定好了用C编译器'cc'生成[.o]文件的规则 这就是隐含规则
```

  - 一些隐含规则
    - 默认的后缀列表是：.out  .a  .ln  .o  .c  .cc  .C  .p  .f  .F  .r  .y  .l  .s  .S  .mod  .sym  .def  .h  .info  .dvi  .tex  .texinfo  .texi  .txinfo  .w  .ch  .web  .sh  .elc  .el

    - 编译c程序的隐含规则: '<n>.o'的目标的依赖目标会自动推导为'<n>.c' 其生成命令是'$(CC) -c $(CPPFLAGS) $(CFLAGS)'

    - 编译c++程序的隐含规则: '<n>.o'的目标的依赖目标会自动推导为'<n>.cc'或是'<n>.C' 并且其生成命令是 `$(CXX) -c $(CPPFLAGS) $(CFLAGS)` (建议使用'.cc'作为C++源文件的后缀 而不是'.C')


    - 链接Object文件的隐含规则
      - '<n>'目标依赖于'<n>.o' 通过运行C的编译器来运行链接程序生成(一般是'ld') 其生成命令是：`$(CC) $(LDFLAGS) <n>.o $(LOADLIBES) $(LDLIBS)` 该规则对于只有一个源文件的工程有效 同时也对多个Object文件(由不同的源文件生成)的也有效 例如
        ```bash
                x : y.o z.o
                并且 'x.c' 'y.c' 'z.c' 都存在时 隐含规则将执行如下命令：
                cc -c x.c -o x.o
                cc -c y.c -o y.o
                cc -c z.c -o z.o
                cc x.o y.o z.o -o x
                rm -f x.o
                rm -f y.o
                rm -f z.o
                如果没有一个源文件(如x.c)和目标名字(如x)相关联 最好写出自己的生成规则 不然隐含规则会报错
        ```

    - Yacc C程序时的隐含规则: '<n>.c'的依赖文件被自动推导为'n.y'(Yacc生成的文件) 其生成命令是:'$(YACC) $(YFALGS)'  (Yacc是一个语法分析器)


    - Lex C程序时的隐含规则: '<n>.c'的依赖文件被自动推导为'n.l'(Lex生成的文件) 其生成命令是:'$(LEX) $(LFALGS)'


    - 从C程序、Yacc文件或Lex文件创建Lint库的隐含规则: '<n>.ln' (lint生成的文件)的依赖文件被自动推导为'n.c' 其生成命令是:'$(LINT) $(LINTFALGS) $(CPPFLAGS) -i' 对于'<n>.y'和'<n>.l'也是同样规则

    - 隐含规则使用的变量
      - 在隐含规则中的命令中 基本上都是使用了一些预先设置的变量 可以在makefile中改变这些变量的值 或是在make的命令行中传入这些值 或是在环境变量中设置这些值 只要设置了这些特定的变量 就会对隐含规则起作用 也可以利用make的'-R'或'--no-builtin-variables'参数来取消所定义的变量对隐含规则的作用
        - 关于命令的变量
          - `AR`            函数库打包程序 默认命令是'ar'
          - `AS`            汇编程序 默认命令是'as'
          - `CC`            C编译器 默认命令是'cc'
          - `CXX`           C++编译器 默认命令是'g++'
          - `CO`            从RCS文件中扩展文件程序 默认命令是'co'
          - `CPP`           C预处理器 默认命令是'$(CC) -E'
          - `FC`            Fortran和Ratfor的编译器和预处理程序 默认命令是'f77'
          - `GET`           从SCCS文件中扩展文件的程序 默认命令是 'get'
          - `LEX`           Lex方法分析器程序 默认命令是'lex'
          - `PC`            Pascal语言编译程序 默认命令是'pc'
          - `YACC`          Yacc语法分析器程序 默认命令是'yacc'
          - `YACCR`         Yacc语法分析器 默认命令是'yacc -r'
          - `MAKEINFO`      转换Texinfo源文件(.texi) 到Info文件程序 默认命令是'makeinfo'
          - `TEX`           从TeX源文件创建TeX DVI文件的程序 默认命令是'tex'
          - `TEXI2DVI`      从Texinfo源文件创建军TeX DVI 文件的程序 默认命令是'texi2dvi'
          - `WEAVE`         转换Web到TeX的程序 默认命令是'weave'
          - `CWEAVE`        转换C Web 到 TeX的程序 默认命令是'cweave'
          - `TANGLE`        转换Web到Pascal语言的程序 默认命令是'tangle'
          - `CTANGLE`       转换C Web 到 C 默认命令是'ctangle'
          - `RM`            删除文件命令 默认命令是'rm -f'
        

        - 关于命令参数的变量
          - `ARFLAGS`       函数库打包程序AR命令的参数 默认值是'rv'
          - `ASFLAGS`       汇编语言编译器参数 (当明显地调用'.s'或'.S'文件时)
          - `CFLAGS`        C语言编译器参数
          - `CXXFLAGS`      C++语言编译器参数
          - `COFLAGS`       RCS命令参数
          - `CPPFLAGS`      C预处理器参数 (C 和 Fortran 编译器也会用到)
          - `FFLAGS`        Fortran语言编译器参数
          - `GFLAGS`        SCCS 'get'程序参数
          - `LDFLAGS`       链接器参数 (如'ld')
          - `LFLAGS`        Lex文法分析器参数
          - `PFLAGS`        Pascal语言编译器参数
          - `RFLAGS`        Ratfor 程序的Fortran 编译器参数
          - `YFLAGS`        Yacc语法分析器参数


    - 隐含规则链
      - 在默认情况下 对于中间目标 它和一般的目标有两个地方所不同: 
        - 第一个不同是除非中间的目标不存在 才会引发中间规则
        - 第二个不同的是 只要目标成功产生 那么 产生最终目标过程中 所产生的中间目标文件会被以'rm -f'删除

      - 通常 一个被makefile指定成目标或是依赖目标的文件不能被当作中介 但是可以明显地说明一个文件或是目标是中介目标 可以使用伪目标'.INTERMEDIATE'来强制声明(如：.INTERMEDIATE : mid )

      - 也可以阻止make自动删除中间目标 要做到这一点 可以使用伪目标'.SECONDARY'来强制声明(如：.SECONDARY : sec) 还可以把目标以模式的方式来指定(如：%.o)成伪目标'.PRECIOUS'的依赖目标 以保存被隐含规则所生成的中间文件

      - 在'隐含规则链'中 禁止同一个目标出现两次或两次以上 这样一来 就可防止在make自动推导时出现无限递归的情况

      - Make会优化一些特殊的隐含规则 而不生成中间文件 如 从文件'foo.c'生成目标程序'foo' 按道理 make会编译生成中间文件'foo.o' 然后链接成'foo' 但在实际情况下 这一动作可以被一条'cc'的命令完成(cc -o foo foo.c) 于是优化过的规则就不会生成中间文件
        

    - 定义模式规则
      - 可以使用模式规则来定义一个隐含规则 在规则中 目标的定义需要有"%"字符 "%"的意思是表示一个或多个任意字符 "%"的展开发生在变量和函数的展开之后 变量和函数的展开发生在make载入Makefile时 而模式规则中的"%"则发生在运行时

    - 模式规则介绍
      - 模式规则中 至少在规则的目标定义中要包含"%" 否则就是一般的规则 目标中的"%"定义表示对文件名的匹配 "%"表示长度任意的非空字符串
        - 例如："%.c"表示以".c"结尾的文件名(文件名的长度至少为3) 而"s.%.c"则表示以"s."开头，".c"结尾的文件名(文件名的长度至少为5)

      - 如果"%"定义在目标中 那么目标中的"%"的值决定了依赖目标中的"%"的值 也就是说 目标中的模式的"%"决定了依赖目标中"%"的样子 例如有一个模式规则: %.o : %.c ; <command ......> 其含义是 指出了怎么从所有的[.c]文件生成相应的[.o]文件的规则 如果要生成的目标是"a.o b.o"，那么"%c"就是"a.c b.c"。
        - 一旦依赖目标中的"%"模式被确定 那么make会被要求去匹配当前目录下所有的文件名 一旦找到 make就会执行规则下的命令 所以在模式规则中 目标可能会是多个的 如果有模式匹配出多个目标 make就会产生所有的模式目标 此时make关心的是依赖的文件名和生成目标的命令这两件事

    - 模式规则示例
      - 下面这个例子表示 把所有的[.c]文件都编译成[.o]文件
        ```bash
                %.o : %.c
                        $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
                # "$@"表示所有的目标的挨个值 "$<"表示了所有依赖目标的挨个值 这些奇怪的变量称为"自动化变量"

                # 下面的这个例子中有两个目标是模式的：
                %.tab.c %.tab.h: %.y
                        bison -d $<

                # 这条规则告诉make把所有的[.y]文件都以"bison -d <n>.y"执行 然后生成"<n>.tab.c"和"<n>.tab.h"文件(其中，"<n>"表示一个任意字符串)  如果执行程序"foo"依赖于文件"parse.tab.o"和"scan.o" 并且文件"scan.o"依赖于文件"parse.tab.h"  如果"parse.y"文件被更新了 那么根据上述的规则 "bison -d parse.y" 就会被执行一次 于是 "parse.tab.o"和"scan.o"的依赖文件就齐了
                # (假设"parse.tab.o"由"parse.tab.c"生成  "scan.o"由"scan.c"生成  "foo"由"parse.tab.o"和"scan.o"链接生成 而且foo和其[.o]文件的依赖关系也写好 那么 所有的目标都会得到满足)
        ```

      - 自动化变量
        - 把模式中所定义的一系列的文件自动地挨个取出 直至所有的符合模式的文件都取完了 这种自动化变量只应出现在规则的命令中

        - `$@`  表示规则中的目标文件集 在模式规则中 如果有多个目标 那么"$@"就是匹配于目标中模式定义的集合

        - `$%`  仅当目标是函数库文件 表示规则中的目标成员名
          - 例如 如果一个目标是"foo.a(bar.o)" 那么"$%"就是"bar.o" "$@"就是"foo.a" 如果目标不是函数库文件(Unix下是[.a] Windows下是[.lib]) 那么其值为空

        - `$<`  依赖目标中的第一个目标名字 如果依赖目标是以模式(即"%")定义的 那么"$<"将是符合模式的一系列的文件集 注意 其是一个一个取出来的

        - `$?`  所有比目标新的依赖目标的集合 以空格分隔

        - `$^`  所有的依赖目标的集合 以空格分隔 如果在依赖目标中有多个重复的 那个这个变量会去除重复的依赖目标 只保留一份

        - `$+`  这个变量很像"$^" 也是所有依赖目标的集合 只是它不去除重复的依赖目标

        - `$*`  这个变量表示目标模式中"%"及其之前的部分 如果目标是"dir/a.foo.b" 并且目标的模式是"a.%.b" 那么"$*"的值就是"dir/a.foo"
          - 这个变量对于构造有关联的文件名是比较有较 如果目标中没有模式的定义 那么"$*"也就不能被推导出 但是 如果目标文件的后缀是make所识别的 那么"$*"就是除了后缀的那一部分 例如：如果目标是"foo.c" 因为".c"是make所能识别的后缀名 所以"$*"的值就是"foo"
          - 这个特性是GNU make的 很有可能不兼容于其它版本的make 所以应该尽量避免使用"$*" 除非是在隐含规则或是静态模式中 如果目标中的后缀是make所不能识别的 那么"$*"就是空值

        - 如果希望只对更新过的依赖文件进行操作时 "$?"在显式规则中很有用 例如: 假设有一个函数库文件叫"lib" 其由其它几个object文件更新 那么把object文件打包的比较有效率的Makefile规则是:
```bash 
        lib : foo.o bar.o lose.o win.o
                ar r lib $?
```

        在上述所列出来的自动量变量中 四个变量($@、$<、$%、$*)在扩展时只会有一个文件 而另三个的值是一个文件列表
        这七个自动化变量还可以取得文件的目录名或是在当前目录下的符合模式的文件名 只需要搭配上"D"或"F"字样
        这是GNU make中老版本的特性 在新版本中 我们使用函数"dir"或"notdir"就可以做到了 "D"的含义就是Directory 就是目录 "F"的含义就是File 就是文件

        下面是对于上面的七个变量分别加上"D"或是"F"的含义：

        '$(@D)'  表示"$@"的目录部分 (不以斜杠作为结尾) 如果"$@"值是"dir/foo.o" 那么"$(@D)"就是"dir" 而如果"$@"中没有包含斜杠的话 其值就是"."(当前目录)

        '$(@F)'  表示"$@"的文件部分 如果"$@"值是"dir/foo.o" 那么"$(@F)"就是"foo.o" "$(@F)"相当于函数"$(notdir $@)"

        "$(*D)"
        "$(*F)"
        和上面所述的同理 也是取文件的目录部分和文件部分 对于上面的那个例子 "$(*D)"返回"dir" 而"$(*F)"返回"foo"

        "$(%D)"
        "$(%F)"
        分别表示了函数包文件成员的目录部分和文件部分 这对于形同"archive(member)"形式的目标中的"member"中包含了不同的目录很有用

        "$(<D)"
        "$(<F)"
        分别表示依赖文件的目录部分和文件部分

        "$(^D)"
        "$(^F)"
        分别表示所有依赖文件的目录部分和文件部分（无相同的）

        "$(+D)"
        "$(+F)"
        分别表示所有依赖文件的目录部分和文件部分（可以有相同的）

        "$(?D)"
        "$(?F)"
        分别表示被更新的依赖文件的目录部分和文件部分

        提醒一下的是 对于"$<" 为了避免产生不必要的麻烦 最好给$后面的那个特定字符都加上圆括号 比如 "$(<)"就要比"$<"要好一些
        还得要注意的是 这些变量只使用在规则的命令中 而且一般都是"显式规则"和"静态模式规则" 其在隐含规则中并没有意义
}

                模式的匹配:{
                        一般来说 一个目标的模式有一个有前缀或是后缀的"%" 或是没有前后缀 直接就是一个"%"
                        因为"%"代表一个或多个字符 所以在定义好了的模式中 我们把"%"所匹配的内容叫做"茎" 例如"%.c"所匹配的文件"test.c"中"test"就是"茎"
                        因为在目标和依赖目标中同时有"%"时 依赖目标的"茎"会传给目标 当做目标中的"茎"

                        当一个模式匹配包含有斜杠（实际也不经常包含）的文件时 那么在进行模式匹配时 目录部分会首先被移开 然后进行匹配 成功后再把目录加回去
                        在进行"茎"的传递时 我们需要知道这个步骤 例如有一个模式"e%t" 文件"src/eat"匹配于该模式 于是"src/a"就是其"茎"
                        如果这个模式定义在依赖目标中 而被依赖于这个模式的目标中又有个模式"c%r" 那么目标就是"src/car"("茎"被传递)
                }

                重载内建隐含规则:{
                        可以重载内建的隐含规则(或是定义一个全新的) 可以重新构造和内建隐含规则不同的命令 如：

                        %.o : %.c
                                $(CC) -c $(CPPFLAGS) $(CFLAGS) -D$(date)

                        可以取消内建的隐含规则 只要不在后面写命令就行 如：

                        %.o : %.s

                        同样也可以重新定义一个全新的隐含规则 其在隐含规则中的位置取决于在哪里写下这个规则 朝前的位置就靠前
                }

                老式风格的"后缀规则" :{
                        后缀规则是一个比较老式的定义隐含规则的方法 后缀规则会被模式规则逐步地取代 因为模式规则更强更清晰 为了和老版本的Makefile兼容 GNU make同样兼容于这些东西
                        后缀规则有两种方式："双后缀"和"单后缀"

                        双后缀规则定义了一对后缀：目标文件的后缀和依赖目标（源文件）的后缀 如".c.o"相当于"%o : %c"
                        单后缀规则只定义一个后缀: 也就是源文件的后缀 如".c"相当于"% : %.c"

                        后缀规则中所定义的后缀应该是make所认识的 如果一个后缀是make所认识的 那么这个规则就是单后缀规则 而如果两个连在一起的后缀都被make所认识 那就是双后缀规则
                        例如：".c"和".o"都是make所知道 因而 如果定义了一个规则是".c.o"那么其就是双后缀规则 意义就是".c"是源文件的后缀 ".o"是目标文件的后缀 如下示例：

                                .c.o:
                                        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

                        后缀规则不允许任何的依赖文件 如果有依赖文件的话 那就不是后缀规则 那些后缀统统被认为是文件名 如：

                                .c.o: foo.h
                                        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

                        这个例子就是说 文件".c.o"依赖于文件"foo.h" 而不是我们想要的这样：

                                %.o: %.c foo.h
                                        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

                        后缀规则中 如果没有命令 那是毫无意义的 因为他也不会移去内建的隐含规则

                        要让make知道一些特定的后缀 可以使用伪目标".SUFFIXES"来定义或是删除，如：' .SUFFIXES: .hack .win ' 把后缀.hack和.win加入后缀列表中的末尾

                        .SUFFIXES:              # 删除默认的后缀
                        .SUFFIXES: .c .o .h     # 定义自己的后缀

                        先清楚默认后缀 后定义自己的后缀列表

                        make的参数"-r"或"-no-builtin-rules"也会使用得默认的后缀列表为空
                        而变量"SUFFIXE"被用来定义默认的后缀列表 你可以用".SUFFIXES"来改变后缀列表 但请不要改变变量"SUFFIXE"的值
                }

                隐含规则搜索算法:{
                        假设有一个目标叫' T ' 下面是搜索目标T的规则的算法 如果目标是"archive(member)"的函数库文件模式 那么这个算法会被运行两次 第一次是找目标T
                        如果没有找到的话 那么进入第二次 第二次会把"member"当作T来搜索

                        1、把T的目录部分分离出来 叫D 而剩余部分叫N (如: 如果T是"src/foo.o" 那么D就是"src/" N就是"foo.o")

                        2、创建所有匹配于T或是N的模式规则列表

                        3、如果在模式规则列表中有匹配所有文件的模式 如"%" 那么从列表中移除其它的模式

                        4、移除列表中没有命令的规则

                        5、对于第一个在列表中的模式规则:
                                1 推导其"茎"S S应该是T或是N匹配于模式中"%"非空的部分
                                2 计算依赖文件 把依赖文件中的"%"都替换成"茎"S 如果目标模式中没有包含斜框字符 而把D加在第一个依赖文件的开头
                                3 测试是否所有的依赖文件都存在或是理当存在 (如果有一个文件被定义成另外一个规则的目标文件 或者是一个显式规则的依赖文件 那么这个文件就叫"理当存在")
                                4 如果所有的依赖文件存在或是理当存在 或是就没有依赖文件 那么这条规则将被采用 退出该算法

                        6、如果经过第5步 没有模式规则被找到 那么就做更进一步的搜索 对于存在于列表中的第一个模式规则：
                                1 如果规则是终止规则 那就忽略它 继续下一条模式规则
                                2 计算依赖文件 同第5步
                                3 测试所有的依赖文件是否存在或是理当存在
                                4 对于不存在的依赖文件 递归调用这个算法查找他是否可以被隐含规则找到
                                5 如果所有的依赖文件存在或是理当存在 或是就根本没有依赖文件 那么这条规则被采用 退出该算法

                        7、如果没有隐含规则可以使用 查看".DEFAULT"规则 如果有 采用 把".DEFAULT"的命令给T使用

                        一旦规则被找到 就会执行其相当的命令 而此时自动化变量的值才会生成
                }
        }
}

- **使用make更新库函数**:{
                函数库文件也就是对Object文件(程序编译的中间文件)的打包文件 一般是由命令"ar"来完成打包工作

                函数库文件的成员:{
                        一个函数库文件由多个文件组成 可以以如下格式指定函数库文件及其组成：

                                archive(member)

                        这个不是一个命令 而一个目标和依赖的定义 一般来说 这种用法基本上就是为了"ar"命令来服务的 如：

                                foolib(hack.o) : hack.o
                                        ar cr foolib hack.o

                        如果要指定多个member 那就以空格分开 如: foolib(hack.o kludge.o) 其等价于: foolib(hack.o) foolib(kludge.o)

                        还可以使用Shell的文件通配符来定义 如 foolib(*.o)
                }

                函数库成员的隐含规则:{
                        当make搜索一个目标的隐含规则时 一个特殊的特性是 如果这个目标是"a(m)"形式的 其会把目标变成"(m)"
                        于是 如果成员是"%.o"的模式定义 并且如果使用"make foo.a(bar.o)"的形式调用Makefile时 隐含规则会去找"bar.o"的规则
                        如果没有定义bar.o的规则 那么内建隐含规则生效 make会去找bar.c文件来生成bar.o 如果找得到的话 make执行的命令大致如下:

                                cc -c bar.c -o bar.o
                                ar r foo.a bar.o
                                rm -f bar.o

                        还有一个变量要注意的是"$%" 这是专属函数库文件的自动化变量
                }

                函数库文件的后缀规则:{
                        可以使用"后缀规则"和"隐含规则"来生成函数库打包文件 如：

                        .c.a:
                                $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
                                $(AR) r $@ $*.o
                                $(RM) $*.o

                        其等效于：

                        (%.o) : %.c
                                $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
                                $(AR) r $@ $*.o
                                $(RM) $*.o
                }

                注意事项:{
                        在进行函数库打包文件生成时 请小心使用make的并行机制("-j"参数) 如果多个ar命令在同一时间运行在同一个函数库打包文件上 就很有可能损坏这个函数库文件
                }
}



---
---


Makefile基础知识：
                最简单的Makefile
                        hello：hello.c
                                gcc hello.c - o hello  	# 开头必须为一个Tab  不是一个空格
                        
                        规则：一个Makefile文件由一条一条的规则构成 一条规则结构如下
                                target … (目标) : prerequisites … (依赖)
                                        recipe(方法)
                                        …
                                        …
                
                Makefile文件的命名与指定
                        make会自动查找makefile文件 查找顺序为GNUmakefile -> makefile -> Makefile（最常用）
                        手动指定文件名：
                                make -f mkfile	# make -f <filename>
                                make --file=mkfile		#make --file=<filename>
                                # 手动指定后 make就会使用指定的文件 即使有makefile等文件也不会自动使用

                Makefile文件内容组成
                        一个Makefile文件通常由五种类型的内容组成：显式规则、隐式规则、变量定义、指令和注释
                        显式规则：
                                显式指明何时以及如何生成或更新目标文件 显示规则包括目标、依赖和更新方法三个部分
                        隐式规则：
                                根据文件自动推导如何从依赖生成或更新目标文件
                        
                目标
                        Makefile中会有很多目标 但最终目标只有一个 其他所有内容都是为这个最终目标服务的 写Makefile时 先写出最终目标 再依次解决总目标的依赖
                        一般情况下 第一条规则中的目标会被确立为最终目标 第一条规则默认会被make执行
                        通常来说目标是一个文件 一条规则的目的就是生成或更新目标文件
                        make会根据目标文件和依赖文件最后修改时间判断是否需要执行更新目标文件的方法 如果目标文件不存在或目标文件最后修改时间早于其中一个依赖文件最后修改时间 则重新执行更新目标文件的方法 否则不会执行
                        除了最终目标对应的更新方法默认会执行外 如果Makefile中一个目标不是其他目标的依赖 那么这个目标对应的规则不会自动执行 需要手动指定 方法为
                                make <target>      #如 make clean
                        可以使用.DEFAULT_GOAL来修改默认最终目标
                                        .DEFAULT_GOAL = main
                                                all:
                                                        @echo all
                                                main:
                                                        @echo main
                依赖
                        依赖类型
                                普通依赖
                                        如果任何一个依赖文件修改时间比目标晚 那么就重新生成目标文件
                                order-only依赖
                                        依赖文件不存在时 会执行对应的方法生成 但依赖文件更新并不会导致目标文件的更新 如果目标文件已存在 order-only依赖中的文件即使修改时间比目标晚 目标文件也不会更新
                                        target：normalfile ｜ order-onlyfile

                更新方法
                        target … (目标)：prerequisites …（依赖）
                                        recipe（方法）
                                        …	
                        执行终端
                                更新方法实际就是一些shell指令 通常以Tab开头 或直接放在目标-依赖列表后面 用分号隔开 这些指令都需要交给shell执行 所以需要符合shell语法 默认使用的shell是sh 默认的执行方式为一条指令重新调用一个shell进程来执行 有时为了提高性能或其他原因 想让这个目标的所有指令都在同一进程中执行 可以在makefile中添加  .ONESHELL:  这样所有指令都会在同一次shell调用中执行
                        
                        shell语句回显问题
                                通常make在执行一条shell语句前都会先打印这条语句 如果不想打印 可以在语句开头在@
                                @echo hello
                                @g++ -o hello hello.cpp
                                也可以使用 .SILENT 来指定哪些目标的更新方法指令不用打印
                                .SILENT: main all
                        
                        错误处理
                                如果一条规则当中包含多条shell指令 每条指令执行完之后make都会检查返回状态 如果返回状态是0 则执行成功 继续执行下一条指令 直到最后一条指令执行完成之后 一条规则也就结束了 如果过程中发生了错误 即某一条指令的返回值不是0 那么make就会终止当前规则中剩下的shell指令	如果希望make忽视错误继续下一条指令 在指令开头可以加 - 来忽略错误
                                clean：
                                        -rm main.o hello.o
                                        -rm main
                变量应用
                        Makefile中的变量有点类似c语言中的宏定义 即 用一个名称表示一串文本 但与c语言的宏定义不同 Makefile的变量值是可以改变的 变量定义之后可以在目标、依赖、方法等Makefile文件的任意地方进行引用
                        变量可以用来表示：
                                文件名序列
                                编译选项
                                需要运行的程序
                                需要进行操作的路径
                        变量定义与引用方式
                                定义方式
                                        # <变量名> = <变量值>  <变量名> ：= <变量值>  <变量名> ：：= <变量值>
                                        files = main.cpp hello.cpp
                                        objects := main.o hello.o
                                        var3 ::= main.o
                                使用方式
                                        # $(变量名)  或 ${变量名}
                                        main.o : $(files)  #或 main.o : ${files}
                                        变量名只有一个字符时可以不用括号 例如$a、$b 但不建议这样使用
                Makefile读取过程
                        make分两个阶段来执行Makefile 第一阶段（读取阶段）：
                                读取Makefile文件的所有内容
                                根据Makefile的内容在程序内建立起变量
                                在程序内构建起显式规则、隐式规则
                                建立目标和依赖之间的依赖图
                        第二阶段（目标更新阶段）：
                                用第一阶段构建起来的数据确定哪个目标需要更新然后执行对应的更新方法  变量和数据的展开如果发生在第一阶段 就称作立即展开 否则称为延迟展开 立即展开的变量或函数在第一个阶段 延迟展开的变量或函数在将会用到的时候才展开
                                显式规则中 目标和依赖部分都是立即展开 在更新方法中延迟展开

                变量赋值
                        递归展开赋值（延迟展开）
                                第一种方式就是直接使用 =  这种方式如果赋值的时候右边是其他变量引用或者函数调用之类的 将不会做处理 直接保留原样 在使用到该变量的时候再来进行处理得到变量值（Makefile执行的第二个阶段在进行变量展开得到变量值）
                                bar2 = Thisisbar2no1
                                foo = $(bar)
                                foo2 = $(bar2)

                                all:
                                        @echo $(foo)			# Huh?
                                        @echo $(foo2)		# thisisbar2no.2
                                        @echo $(ugh)        	# Huh?

                                bar = $(ugh)
                                ugh = Huh?
                                bar2 = thisisbar2no.2

                        简单赋值（立即展开）
                                简单赋值使用 := 或 ::=  这种方式如果等号右边是其他变量或者引用的话 将会在赋值的时候就进行处理得到变量值（Makefile执行的第一个阶段进行变量展开）
                                bar2 := Thisisbar2no1
                                foo := $(bar)
                                foo2 := $(bar2)

                                all:
                                        @echo $(foo)			# 
                                        @echo $(foo2)		# Thisisbar2no1
                                        @echo $(ugh)        	# 

                                bar = $(ugh)
                                ugh = Huh?
                                bar2 = thisisbar2no.2

                        条件赋值
                                条件赋值使用 ?=  如果变量已经定义过了 即已经有值 那么就保持原来的值 如果没有 那就把右边的值赋给变量
                                var1 = 100
                                var1 ？= 200
                                
                                all:
                                        @echo $(var1)      # 100

                        追加
                                使用 += 在变量已有的基础上追加内容
                                files = main.cpp
                                files += hello.cpp

                                all:
                                        @echo $(files)		# main.cpp hello.cpp

                        Shell运行赋值
                                使用 != 运行一个Shell指令后将返回值赋给一个变量
                                gcc_version != gcc --version
                                files != ls .        # ls . 是一个shell命令 列出当前路径下的文件

                        多行变量
                                变量值有多行 多用于定义shell指令
                                define varable_name
                                        // 变量内容
                                endef
                                
                                define varable_name :=
                                endef
                                
                                define varable_name +=
                                endef

                        取消变量定义
                                undefine varable_name

                        环境变量的使用
                                all:
                                        @echo $(USERNAME)
                                        @echo $(JAVA_HOME)
                                        @echo $(SystemRoot)

                        变量替换引用
                                语法 $(var:a=b) 即 将变量var的值当中每一项结尾的a替换为b 
                                files = main.cpp hello.cpp
                                objs := $(files:.cpp=.o) 	# main.o hello.o
                                或
                                obis := $(files:%.cpp=%.o)
                                
                        变量覆盖
                                所有在Makefile中的变量 都可以在执行make时通过指定参数的方式进行覆盖
                                若不想被覆盖 则加上 override
                                override Demo := ThisIsMadefile
                                all:
                                        @echo $(Demo)

                        绑定目标的变量
                                Madefile中的变量一般是全局变量 也就是说定义之后在Makefile的任意位置都可以使用 但也可以将变量指定在某个目标的范围内 这样这个变量就只能在这个目标对应的规则里面使用
                                
                        自动变量
                                $@  本条规则的目标名、若目标是归档文件的成员则为归档文件名、在多目标的模式规则中则为导致本条规则方法执行的那个目标名
                                $<  	本条规则的第一个依赖名称
                                $?  	依赖中修改时间晚于目标文件修改时间的所有文件名 以空格隔开
                                $^	所有依赖文件名 文件名不会重复 不包含order-only依赖
                                $+	表示所有依赖文件名 包含重复文件名 不包含order-only依赖
                                $|  	表示所有order-only依赖文件名
                                $*	目标文件名的主干部分（不包含后缀名）
                                $%	如果目标不是归档文件 则为空 如果目标是归档文件成员 则对应的成员文件名

                多目标与多规则
                        显式规则中一条规则可以有多个目标 多个目标可以是相互独立的目标 也可以是组合目标 用写法来区分
                        独立多目标
                                相互独立的多个目标与依赖之间直接用 ：  常用的两种情况 
                                        只需要写目标和依赖 不需要写方法时
                                                block.o input.o sense.o : common.h
                                        这写法等价于
                                                block.o : common.h
                                                input.o : common.h
                                                sense.o : common.h
                                        生成（更新）目标的方法写法一样的 只是依赖与目标不一样时 
                                                

                        组合多目标
                                多目标与依赖之前用 &:  这样的多个目标为组合目标  与独立多目标的区别在于 独立多目标每个目标多更新需要单独调用一次更新方法 而组合多目标调用一次方法将更新所有目标
                                        block.o input.o scene.o &: block.cpp input.cpp scene.cpp common.cpp
                                                g++ -c block.cpp
                                                g++ -c input.cpp
                                                g++ -c scene.cpp
                                所有目标多更新方法都写到其中 每次更新只会调用一次

                        多规则
                                如果同一个目标 多次定义了方法 那么编译时将会发生覆盖 最终只会实现最后一次方法 其依赖将会被合并

                静态模式
                        独立多目标可以简化Makefile的书写 但是不利于将各个目标的依赖分开 让目标文件根据各自的依赖进行更新 静态模式可以在一定程度上改进依赖分开问题 静态模式就是用 % 进行文件匹配来推导出对应的依赖
                        target … : target-pattern (目标模式) : prereq-patterns (依赖模式) …
                                recipe
                                …
                        例如
                                block.o : %.o : %.cpp %.h
                                        g++ -c $<
                        block.o为目标 %.o为目标模式 %.cpp %.h 为依赖模式  对这一条规则  %.o代表的是目标文件block.o 所以这里的%匹配的是block 因此 %.cpp 表示block.cpp  %.h代表block.h	所以block.o : %.o : %.cpp %.h表示的意思同下面这种写法
                                block.o : block.cpp block.h
                        自动推导出block.o 依赖block.cpp 和block.h
                        另外 $< 表示目标的第一个依赖 在这条规则中 $< 表示 block.cpp

                指定依赖搜索路径
                        make默认在Makefile文件所在目录下查找依赖文件 如果找不到 就会报错 这时候就需要手动指定搜索路径 用VPATH变量或vpath指令					VPATH用法如下
                                VPATH = dir1:dir2:dir3 …
                                例如
                                        VPATH = include:src
                        多个目录之间冒号隔开 这时make会在VPATH指定的这些目录里面查找依赖文件
                        vpath指令用法
                                vpath比VPATH使用更灵活 可以指定某个类型的文件在哪个目录搜索
                                vpath %.h include   # .h 文件在include目录下查找
                                vpath %.h include:headers 	 # .h文件在include或headers文件下查找
                                vpath % src		#所有文件都在src下查找
                                vpath hello.cpp src	# hello.cpp 文件在src查找

                条件判断
                        使用条件指令可以让make执行或略过Makefile文件中的一些部分
                        ifdef判断一个变量是否已定义
                                ifdef Win
                                        0S = Windows
                                else ifdef Mac
                                        OS = MacOS
                                else
                                        OS = Linux
                                endif
                        ifndef判断一个变量是否没被定义
                                ifndef FLAGS
                                        FLAGS = -finput-charset=utf-8
                                endif
                        ifeq判断两个值是否相等
                                version = 3.0
                                ifeq ($(version), 1.0)		# ifeq 后面一定要空格
                                        msg := 请更新版本
                                else ifeq （$(version), 3.0）
                                        msg := 版本过新
                                else
                                        msg := 版本可以用
                                endif
                                或用下面的写法
                                ifeq “$(version)” “1.0”
                                …
                                或
                                ifeq ‘$(version)’ ‘1.0’
                                …
                                或 
                                ifeq ‘$(version)’ “1.0”

                文本处理函数
                        调用函数的写法
                        $(function arguments) 或 ${function arguments}
                        $(function arg1,$(arg2),arg3…)     #参数之间不要空格
                        字符替换与分析
                                subst 文本替换函数 返回替换后的文本
                                        $(subs target,replacement,text)    #用replacement替换text文本中的target
                                patsubst  模式替换 返回替换后的文本
                                        $(patsubst pattern,replacement,text)    #

                                strip 去除字符串头部和尾部的空格 中间如果连续有多个空格 则用一个空格替换 返回去除空格后的文本
                                $(strip string)   	# string 是需要去除空格的字符串

                                findstring	查找字符串 如果找到了 则返回对应的字符串 如果没找到 则返回空串
                                $(findstring find,string)	#find 需要查找的字符串     string 用来查找的内容

                                filter 从文本中筛选出符合模式的内容并返回
                                $(filter pattern …,text)	#pattern 模式 可以有多个 用空格隔开  text用来筛选文本 多项内容需要空格隔开  否则只当一项来处理
                                filter-out 与filter相反 过滤掉符合模式的 返回剩下内容
                                $(filter-out pattern …,text)   # 同上
                                
                                sort 将文本内的各项按字典顺序排列 并且移除重复项
                                $(sort list)   # 需要排序内容

                                word	用于返回文本中第n个单词
                                $(word n, text)	# n 第n个单词 从1开始 如果n大于总单词数 则返回空串   text 待处理文本

                                wordlist	用于返回文本指定范围内的单词列表
                                $(wordlist started,text)	#start 起始位置 如果大于单词总数 则返回空串  end结束位置 如果大于单词总数 则返回起始位置之后全部

                                words	返回文本中单词数
                                $(words text)		# text 需要处理的文本

                                firstword	返回第一个单词
                                $(firstword text)

                                lastword		返回最后一个单词
                                $(lastword text)

                文件名处理函数
                                dir	返回文件目录
                                $(dir files)	# files 需要返回目录的文件名  可以有多个 用空格隔开

                                notdir	返回除目录部分的文件名
                                $(noter files)		#files 需要返回文件列表 可以有多个 用空格隔开

                                suffix	返回文件后缀名 如果没有后缀 返回空
                                $(suffix files) 	# files 需要返回后缀的文件名 可以有多个 用空格隔开

                                basename	返回文件名除后缀的部分
                                $(basename files)		#files 需要返回的文件名 可以有多个 用空格隔开

                                addsuffix	给文件名添加后缀
                                $(addsuffix suffix, files) 	# suffix 需要添加的后缀  files 需要添加后缀的文件名 可以有多个 用空格隔开

                                addprefix	给文件名添加前缀
                                $(addprefix prefix,files) 	#prefix 需要添加的前缀  files 需要添加前缀的文件名 可以有多个 用空格隔开

                                join 将两个列表中的内容一对一连接 如果两个列表内容数量不想等 则多出来的部分原样返回
                                $(join list1,list2)		# list1 第一个列表   list2 需要连接的第二个列表

                                wildcard		返回符合通配符的文件列表
                                $(wildcard pattern)	# pattern 通配符

                                realpath		返回文件的绝对路径
                                $(realpath files)		# files  需要返回绝对路径的文件 可以有多个 用空格隔开

                                abspath		返回绝对路径 用法同realpath 如果一个文件名不存在 realpath不会返回内容 abspath则会返回一个当前文件夹下的绝对路径
                                $(abspath files)


                条件函数
                                if  条件判断 如果条件展开不是空串 则返回真的部分 否则返回假的部分
                                $(if condition,then-part,else-part)  # condition 条件部分  then-part 条件为真时执行的部分   else-part 条件为假时执行的部分 如果省略则为假时返回空串 
                                or	返回条件中第一个不为空的部分 
                                $(or condition,condition2,condition3…)

                                and		如果条件中有一个为空串 则返回空 如果全都不为空 则返回最后一个条件
                                $(and condition1,condition2,condition3…)

                                intcmp 	比较两个整数大小 并返回对应操作结果
                                $(intcmp lhs,rhs,lt-part,eq-part,gt-part)    # lhs 第一个数  rhs 第二个数 lt-part   lhs<rhs 时执行   相等 执行eq-part  大于 执行gt-part

                                file	读写文件
                                $(file op filename,text)	# op操作  >覆盖    >> 追加     < 读   filename 需要操作的文件名。 text 写入的文本内容 读取不需要该参数

                                foreach 		对一列用空格隔开的字符序列中每一项进行处理 并返回处理后的列表
                                $(foreach each,list,process)     # each  代表list中的每一项。 list 待处理字符串序列 用空格隔开 process 需进行的处理

                                call		将一些复杂的表达式写成一个变量 用call可以像调用函数一样进行调用 类似于编程语言中的自定义函数 在函数中可以用$(n)来访问第n个参数
                                $(call funcname,param1,param2,…)   # funcname 自定义函数名  …参数 至少一个 可有多个 用 ，隔开

                                value	对于不是立即展开的变量 可以查看变量的原始定义 对于立即展开的变量 直接返回变量值
                                $(value variable)

                                origin	查看一个变量定义来源
                                $(origin variable)

                                flavor	查看一个变量的赋值方式
                                $(flavor variable)

                                eval		将一段文本生成Makefile的内容
                                $(eval text)

                                shell	用于执行shell命令
                                $(shell zhiling)

                                let		将一个字符串序列中的项拆开放入多个变量中 并对各个变量进行操作
                                $(let var1 var2 …,[list],proc)    #var 变量 可以有多个 用，隔开   list 待处理字符串 各项用空格隔开  proc 对变量进行的操作 结果为let返回值
                                将list中的值依次一项一项放到var中 如果var的个数多于list项数 剩下的则为空串

                                error	提示错误信息并终止make执行
                                $(error text)		# text 提示信息
                        
                                warning	提示警告信息 make不会终止
                                $(warning text)

                                info		输出一些信息
                                $(info text）
                                
自动推导与隐式规则
        Makefile中有一些生成目标文件的规则使用频率非常高 比如由.c或.cpp文件编译成.o文件 这样的规则在make中可以自动推导 所以可以不用明确写出来 这样的规则称为隐式规则
        一些make预定义的规则
                c语言编译
                        从.c到.o
                                $(CC) $(CPPFLAGS) $(CFLAGS) -c
                C++编译
                        从.cpp到.o
                                $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c
                链接
                        由.o文件链接到可执行文件
                                $(CC) $(LDFLAGS) *.o $(LOADLIBES) $(LDLIBS)

        隐式规则中常用的一些变量
                CC		编译c语言的程序 默认为 ‘cc’
                CXX		编译c++的程序 默认为 ‘g++’
                AR		归档程序 默认为 ar
                CPP		c语言预处理程序 默认为 $(CC) -E
                RM		删除文件的程序 默认为 rm -f
                CFLAGS	传递给c编译器的一些选项 如 -O2 -linclude
                CXXFLAGS	传递给c++编译器的一些选项 如 -std=c++ 11 -fexec-charset=GBK
                CPPFLAGS	c语言预处理的一些选项
                LDFLAGS		链接选项 如 -L
                LDLIBS		链接需要用到的库 如-lkernel32 -luser32 -lgdi32
                                        
makefile语法：
                目的：依赖
                        通过依赖生成目的的命令

                        $@  代表目的
                        *	通配符

                        %.o : %.c
                                gcc	-c $< -o $@
                        $<  代表依次匹配
							
						



