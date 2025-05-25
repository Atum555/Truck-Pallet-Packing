#ifndef GENETICOPERATIONS_HPP
#define GENETICOPERATIONS_HPP

#include "item.hpp"
#include <random>
#include <vector>

using namespace std;

void singlePointCrossover(
    const Individual &parent1, const Individual &parent2, Individual &child1, Individual &child2, mt19937 &rng
) {
    size_t chromosomeLength = parent1.genomeSize;

    uniform_int_distribution<size_t> dist(1, chromosomeLength - 1);
    size_t                           crossoverPoint = dist(rng);

    for (size_t i = 0; i < chromosomeLength; ++i) {
        if (i < crossoverPoint) {
            child1.set(i, parent1[i]);
            child2.set(i, parent2[i]);
        } else {
            child1.set(i, parent2[i]);
            child2.set(i, parent1[i]);
        }
    }
}

void bitFlipMutation(Individual &ind, double mutationRate, mt19937 &rng) {
    uniform_real_distribution<> dist(0.0, 1.0);
    for (size_t i = 0; i < ind.genomeSize; ++i)
        if (dist(rng) < mutationRate) ind.set(i, !ind[i]);
}

pair<Individual, Individual>
crossover(const Individual &parent1, const Individual &parent2, double crossoverRate, mt19937 &rng) {
    Individual child1 = parent1.clone();
    Individual child2 = parent2.clone();

    uniform_real_distribution<> dist(0.0, 1.0);
    if (dist(rng) < crossoverRate) { singlePointCrossover(parent1, parent2, child1, child2, rng); }

    return { child1, child2 };
}
#endif
