#ifndef PALLET_HPP
#define PALLET_HPP

#include <cstdint>
#include <ostream>

class Pallet {
  private:
    uint64_t _id;
    uint64_t _weight;
    uint64_t _profit;

  public:
    Pallet(uint64_t id, uint64_t weight, uint64_t profit) : _id(id), _weight(weight), _profit(profit) {}

    uint64_t id() const { return this->_id; }

    uint64_t weight() const { return this->_weight; }

    uint64_t profit() const { return this->_profit; }

    friend std::ostream &operator<<(std::ostream &os, const Pallet &pallet) {
        os << "Pallet(ID: " << pallet._id << ", Weight: " << pallet._weight << ", Profit: " << pallet._profit << ")";
        return os;
    }
};

#endif // PALLET_HPP
