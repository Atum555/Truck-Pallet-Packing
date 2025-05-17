#ifndef PALLET_LIST_HPP
#define PALLET_LIST_HPP

#include "pallet.hpp"
#include <iostream>
#include <ostream>
#include <vector>

class PalletList {
  private:
    std::vector<Pallet> _pallets;

  public:
    // Add a pallet to the list
    void addPallet(const Pallet &pallet) { _pallets.push_back(pallet); }

    // Get the list of pallets
    const std::vector<Pallet> &getPallets() const { return _pallets; }

    friend std::ostream &operator<<(std::ostream &os, const PalletList &palletList) {
        os << "PalletList: [" << std::endl;
        for (size_t i = 0; i < palletList._pallets.size(); ++i) {
            os << palletList._pallets[i];
            if (i != palletList._pallets.size() - 1) os << ",";
            os << std::endl;
        }
        os << "]";
        return os;
    }
};

#endif // PALLET_LIST_HPP
