#include <algorithm>
#include <vector>

#include "pallet_list.hpp"
#include "parsers.hpp"
#include "truck.hpp"
using namespace std;

PalletList greedy(DataSet dataset){
    Truck truck = dataset.first;
    vector<Pallet> palletList = dataset.second.getPallets();
    PalletList res;

    sort(palletList.begin(), palletList.end(), [](const Pallet &a, const Pallet &b) {
        return a.profit()/a.weight() < b.profit()/b.weight();
    });

    int currentWeight=0;
    for (const Pallet pallet : palletList){
        if (currentWeight + pallet.weight() <= truck.capacity()) {
            res.addPallet(pallet);
            currentWeight += pallet.weight();
        }
    }
    return res;
}
