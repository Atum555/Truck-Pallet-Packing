#ifndef GENETICOPERATIONS_HPP
#define GENETICOPERATIONS_HPP

#include "item.hpp"
#include <vector>
#include <random>

using namespace std;

void singlePointCrossover(
    const Item &parent1,
    const Item &parent2,
    Item       &child1,
    Item       &child2,
    mt19937    &rng
) {
    size_t chromosomeLength = parent1.chromosome.size();

    uniform_int_distribution<size_t> dist(1, chromosomeLength - 1);
    size_t                           crossoverPoint = dist(rng);

    for (size_t i = 0; i < chromosomeLength; ++i) {
        if (i < crossoverPoint) {
            child1.chromosome[i] = static_cast<bool>(parent1.chromosome[i]);
            child2.chromosome[i] = static_cast<bool>(parent2.chromosome[i]);
        } else {
            child1.chromosome[i] = static_cast<bool>(parent2.chromosome[i]);
            child2.chromosome[i] = static_cast<bool>(parent1.chromosome[i]);
        }
    }
}

void bitFlipMutation(Item &ind, double mutationRate, mt19937 &rng) {
    uniform_real_distribution<> dist(0.0, 1.0);
    for (size_t i = 0; i < ind.chromosome.size(); ++i) {
        if (dist(rng) < mutationRate) {
            ind.chromosome[i] = !ind.chromosome[i];
        }
    }
}
#endif
