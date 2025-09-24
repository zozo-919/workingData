CC:=gcc

Thread_create:Thread_create_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

Pthread_join_exit:Pthread_join_exit_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_detach:pthread_detach_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel:pthread_cancel_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

# 在macos中执行有点问题
pthread_cancel_async:pthread_cancel_async_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

race_condition:race_condition_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_write_unlock:rwlock_write_unlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test:rwlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


rwlock_write_hungry:rwlock_write_hungry_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_lock_condition_var:pthread_lock_condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

# 本例无法编译 macos系统未提供sem_init函数的实现
# unnamed_sem_bin_thread:unnamed_sem_bin_thread.c
# 	-$(CC) -o $@ $^
# 	-./$@
# 	-rm ./$@


named_sem_bin:named_sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

thread_pool_test:thread_pool_test.c
	-$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`
	-./$@
	-rm ./$@