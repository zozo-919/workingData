CC := gcc

system_test:system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test:fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


execve:execve_test.c
	-$(CC) -o $@ $^

execve_test:execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_execve:fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

waitpid:waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

procces:procces_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe:unnamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ test_test_test_test
	-rm ./$@


fifo_write:fifo_write_test.c
	-$(CC) -o $@ $^

fifo_read:fifo_read_test.c
	-$(CC) -o $@ $^

shared_memory:shared_memory.c
	-$(CC) -o $@ $^
	-./$@ 
	-rm ./$@

# macos系统不支持POSIX消息队列
# parent_child_mq_test:parent_child_mq_test.c
# 	-$(CC) -o $@ $^ 
# 	-./$@ 
# 	-rm ./$@

# producer_test:producer_test.c
# 	-$(CC) -o $@ $^ 

# consumer_test:consumer_test.c
# 	-$(CC) -o $@ $^ 


signal_test:signal_test.c
	-$(CC) -o $@ $^
	-./$@ 
	-rm ./$@