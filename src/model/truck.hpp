#ifndef TRUCK_HPP
#define TRUCK_HPP

#include <ostream>

class Truck {
  private:
    int _capacity;
    int _pallets;

  public:
    Truck(int capacity, int pallets) : _capacity(capacity), _pallets(pallets) {}

    int capacity() const { return this->_capacity; }

    int pallets() const { return this->_pallets; }

    friend std::ostream &operator<<(std::ostream &os, const Truck &truck) {
        os << "Truck(Capacity: " << truck._capacity << ", Pallets: " << truck._pallets << ")";
        return os;
    }
};

#endif // TRUCK_HPP
