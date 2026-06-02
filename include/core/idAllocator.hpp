#pragma once

#include <stdexcept>
#include <vector>

class IDAllocator {
  private:
    size_t idAmount;
    std::vector<bool> ids;

  public:
    IDAllocator(const size_t amount) : idAmount(amount), ids(amount, false) {}

    unsigned int allocate() {
        for (size_t i = 0; i < idAmount; i++) {
            if (!ids.at(i)) {
                ids.at(i) = true;
                return i + 1;
            }
        }
        throw std::runtime_error("Tried to allocate too many IDs");
    }

    void free(const unsigned int id) {
        unsigned int allocatedID = id - 1;
        if (allocatedID < ids.size() && allocatedID >= 0) {
            ids.at(allocatedID) = false;
        }
    }
};