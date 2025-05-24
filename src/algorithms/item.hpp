#ifndef ITEM_HPP
#define ITEM_HPP

#include <algorithm>
#include <numeric>
#include <vector>

#include "pallet_list.hpp"
#include "parsers.hpp"

using namespace std;

class Item {
  public:
    vector<char> chromosome;
    double       fitness;
    double       selectionProbability;

    Item(size_t numPallets) : chromosome(numPallets), fitness(0.0), selectionProbability(0.0) {}

    void calculateFitness(DataSet dataset) {
        double currentWeight       = 0.0;
        double currentProfit       = 0.0;
        size_t selectedPalletCount = 0;

        Truck          truck      = dataset.first;
        vector<Pallet> availablePallets = dataset.second.getPallets();

        for (size_t i = 0; i < chromosome.size(); ++i) {
            if (chromosome[i]) {
                currentWeight += availablePallets[i].weight();
                currentProfit += availablePallets[i].profit();
                selectedPalletCount++; // Increment count
            }
        }

        fitness = currentProfit;

        double penaltyFactor = 100.0; // Your existing penalty factor
        if (currentWeight > truck.capacity()) { fitness -= penaltyFactor * (currentWeight - truck.capacity()); }

        double palletCountPenaltyFactor = 0.01;
        fitness -= palletCountPenaltyFactor * selectedPalletCount;
    }
    Item clone() const {
        Item new_ind(chromosome.size());
        new_ind.chromosome           = chromosome;
        new_ind.fitness              = fitness;
        new_ind.selectionProbability = selectionProbability;
        return new_ind;
    }

    Item &operator=(const Item &other) = default;

    Item(const Item &other) = default;

    string toString() const {
        string s = "[";
        for (bool b : chromosome) { s += (b ? "1" : "0"); }
        s += "] Fitness: " + to_string(fitness);
        return s;
    }

    size_t countSelectedPallets() const {
        size_t count = 0;
        for (bool bit : chromosome) {
            if (bit) { count++; }
        }
        return count;
    }

    long long calculateSelectedPalletsIdSum(const vector<Pallet> &availablePallets) const {
        long long idSum = 0;
        for (size_t i = 0; i < chromosome.size(); ++i) {
            if (chromosome[i]) {
                if (i < availablePallets.size()) {
                    idSum += availablePallets[i].id();
                }
            }
        }
        return idSum;
    }

};
#endif
