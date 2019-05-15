//
// Created by lepet on 5/10/2019.
//

#ifndef MINIATURE_COMMON_H
#define MINIATURE_COMMON_H

#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <chrono>
#include <memory>
#include <queue>
#include <functional>

namespace io {
    std::string read_file(const std::string& filename);
}

template<typename T>
class bind_guard {
};

//template<typename T, size_t size_>
//class ring_buffer {
//public:
//    constexpr static size_t size{size_};
//
//    ring_buffer() = default;
//
//    bool push(const T& val) {
//        auto head = head_.load(std::memory_order_relaxed);
//        auto head_next = next(head);
//        auto tail = tail_.load(std::memory_order_relaxed);
//        if (head_next == tail)
//            return false;
//        buffer[head] = val;
//        head_.store(head_next, std::memory_order_release);
//        return true;
//    }
//
//    bool pop(T& val) {
//        auto tail = tail_.load(std::memory_order_relaxed);
//        auto head = head_.load(std::memory_order_relaxed);
//        if (tail == head)
//            return false;
//        val = buffer[tail];
//        auto tail_next = next(tail);
//        tail_.store(tail_next, std::memory_order_release);
//        return true;
//    }
//
//private:
//    size_t next(size_t ptr) { return (ptr + 1) % size; }
//
//private:
//    T buffer[size];
//    std::atomic_size_t head_{0}, tail_{0};
//};
//
//using command_t = std::function<void()>;
//using command_buffer_t = ring_buffer<command_t, 1024>;

template<typename T>
struct double_buffer {
    std::mutex mtx;
    std::condition_variable cond;
    std::queue<T> server_buffer, client_buffer;
};

#endif //MINIATURE_COMMON_H
