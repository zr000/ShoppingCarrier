# thread
> 位于头文件&lt;threa&gt;中, #include&lt;thread&gt;
## 类 thread
> 提供了三个构造函数，thread(), thread(thread&&)和thread&lt;Fun, ...Args&gt;(Func, ...)
> 拷贝构造函数声明成了delete，无法复制一个线程
> 成员函数：
>     void swap(thread&) 交换两个线程类
>     bool joinable()
>     void join()
>     void detach()      分离线程对象和线程句柄，让线程单独执行
>     id   get_id()
>     native_handle_type native_handle()
> 静态成员
>     static unsigned hardware_concurrency()  获取线程数，这里是获取的逻辑线程

## 头文件 thread
> void swap(thread& 1, thread& 2)
> operator &lt;&lt;
> namespace this_thread: sleep_for(): 休眠一段时间     sleep_until(): 一直休眠到某个时间
