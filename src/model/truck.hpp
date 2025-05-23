#ifndef TRUCK_HPP
#define TRUCK_HPP

#include <cstdint>
#include <ostream>

class Truck {
  private:
    uint64_t _capacity;
    uint64_t _pallets;

  public:
    Truck(uint64_t capacity, uint64_t pallets) : _capacity(capacity), _pallets(pallets) {}

    uint64_t capacity() const { return this->_capacity; }

    uint64_t pallets() const { return this->_pallets; }

    friend std::ostream &operator<<(std::ostream &os, const Truck &truck) {
        os << "Truck(Capacity: " << truck._capacity << ", Pallets: " << truck._pallets << ")";
        return os;
    }
};

#endif // TRUCK_HPP
