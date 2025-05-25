#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <algorithm>
#include <chrono>
#include <numeric>
#include <ostream>
#include <vector>

#include "pallet_list.hpp"

class Individual {
  private:
    std::vector<uint64_t> genome;

  public:
    uint64_t genomeSize;
    double   fitness;

    Individual(const Individual &other) = default;

    Individual &operator=(const Individual &other) = default;

    // Generate a random individual
    Individual(uint64_t numBits) : genome((numBits + 63) / 64, 0), genomeSize(numBits), fitness(0.0) {}

    // Genome bit getter
    bool operator[](size_t index) const {
        if (index >= genomeSize) throw std::out_of_range("Index out of range");
        return (genome[index / 64] & (1ULL << (index % 64))) != 0;
    }

    // Genome bit setter
    void set(size_t index, bool value) {
        if (index >= genomeSize) throw std::out_of_range("Index out of range");
        if (value) genome[index / 64] |= (1ULL << (index % 64));
        else genome[index / 64] &= ~(1ULL << (index % 64));
    }

    Individual clone() const {
        Individual new_ind(genomeSize);
        new_ind.genome  = genome;
        new_ind.fitness = fitness;
        return new_ind;
    }

    void calculateFitness(const DataSet &dataset) {
        const Truck               &truck            = dataset.first;
        const std::vector<Pallet> &availablePallets = dataset.second.getPallets();

        uint64_t currentWeight       = 0;
        uint64_t currentProfit       = 0;
        uint64_t selectedPalletCount = 0;

        for (uint64_t i = 0; i < genomeSize; ++i) {
            bool bit             = (*this)[i];
            currentWeight       += availablePallets[i].weight() * bit;
            currentProfit       += availablePallets[i].profit() * bit;
            selectedPalletCount += bit;
        }

        if (currentWeight > truck.capacity()) fitness = std::numeric_limits<double>::lowest();
        else fitness = static_cast<double>(currentProfit) - 0.001 * selectedPalletCount;
    }

    void status(std::ostream &os, const DataSet &dataset) const {
        std::vector<Pallet> palletList = dataset.second.getPallets();
        Truck               truck      = dataset.first;

        int weight          = 0;
        int profit          = 0;
        int numberOfPallets = 0;
        for (uint64_t i = 0; i < genomeSize; ++i)
            if ((*this)[i]) {
                weight += palletList[i].weight();
                profit += palletList[i].profit();
                numberOfPallets++;
            }

        os << "Fitness:    " << fitness << std::endl
           << "Max weight: " << truck.capacity() << std::endl
           << "Weight:     " << weight << std::endl
           << "Profit:     " << profit << std::endl
           << "Pallets:    " << numberOfPallets << std::endl
           << std::endl;

        for (uint64_t i = 0; i < genomeSize; ++i)
            if ((*this)[i]) os << i + 1 << " ";
        os << std::endl;
    }
};
#endif // INDIVIDUAL_HPP
