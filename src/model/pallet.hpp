#ifndef PALLET_HPP
#define PALLET_HPP

#include <ostream>

class Pallet {
  private:
    int _id;
    int _weight;
    int _profit;

  public:
    Pallet(int id, int weight, int profit) : _id(id), _weight(weight), _profit(profit) {}

    int id() const { return this->_id; }

    int weight() const { return this->_weight; }

    int profit() const { return this->_profit; }

    friend std::ostream &operator<<(std::ostream &os, const Pallet &pallet) {
        os << "Pallet(ID: " << pallet._id << ", Weight: " << pallet._weight
           << ", Profit: " << pallet._profit << ")";
        return os;
    }
};

#endif // PALLET_HPP
