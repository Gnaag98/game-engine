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

ThreadPool::ThreadPool(int thread_count) {
  m_threads.reserve(thread_count);
  for (int i = 0; i < thread_count; ++i) {
    m_threads.emplace_back(std::thread(&ThreadPool::work, this, i));
  }
}

ThreadPool::~ThreadPool() {
  m_is_destructing = true;
  m_condition.notify_all();
  for (std::thread& thread : m_threads) {
    thread.join();
  }
}

void ThreadPool::work(int ID) {
  std::packaged_task<void(int)> task;

  const auto& TASKS = m_tasks;
  const auto& IS_DESTRUCTING = m_is_destructing;

  while (true) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [&] { return m_tasks.empty() == false || m_is_destructing; });
    if (m_is_destructing) {
      break;
    } else {
      task = std::move(m_tasks.front());
      m_tasks.pop();
      lock.unlock();
      task(ID);
    }
  }
}

std::future<void> ThreadPool::add_task(std::function<void(int)>&& workload) {
  std::packaged_task<void(int)> task(workload);
  std::future<void> future = task.get_future();
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.emplace(std::move(task));
  }
  m_condition.notify_one();
  return future;
}
