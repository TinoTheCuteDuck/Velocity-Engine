#pragma once

#include <stdexcept>
#include <vector>

class IDAllocator {
  private:
    size_t idAmount;
    size_t lastFreeId = 0;
    std::vector<bool> ids;

  public:
    IDAllocator(const size_t amount) : idAmount(amount), ids(amount, false) {}

    unsigned int allocate() {
        for (size_t i = lastFreeId; i < idAmount; i++) {
            if (!ids.at(i)) {
                ids.at(i) = true;
                lastFreeId = i + 1;
                return i + 1;
            }
        }
        throw std::runtime_error("Attempted to allocate too many IDs");
    }

    void free(const unsigned int id) {
        unsigned int allocatedId = id - 1;
        if (allocatedId < ids.size()) {
            ids.at(allocatedId) = false;
            lastFreeId = allocatedId;
        }
    }
};