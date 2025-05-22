#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

#include "dynamicProgramming.h"
#include "pallet_list.hpp"
#include "parsers.hpp"
#include "truck.hpp"

using namespace std;

struct solution {
    int profit;
    int itemCount;
    int sumIndices;

    solution() : profit(0), itemCount(0), sumIndices(0) {}

    solution(int p, int ic, int si) : profit(p), itemCount(ic), sumIndices(si) {}

    bool operator<(const solution &other) const {
        if (profit != other.profit) { return profit < other.profit; }
        if (itemCount != other.itemCount) { return itemCount > other.itemCount; }
        return sumIndices > other.sumIndices;
    }
};

PalletList dynamicProgramming(const DataSet dataset) {
    Truck          truck        = dataset.first;
    vector<Pallet> palletVector = dataset.second.getPallets();
    PalletList     optimalSolution;
    int            n        = palletVector.size();
    int            capacity = truck.capacity();

    if (n == 0 || capacity == 0) { return optimalSolution; }

    vector<vector<solution>> dp(n + 1, vector<solution>(capacity + 1));

    for (int i = 1; i <= n; ++i) {
        int currentPalletWeight = palletVector[i - 1].weight();
        int currentPalletProfit = palletVector[i - 1].profit();
        int currentPalletIndex  = i - 1;

        for (int k = 0; k <= capacity; ++k) {
            solution option1 = dp[i - 1][k];

            solution option2;
            if (currentPalletWeight <= k) {
                if (dp[i - 1][k - currentPalletWeight].sumIndices == std::numeric_limits<int>::max()) {
                    option2 = solution(-1, 0, std::numeric_limits<int>::max());
                } else {
                    int newProfit     = dp[i - 1][k - currentPalletWeight].profit + currentPalletProfit;
                    int newItemCount  = dp[i - 1][k - currentPalletWeight].itemCount + 1;
                    int newSumIndices = dp[i - 1][k - currentPalletWeight].sumIndices + currentPalletIndex;
                    option2           = solution(newProfit, newItemCount, newSumIndices);
                }
            } else {
                option2 = solution(-1, 0, std::numeric_limits<int>::max());
            }

            if (option1 < option2) {
                dp[i][k] = option2;
            } else {
                dp[i][k] = option1;
            }
        }
    }

    int currentWeight = capacity;
    for (int i = n; i > 0 && currentWeight > 0; --i) {
        bool was_included = false;
        int  palletWeight = palletVector[i - 1].weight();
        int  palletProfit = palletVector[i - 1].profit();
        int  palletIndex  = i - 1;

        if (currentWeight >= palletWeight) {
            solution expectedIfIncluded(
                dp[i - 1][currentWeight - palletWeight].profit + palletProfit,
                dp[i - 1][currentWeight - palletWeight].itemCount + 1,
                dp[i - 1][currentWeight - palletWeight].sumIndices + palletIndex
            );

            if (dp[i][currentWeight].profit == expectedIfIncluded.profit
                && dp[i][currentWeight].itemCount == expectedIfIncluded.itemCount
                && dp[i][currentWeight].sumIndices == expectedIfIncluded.sumIndices) {
                if (!(dp[i][currentWeight].profit == dp[i - 1][currentWeight].profit
                      && dp[i][currentWeight].itemCount == dp[i - 1][currentWeight].itemCount
                      && dp[i][currentWeight].sumIndices == dp[i - 1][currentWeight].sumIndices)) {
                    was_included = true;
                }
            }
        }

        if (was_included) {
            optimalSolution.addPallet(palletVector[i - 1]);
            currentWeight -= palletVector[i - 1].weight();
        }
    }

    return optimalSolution;
}
