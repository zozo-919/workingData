#重新命名编译器的名字 
CC:=gcc

# $@ 表示当前目标文件的名称 这里代表fopen  $^ 代表所有依赖的文件 -是忽略错误
fopen:fopen_test.c
# -$(CC) -o $@ $^ 等价于 -gcc -o fopen fopen_test.c
	-$(CC) -o $@ $^
# -./$@ 等价于 -./fopen 即执行生成的可执行文件
	-./$@
# -rm ./$@ 等价于 -rm ./fopen 
	-rm ./$@

fclose:fclose_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fputc:fputc_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputs:fputs_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fprintf:fprintf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fgetc:fgetc_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fgets:fgets_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fscanf:fscanf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


stdinOutErr:stdin_out_err_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unistdTest:unistd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

systemCall:system_call_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fread:fread_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fwrite:fwrite_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@