#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <queue>
#include <vector>
#include <condition_variable>
#include <functional>

class ThreadPool {
    size_t pool_size_;
    std::queue<std::function<void()>> task_queue;
    std::vector<std::thread> thread_pool;
    std::condition_variable cv;
    std::mutex m;
    std::atomic<bool> end;
public:

    explicit ThreadPool(size_t pool_size) : pool_size_(pool_size), end(false) {
        for(size_t i = 0; i < pool_size_; ++i) {
            thread_pool.emplace_back([this](){this->thread_job();});
        }
    }

    ~ThreadPool() {
        end = true;
        cv.notify_all();
        for(size_t i = 0; i < pool_size_; ++i) {
            thread_pool[i].join();
        }
    }

    template <typename Func, typename... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto pack_task = std::make_shared<std::packaged_task<decltype(func(args...))()>> (std::bind(func, args...));
        std::future<decltype(func(args...))> fut = (*pack_task).get_future();
        std::unique_lock<std::mutex> lk(m);
        task_queue.push([pack_task](){(*pack_task)();});
        cv.notify_one();
        return fut;
    }

    void thread_job() {
        while(!end) {
            std::unique_lock<std::mutex> lk(m);
            if(task_queue.empty()) {
                cv.wait(lk);
                continue;
            }
            auto task = task_queue.front();
            task_queue.pop();
            lk.unlock();
            task();
        }
    }
};