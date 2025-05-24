#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "item.hpp"
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

class Population {
  public:
    vector<Item> items;
    mt19937      rng; // random number generator

    Population(int size, size_t numPallets, unsigned int seed) : rng(seed) {
        items.reserve(size);
        for (int i = 0; i < size; ++i) {
            Item newInd(numPallets);

            uniform_real_distribution<> dist(0.0, 1.0);
            for (size_t j = 0; j < numPallets; ++j) { newInd.chromosome[j] = (dist(rng) < 0.5 ? 1 : 0); }
            items.push_back(move(newInd));
        }
    }


    Item select(int tournamentSize, const vector<Pallet> &allAvailablePallets) {
        vector<Item *> tournamentContestants;
        tournamentContestants.reserve(tournamentSize);

        uniform_int_distribution<size_t> dist(0, items.size() - 1);
        for (int i = 0; i < tournamentSize; ++i) { tournamentContestants.push_back(&items[dist(rng)]); }

        if (tournamentContestants.empty()) {
            return Item(0);
        }

        Item *best = tournamentContestants[0];

        for (size_t i = 1; i < tournamentContestants.size(); ++i) {
            Item *current = tournamentContestants[i];

            if (current->fitness > best->fitness) {
                best = current;

            } else if (current->fitness == best->fitness) {
                size_t currentPalletCount = current->countSelectedPallets();
                size_t bestPalletCount    = best->countSelectedPallets();

                if (currentPalletCount < bestPalletCount) {
                    best = current;
                } else if (currentPalletCount == bestPalletCount) {

                    long long currentIdSum = current->calculateSelectedPalletsIdSum(allAvailablePallets);
                    long long bestIdSum    = best->calculateSelectedPalletsIdSum(allAvailablePallets);

                    if (currentIdSum < bestIdSum) {
                        best = current;
                    } else if (currentPalletCount == bestPalletCount) {
                        long long currentIdSum = current->calculateSelectedPalletsIdSum(allAvailablePallets);
                        long long bestIdSum    = best->calculateSelectedPalletsIdSum(allAvailablePallets);

                        if (currentIdSum < bestIdSum) {
                            best = current;
                        }
                    }
                }
            }

        }
        return best->clone();
    }

        void calculateSelectionProbabilities() {
            double totalFitness = 0.0;
            for (const auto &ind : items) { totalFitness += ind.fitness; }

            if (totalFitness == 0) {
                for (auto &ind : items) { ind.selectionProbability = 1.0 / items.size(); }
            } else {
                for (auto &ind : items) { ind.selectionProbability = ind.fitness / totalFitness; }
            }
        }

        Item selectRouletteWheel() {
            uniform_real_distribution<> dist(0.0, 1.0);
            double                      pick       = dist(rng);
            double                      currentSum = 0.0;

            for (const auto &ind : items) {
                currentSum += ind.selectionProbability;
                if (pick <= currentSum) { return ind.clone(); }
            }
            return items.back().clone();
        }
    };
#endif
