#ifndef WORK_QUEUE_HPP
#define WORK_QUEUE_HPP

#include <queue>
#include <mutex>

template <typename T>
class WorkQueue {
public:
    WorkQueue() = default;

    void AddWork(const T &work) {
        mutex_.lock();
        work_queue_.push(work);
        mutex_.unlock();
    }

    bool GetWork(T &work) {
        mutex_.lock();
        if (work_queue_.empty()) {
            mutex_.unlock();
            return false;
        }
        work = work_queue_.front();
        work_queue_.pop();
        mutex_.unlock();
        return true;
    }

private:
    std::queue<T> work_queue_;
    std::mutex    mutex_;
};

#endif