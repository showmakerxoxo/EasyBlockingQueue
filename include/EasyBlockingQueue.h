#pragma once

#ifndef EASY_BLOCK_QUEUE_H
#define EASY_BLOCK_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>

template <typename TaskType>
class EasyBlockingQueue {
 public:
  enum class State { OK, CLOSED, FULL };
  enum class ClosePolicy { Remaining, Immediate };

  explicit EasyBlockingQueue(size_t in_capacity = 0)
      : m_capacity(in_capacity) {}
  ~EasyBlockingQueue() { close(); }

  /**
   * @brief offer
   * @param in_item
   * @return
   * @note submit task to the queue
   */
  State offer(const TaskType &in_item) { return _push(in_item); }
  State offer(TaskType &&in_item) { return _push(in_item); }

  template <typename... Args>
  State emplace(Args &&...args) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_isClosed) {
      return State::CLOSED;
    }

    if (m_capacity > 0 && m_queue.size() >= m_capacity) {
      return State::FULL;
    }

    m_queue.emplace(std::forward<Args>(args)...);
    m_notEmpty_cv.notify_one();
    return State::OK;
  }

  /**
   * @brief take
   * @param out_item
   * @return
   * @note take and delete head task
   */
  State take(TaskType &out_item) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_notEmpty_cv.wait(lock,
                       [this]() { return !m_queue.empty() || m_isClosed; });

    if (m_isClosed && m_queue.empty()) {
      std::cout << "take -> m_queue is closed and empty" << std::endl;
      return State::CLOSED;
    }

    out_item = std::move(m_queue.front());
    m_queue.pop();
    _notifyNotFull();

    return State::OK;
  }

  /**
   * @brief pop
   * @return
   * @note delete head task
   */
  State pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_notEmpty_cv.wait(lock,
                       [this]() { return !m_queue.empty() || m_isClosed; });

    if (m_isClosed && m_queue.empty()) {
      std::cout << "pop -> m_queue is closed and empty" << std::endl;
      return State::CLOSED;
    }

    m_queue.pop();
    _notifyNotFull();

    return State::OK;
  }

  void close(ClosePolicy in_policy = ClosePolicy::Remaining) {
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_isClosed = true;

      if (in_policy == ClosePolicy::Immediate) {
        std::queue<TaskType> empty;
        std::swap(m_queue, empty);
      }
    }

    m_notEmpty_cv.notify_all();
    m_notFull_cv.notify_all();
  }

  size_t size() const {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
  }

  bool isClosed() const {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_isClosed;
  }

 private:
  std::queue<TaskType> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_notEmpty_cv;
  std::condition_variable m_notFull_cv;
  size_t m_capacity;
  bool m_isClosed{false};

 private:
  template <typename T>
  State _push(T &&in_item) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_isClosed) {
      return State::CLOSED;
    }

    if (m_capacity > 0) {
      m_notFull_cv.wait(
          lock, [this]() { return m_queue.size() < m_capacity || m_isClosed; });
      if (m_isClosed) {
        return State::CLOSED;
      }
    }

    m_queue.push(std::forward<T>(in_item));
    m_notEmpty_cv.notify_one();
    return State::OK;
  }

  void _notifyNotFull() {
    if (m_capacity > 0) {
      m_notFull_cv.notify_one();
    }
  }
};

#endif
