#include "thread_pool.hpp"

ThreadPool::ThreadPool(int num_threads) : stop(false), num_threads_(num_threads) {
    num_threads_ = num_threads_ < 1 ? 1 : num_threads_;
    for (int i = 0; i < num_threads_; i++) {
        thread_queue_.emplace_back(
            [this]() {
                while (1) {
                    Task task;
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    this->cond_.wait(lock, [this]() { return this->stop || !this->task_queue_.empty(); });
                    if (this->stop && this->task_queue_.empty())
                        return;
                    task = std::move(this->task_queue_.front());
                    this->task_queue_.pop();
                    lock.unlock();
                    task();
                }
            }
        );
    }
}

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(mutex_);
    stop = true;
    lock.unlock();
    cond_.notify_all();
    for (auto &worker : thread_queue_)
        worker.join();
}