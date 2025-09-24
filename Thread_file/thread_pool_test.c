#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/** data 来自g_thread_pool_push
 *  user_data 来自g_thread_pool_new
 */
void task_func(gpointer data, gpointer user_data)
{
    int task_num = *(int*)data;
    free(data);
    printf("开始执行%d任务\n",task_num);
    sleep(task_num);
    printf("%d任务执行完成\n",task_num);

}

int main(int argc, char const *argv[])
{
    // 创建线程池
    /**
     * GThreadPool * g_thread_pool_new(GFunc func, gpointer user_data, gint max_threads, gboolean exclusive, GError **error);
     * @brief 线程池创建函数
     * @param func: 线程执行的函数  类型为void （*）（gpointer data, gpointer user_data）
     *        user_data : 传递给线程函数的用户数据
     *        max_threads: 线程池最大线程数。-1表示无限制
     *        exclusive: 是否独占线程池（TRUE 表示不允许其他任务共享）
     *        error: 错误信息指针
     * @return 返回线程池对象
     */
    GThreadPool *pool = g_thread_pool_new(task_func,NULL,5,TRUE,NULL);

    // 向线程池中添加任务
    for (size_t i = 0; i < 10; i++)
    {
        // 每一个提交任务的编号
        int *tmp = malloc(sizeof(int));
        *tmp = i + 1;
        /**
         * gboolean g_thread_pool_push(GThreadPool *pool, gpointer data, GError **error);
         * @brief 向线程池添加任务
         * @param pool: 通过g_thread_pool_new创建的线程池对象
         *        data: 传递给任务函数的数据
         *        error: 错误对象指针
         * @return TRUE-成功   FALSE-失败
         */
        g_thread_pool_push(pool, tmp,NULL);
    }
    
    /**
     * void g_thread_pool_free(GThreadPool *pool,gboolean immediate, gboolean wait);
     * @brief 释放线程池资源函数
     * @param pool: 要释放的线程池指针
     *        immediate: 是否立即停止线程
     *        wait: 是否等待任务完成
     * @return
     */
    g_thread_pool_free(pool,FALSE,TRUE);
    return 0;
}
