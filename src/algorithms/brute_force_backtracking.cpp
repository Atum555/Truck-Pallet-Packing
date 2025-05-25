#include "algorithms.hpp"

using namespace std;

void backtrack(
    const vector<Pallet> &pallets, uint64_t capacity, size_t idx, int currentWeight, int currentProfit,
    vector<int> &currentSelection, int &bestProfit, vector<int> &bestSelection
) {
    if (idx == pallets.size()) {
        if (currentProfit > bestProfit) {
            bestProfit    = currentProfit;
            bestSelection = currentSelection;
        }
        return;
    }

    // Exclude current pallet
    backtrack(pallets, capacity, idx + 1, currentWeight, currentProfit, currentSelection, bestProfit, bestSelection);

    // Include current pallet if it fits
    if (currentWeight + pallets[idx].weight() <= capacity) {
        currentSelection.push_back(idx);
        backtrack(
            pallets, capacity, idx + 1, currentWeight + pallets[idx].weight(), currentProfit + pallets[idx].profit(),
            currentSelection, bestProfit, bestSelection
        );
        currentSelection.pop_back();
    }
}

PalletList solveBruteForceBacktracking(const DataSet &dataset) {
    int            capacity = dataset.first.capacity();
    vector<Pallet> pallets  = dataset.second.getPallets();

    int         bestProfit = 0;
    vector<int> currentSelection, bestSelection;

    backtrack(pallets, capacity, 0, 0, 0, currentSelection, bestProfit, bestSelection);

    PalletList result;
    for (int idx : bestSelection) result.addPallet(pallets[idx]);

    return result;
}
