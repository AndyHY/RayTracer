#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
    using Task = std::function<void()>;

public:
    ThreadPool(int num_threads);
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool& operator=(const ThreadPool &other) = delete;
    ~ThreadPool();

    template <typename F, typename... Args>
    auto AddTask(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    bool stop;                                  //是否停止
    int  num_threads_;                          //线程个数
    std::mutex mutex_;                          //互斥量
    std::condition_variable cond_;              //条件变量
    std::queue<Task>  task_queue_;              //任务队列
    std::vector<std::thread> thread_queue_;     //线程队列
};

template <typename F, typename... Args>
auto ThreadPool::AddTask(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using ReturnType = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<ReturnType> ret = task->get_future();

    std::unique_lock<std::mutex> lock(mutex_);
    if (stop)
        throw std::runtime_error("AddTask on stopped ThreadPool");
    task_queue_.emplace([task]() { (*task)(); });
    lock.unlock();
    
    cond_.notify_one();

    return ret;
}

#endif