#include "brute_force.h"
#include <cmath>
using namespace std;

#define BIT(n) (1 << n)

PalletList solveBruteForce(const DataSet &DataSet) {
    int            capacity   = DataSet.first.capacity();
    int            palletsNum = DataSet.first.pallets();
    vector<Pallet> pallets    = DataSet.second.getPallets();

    int combinations = BIT(palletsNum);
    int value        = 0;
    int weight       = 0;

    PalletList palletList;
    int bestValue = 0;

    for (int mask = 0; mask < combinations; mask++) {
        value  = 0;
        weight = 0;

        for (int i = 0; i < palletsNum; i++) {
            if (mask & BIT(i)) {
                value  += pallets[i].profit();
                weight += pallets[i].weight();
            }
        }

        if (weight <= capacity && value > bestValue) {
            bestValue = value;
            palletList.clear();

            for (int j = 0; j < palletsNum; j++) {
                if (mask & BIT(j)) palletList.addPallet(pallets[j]);
            }
        }
    }

    return palletList;
}