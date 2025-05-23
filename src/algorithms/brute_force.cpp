#include <cmath>
#include <cstdint>
#include <vector>

#include "algorithms.hpp"

using namespace std;

PalletList bruteForce(const DataSet &dataSet) {
    vector<Pallet> pallets    = dataSet.second.getPallets();
    u_int64_t      capacity   = dataSet.first.capacity();
    u_int64_t      palletsNum = pallets.size();

    // Sanity check
    if (palletsNum >= 64) return PalletList();

    u_int64_t combinations = BIT(palletsNum);
    u_int64_t value        = 0;
    u_int64_t weight       = 0;

    vector<Pallet> solution;
    u_int64_t      bestValue = 0;

    for (u_int64_t mask = 0; mask < combinations; mask++) {
        value  = 0;
        weight = 0;

        for (u_int64_t i = 0; i < palletsNum; i++)
            if (mask & BIT(i)) {
                value  += pallets[i].profit();
                weight += pallets[i].weight();
            }


        if (weight <= capacity && value > bestValue) {
            bestValue = value;
            solution.clear();

            for (u_int64_t j = 0; j < palletsNum; j++)
                if (mask & BIT(j)) solution.push_back(pallets[j]);
        }
    }

    return PalletList(solution);
}
