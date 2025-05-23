#ifndef PALLET_LIST_HPP
#define PALLET_LIST_HPP

#include "pallet.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

class PalletList {
  private:
    std::vector<Pallet> _pallets;

  public:
    PalletList() {}

    // Constructor from a vector of pallets
    explicit PalletList(const std::vector<Pallet> &pallets) : _pallets(pallets) {}

    // Add a pallet to the list
    void addPallet(const Pallet &pallet) { _pallets.push_back(pallet); }

    // Get the list of pallets
    const std::vector<Pallet> &getPallets() const { return _pallets; }

    uint64_t totalWeight() const {
        uint64_t weight = 0;
        for (const auto &pallet : _pallets) weight += pallet.weight();
        return weight;
    }

    uint64_t totalProfit() const {
        uint64_t value = 0;
        for (const auto &pallet : _pallets) value += pallet.profit();
        return value;
    }

    // Print Pallets
    friend std::ostream &operator<<(std::ostream &os, const PalletList &palletList) {
        os << "PalletList: [" << std::endl;
        for (size_t i = 0; i < palletList._pallets.size(); ++i) {
            os << "  " << palletList._pallets[i];
            if (i != palletList._pallets.size() - 1) os << ",";
            os << std::endl;
        }
        os << "]" << std::endl;
        os << std::endl
           << "Pallets: " << palletList._pallets.size() << std::endl
           << "Weight: " << palletList.totalWeight() << std::endl
           << "Profit: " << palletList.totalProfit() << std::endl;
        return os;
    }
};

#endif // PALLET_LIST_HPP
