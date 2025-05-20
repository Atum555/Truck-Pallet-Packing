#include "pallet_list.hpp"
#include "parsers.hpp"
#include "truck.hpp"
#include <algorithm>
#include <vector>
using namespace std;

PalletList greedy(DataSet dataset) {
    Truck          truck      = dataset.first;
    vector<Pallet> palletList = dataset.second.getPallets();
    PalletList     res;

    sort(palletList.begin(), palletList.end(), [](const Pallet &a, const Pallet &b) {
        int ratioA = a.profit() / a.weight();
        int ratioB = b.profit() / b.weight();
        if (ratioA != ratioB) { return ratioA > ratioB; }
        if (a.weight() != b.weight()) {
            return a.weight() > b.weight();
        } else {
            return a.id() < b.id();
        }
    });

    int currentWeight = 0;
    for (const Pallet &pallet : palletList) {
        if (currentWeight + pallet.weight() <= truck.capacity()) {
            res.addPallet(pallet);
            currentWeight += pallet.weight();
        }
    }
    return res;
}
