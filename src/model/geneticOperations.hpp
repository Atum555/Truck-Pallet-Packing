#ifndef GENETIC_OPERATIONS_HPP
#define GENETIC_OPERATIONS_HPP

#include <random>
#include <vector>

#include "item.hpp"

std::pair<Individual, Individual>
crossover(const Individual &parent1, const Individual &parent2, double crossoverRate, std::mt19937 &rng) {
    Individual child1 = parent1.clone();
    Individual child2 = parent2.clone();

    std::uniform_real_distribution<> dist1(0.0, 1.0);
    if (dist1(rng) > crossoverRate) return { child1, child2 };

    size_t                                chromosomeLength = parent1.genomeSize;
    std::uniform_int_distribution<size_t> dist2(1, chromosomeLength - 1);
    size_t                                crossoverPoint = dist2(rng);

    for (size_t i = crossoverPoint; i < chromosomeLength; ++i) {
        child1.set(i, parent2[i]);
        child2.set(i, parent1[i]);
    }

    return { child1, child2 };
}
#endif // GENETIC_OPERATIONS_HPP
