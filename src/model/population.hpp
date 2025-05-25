#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <algorithm>
#include <random>
#include <vector>

#include "item.hpp"
#include "parsers.hpp"

class Population {
  public:
    std::vector<Individual> individuals;
    std::mt19937            rng; // random number generator

    Population(int size, size_t numPallets, unsigned int seed) : rng(seed) {
        individuals.reserve(size);
        for (int i = 0; i < size; ++i) {
            Individual individual(numPallets);
            individuals.push_back(std::move(individual));
        }
    }

    void updateFitness(const DataSet &dataSet) {
        for (auto &ind : individuals) ind.calculateFitness(dataSet);
    }

    void sortByFitness() {
        std::sort(individuals.begin(), individuals.end(), [](const Individual &a, const Individual &b) {
            return a.fitness > b.fitness;
        });
    }
};

#endif
