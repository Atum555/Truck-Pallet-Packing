#ifndef TRUCK_HPP
#define TRUCK_HPP

#include <cstdint>
#include <ostream>

class Truck {
  private:
    u_int64_t _capacity;
    u_int64_t _pallets;

  public:
    Truck(u_int64_t capacity, u_int64_t pallets) : _capacity(capacity), _pallets(pallets) {}

    u_int64_t capacity() const { return this->_capacity; }

    u_int64_t pallets() const { return this->_pallets; }

    friend std::ostream &operator<<(std::ostream &os, const Truck &truck) {
        os << "Truck(Capacity: " << truck._capacity << ", Pallets: " << truck._pallets << ")";
        return os;
    }
};

#endif // TRUCK_HPP
