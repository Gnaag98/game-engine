#include "ThreadPool.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>

#include <functional>
#include <utility>

#include <vector>
#include <queue>

#include <iostream>

ThreadPool::ThreadPool(const int thread_count) {
  m_threads.reserve(thread_count);
  for (auto i = 0; i < thread_count; ++i) {
    m_threads.emplace_back(std::thread(&ThreadPool::work, this, i));
  }
}

ThreadPool::~ThreadPool() {
  m_is_destructing = true;
  m_condition.notify_all();
  for (auto& thread : m_threads) {
    thread.join();
  }
}

void ThreadPool::work(const int thread_id) {
  // CHANGED: Moved the definition of task into the loop.
  //auto task = std::packaged_task<void(int)>{};

  while (true) {
    auto lock = std::unique_lock<std::mutex>{ m_mutex };
    m_condition.wait(lock, [&] { return !m_tasks.empty() || m_is_destructing; });
    if (m_is_destructing) {
      break;
    } else {
      auto task = std::move(m_tasks.front());
      m_tasks.pop();
      lock.unlock();
      task(thread_id);
    }
  }
}

auto ThreadPool::add_task(std::function<void(int)>&& workload) -> std::future<void> {
  auto task = std::packaged_task<void(int)>{workload};
  auto future = task.get_future();
  {
    auto lock = std::lock_guard<std::mutex>{ m_mutex };
    m_tasks.emplace(std::move(task));
  }
  m_condition.notify_one();
  return future;
}
