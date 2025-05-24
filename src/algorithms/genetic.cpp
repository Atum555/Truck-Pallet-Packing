#include <algorithm>
#include <chrono>
#include <vector>

#include "algorithms.hpp"
#include "geneticOperations.hpp"
#include "item.hpp"
#include "population.hpp"

using namespace std;

/*
    Representation: Items are represented as binary strings, where each bit indicates whether an item is included.
    Fitness Function: Evaluates the total value of selected items while penalizing solutions that exceed the weight
   limit. Crossover and Mutation: Involve swapping items between solutions or flipping bits to introduce variation.
*/

PalletList genetic(const DataSet &dataset) {
    Truck          truck      = dataset.first;
    vector<Pallet> palletList = dataset.second.getPallets();

    size_t numPallets     = palletList.size();
    int    popSize        = 300;
    int    generations    = 100;
    double crossoverRate  = 0.8;
    double mutationRate   = 0.04;
    int    tournamentSize = 6;

    if (numPallets > 1000) {
        popSize        = 400;
        generations    = 300;
        crossoverRate  = 0.85;
        mutationRate   = 0.01;
        tournamentSize = 5;
    }

    unsigned int randomSeed = chrono::high_resolution_clock::now().time_since_epoch().count();

    Population curPopulation(popSize, numPallets, randomSeed);
    Item       bestOverallItem = curPopulation.items[0].clone();
    bestOverallItem.fitness    = -numeric_limits<double>::infinity();

    for (int gen = 0; gen < generations; ++gen) {
        for (auto &Item : curPopulation.items) { Item.calculateFitness(dataset); }

        auto currentGenBestIt
            = max_element(curPopulation.items.begin(), curPopulation.items.end(), [](const Item &a, const Item &b) {
                  return a.fitness < b.fitness;
              });

        if (currentGenBestIt->fitness > bestOverallItem.fitness) { bestOverallItem = currentGenBestIt->clone(); }

        cout << "  Generation " << gen << ": Best fitness = " << currentGenBestIt->fitness
             << " (Overall best: " << bestOverallItem.fitness << ")" << endl;

        vector<Item> nextGeneration;
        nextGeneration.reserve(popSize);

        nextGeneration.push_back(bestOverallItem.clone());
        while ((int)nextGeneration.size() < popSize) {
            Item parent1 = curPopulation.select(tournamentSize, palletList);
            Item parent2 = curPopulation.select(tournamentSize, palletList);

            Item child1(numPallets);
            Item child2(numPallets);

            uniform_real_distribution<> dist(0.0, 1.0);
            if (dist(curPopulation.rng) < crossoverRate) {
                singlePointCrossover(parent1, parent2, child1, child2, curPopulation.rng);
            } else {
                child1 = parent1.clone();
                child2 = parent2.clone();
            }

            bitFlipMutation(child1, mutationRate, curPopulation.rng);
            bitFlipMutation(child2, mutationRate, curPopulation.rng);

            nextGeneration.push_back(move(child1));

            if ((int)nextGeneration.size() < popSize) { nextGeneration.push_back(move(child2)); }
        }

        curPopulation.items = move(nextGeneration);
    }

    vector<Pallet> selectedPalletsVector;
    int            finalTotalWeight = 0;

    for (size_t i = 0; i < bestOverallItem.chromosome.size(); ++i) {
        if (bestOverallItem.chromosome[i]) {
            if (finalTotalWeight + palletList[i].weight() <= truck.capacity()) {
                selectedPalletsVector.push_back(palletList[i]);
                finalTotalWeight += palletList[i].weight();
            }
        }
    }

    PalletList solution(selectedPalletsVector);

    return solution;
}
