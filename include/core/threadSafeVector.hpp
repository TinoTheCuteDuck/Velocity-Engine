#pragma once

#include <mutex>
#include <optional>
#include <vector>

template <typename T>
class ThreadSafeVector {
  public:
    void push_back(T data) {
        std::lock_guard<std::mutex> lock(mutex);
        vector.push_back(std::move(data));
    }

    std::optional<T> pop_back() {
        std::lock_guard<std::mutex> lock(mutex);
        if (vector.empty())
            return std::nullopt;

        T value = std::move(vector.back());
        vector.pop_back();
        return value;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return vector.size();
    }

  private:
    mutable std::mutex mutex;
    std::vector<T> vector;
};