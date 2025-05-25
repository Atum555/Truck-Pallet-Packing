#include <cmath>
#include <cstdint>
#include <vector>

#include "algorithms.hpp"

using namespace std;

PalletList bruteForce(const DataSet &dataSet) {
    vector<Pallet> pallets    = dataSet.second.getPallets();
    uint64_t       capacity   = dataSet.first.capacity();
    uint64_t       palletsNum = pallets.size();

    // Sanity check
    if (palletsNum >= 64) return PalletList();

    uint64_t combinations = BIT(palletsNum);
    uint64_t value        = 0;
    uint64_t weight       = 0;

    vector<Pallet> solution;
    uint64_t       bestValue = 0;

    for (uint64_t mask = 0; mask < combinations; mask++) {
        value  = 0;
        weight = 0;

        for (uint64_t i = 0; i < palletsNum; i++)
            if (mask & BIT(i)) {
                value  += pallets[i].profit();
                weight += pallets[i].weight();
            }


        if (weight <= capacity && value > bestValue) {
            bestValue = value;
            solution.clear();

            for (uint64_t j = 0; j < palletsNum; j++)
                if (mask & BIT(j)) solution.push_back(pallets[j]);
        }
    }

    return PalletList(solution);
}
