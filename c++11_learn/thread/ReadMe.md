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
> namespace this_thread: sleep_for(): 休眠一段时间     sleep_until(): 一直休眠到某个时间。
> 一个thread对象表示一个系统资源

## thread的身份
> thread::id表示线程的唯一身份，可以为{}，表示线程已经结束或者还未开始

## thread生命周期
thread对象在析构时调用terminate结束线程，如果要使线程的生命周期长与对象，需要调用detach(),把对象和线程分离，当给线程传递了一个临时变量时，要非常小心的detach，如果线程生命周期比临时对象长，代码不会保错，但线程会改写其他使用这个地址的变量，让程序每次执行的返回都不相同
线程对象可以调用join，让调用者等待线程执行结束
yield()函数可以释放cpu资源，让其他线程有机会执行，相当于sleep(0)

## 线程同步
> mutex
一个mutex对象表示对资源的互斥访问，如果线程去获取一个已经被获取的mutex，线程会阻塞
> recursive_mutex，可以在同一个线程中重复获取的互斥量
> timed_mutex，在指定时长内尝试获互斥量，相当于WaitforSingleObject里的timeout
> recursive_timed_mutex

> lock_guard&lt;M&gt;，mutex的守卫模板，可以自动枷锁解锁
> unique_lock&lt;M&gt;
