#pragma once

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

class ThreadPool {
private:
  std::vector<std::thread> m_threads;
  std::queue<std::packaged_task<void(int)>> m_tasks;

  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::atomic<bool> m_is_destructing = false;

public:
  ThreadPool(const int thread_count);
  ~ThreadPool();

  [[nodiscard]]
  auto add_task(std::function<void(int)>&& workload) -> std::future<void>;
private:
  void work(const int thread_id);
};
