#	Makefile 内容组成
#	<目标名称>:<前置依赖>
#		/t<需要执行的命令>

#定义变量 objects
objects := ballclock.o

#放在第一个的是默认目标
#目标是编译出ball文件  依赖是ballclock.o
#编译命令是 gcc ballclock.o -o ball
# ball:ballclock.o
# 	gcc ballclock.o -o ball
#与上面等价
ball:$(objects)
	gcc $(objects) -o ball


#目标是ballclock.o 依赖是ballclock.c ballclock.h
#编译命令是 gcc -c ballclock.c 
# ballclock.o:ballclock.c ballclock.h
# 	gcc -c ballclock.c 
#上下等价
# $(objects):ballclock.c ballclock.h
# 	gcc -c ballclock.c
#自动推导
$(objects):ballclock.h

#声明伪目标
.PHONY : clean

clean:
#	rm ballclock.o ball
#	rm $(objects) ball
#忽略错误 rm前面加-
	-rm $(objects) ball






