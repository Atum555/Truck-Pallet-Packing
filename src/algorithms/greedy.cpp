#include <algorithm>
#include <vector>

#include "algorithms.hpp"

using namespace std;

PalletList greedy(const DataSet &dataset) {
    Truck          truck      = dataset.first;
    vector<Pallet> palletList = dataset.second.getPallets();
    PalletList     solution;

    sort(palletList.begin(), palletList.end(), [](const Pallet &a, const Pallet &b) {
        int ratioA = a.profit() / a.weight();
        int ratioB = b.profit() / b.weight();

        if (ratioA != ratioB) return ratioA > ratioB;
        if (a.weight() != b.weight()) return a.weight() > b.weight();
        else return a.id() < b.id();
    });

    int currentWeight = 0;
    for (const Pallet &pallet : palletList)
        if (currentWeight + pallet.weight() <= truck.capacity()) {
            solution.addPallet(pallet);
            currentWeight += pallet.weight();
        }

    return solution;
}
