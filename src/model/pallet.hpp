#ifndef PALLET_HPP
#define PALLET_HPP

#include <cstdint>
#include <ostream>

class Pallet {
  private:
    u_int64_t _id;
    u_int64_t _weight;
    u_int64_t _profit;

  public:
    Pallet(u_int64_t id, u_int64_t weight, u_int64_t profit) : _id(id), _weight(weight), _profit(profit) {}

    u_int64_t id() const { return this->_id; }

    u_int64_t weight() const { return this->_weight; }

    u_int64_t profit() const { return this->_profit; }

    friend std::ostream &operator<<(std::ostream &os, const Pallet &pallet) {
        os << "Pallet(ID: " << pallet._id << ", Weight: " << pallet._weight << ", Profit: " << pallet._profit << ")";
        return os;
    }
};

#endif // PALLET_HPP
