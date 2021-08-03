#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <future>

namespace PublicUtils
{
class ThreadPoolImpl;
class ThreadPool
{
    using Task = std::function<void()>;

public:
    ThreadPool(size_t coreSize = 2, bool autoExpansion = false, size_t maxSize = std::thread::hardware_concurrency());

    ~ThreadPool();

    void SetName(const std::string & name);

    void SetTaskBlockQueueSize(size_t size);

    void Start();

    //如果不需要自己捕捉异常，建议使用CommitTask，内部会自动捕捉异常并记录
    void CommitTask(const Task& task);

    void CommitTask(const std::shared_ptr<Task>& task);

    //如果需要自己捕捉异常，建议使用Commit，可以通过返回的future获取异常
    template<class F, class... Args>
    auto Commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
    {
        using ResType = decltype(f(args...));// 函数f的返回值类型
        auto task = std::make_shared<std::packaged_task<ResType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto c = [task]()
        {
            (*task)();
        };
        CommitTask(c);
        std::future<ResType> future = task->get_future();
        return future;
    }
    // 关闭线程池，并等待结束
    void Shutdown();
    //清空线程池的任务等待队列
    void Clear();
    void SetExceptionCallcack(const std::function<void(const std::exception & exception)> & callback);
private:
    std::unique_ptr<ThreadPoolImpl> _impl;
};
typedef ThreadPool ThreadPoolUtils;
}
