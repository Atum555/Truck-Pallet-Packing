#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>

#include "algorithms.hpp"
#include "geneticOperations.hpp"
#include "item.hpp"
#include "population.hpp"
#include "utils.hpp"

using namespace std;

PalletList genetic(const DataSet &dataset) {
    vector<Pallet> palletList = dataset.second.getPallets();
    Truck          truck      = dataset.first;

    int    numPallets     = palletList.size();
    int    populationSize = 1000;
    double crossoverRate  = 0.75;
    double mutationRate   = 0.001;

    // Initial selection proportions
    double elite_p      = 0.05;
    double tournament_p = 0.35;
    double roulette_p   = 0.2;
    double random_p     = 0.4;

    unsigned int randomSeed = chrono::high_resolution_clock::now().time_since_epoch().count();

    Population population(populationSize, numPallets, randomSeed);

    int    noImprovementCount   = 0;
    int    improvementThreshold = min(numPallets * 10, 200);
    double bestFitness          = -numeric_limits<double>::infinity();

    for (int currentGeneration = 0; noImprovementCount < improvementThreshold; ++currentGeneration) {
        // Calculate fitness and sort
        population.updateFitness(dataset);
        population.sortByFitness();

        //* Print Status
        clearScreen();
        cout << "Generation: " << currentGeneration << endl;
        population.individuals[0].status(cout, dataset);

        // Check for improvement in best fitness
        if (population.individuals[0].fitness > bestFitness) {
            bestFitness        = population.individuals[0].fitness;
            noImprovementCount = 0;
        } else ++noImprovementCount;

        // Keep the top elites and shuffle the rest
        int eliteOffset = static_cast<int>(populationSize * elite_p);
        shuffle(population.individuals.begin() + eliteOffset, population.individuals.end(), population.rng);


        // Tournament selection with breeding
        int tournamentCount = static_cast<int>(populationSize * tournament_p);
        for (int i = 0; i < tournamentCount; i += 2) {
            int parent1Index = population.rng() % populationSize;
            for (int j = 1; j < 5; ++j) { // Tournament size of 5
                int competitorIndex = population.rng() % populationSize;
                if (population.individuals[competitorIndex].fitness > population.individuals[parent1Index].fitness) {
                    parent1Index = competitorIndex;
                }
            }

            int parent2Index = population.rng() % populationSize;
            for (int j = 1; j < 5; ++j) { // Tournament size of 5
                int competitorIndex = population.rng() % populationSize;
                if (population.individuals[competitorIndex].fitness > population.individuals[parent2Index].fitness) {
                    parent2Index = competitorIndex;
                }
            }

            Individual offspring1(numPallets), offspring2(numPallets);
            tie(offspring1, offspring2) = crossover(
                population.individuals[parent1Index], population.individuals[parent2Index], crossoverRate,
                population.rng
            );
            population.individuals[eliteOffset + i] = offspring1;
            if (i + 1 < tournamentCount) { population.individuals[eliteOffset + i + 1] = offspring2; }
        }


        // Roulette wheel selection with breeding
        int    rouletteCount = static_cast<int>(populationSize * roulette_p);
        double totalFitness  = 0.0;
        for (const auto &individual : population.individuals) totalFitness += individual.fitness;
        for (int i = 0; i < rouletteCount; i += 2) {
            double pick1             = uniform_real_distribution<double>(0.0, totalFitness)(population.rng);
            double cumulativeFitness = 0.0;
            int    parent1Index      = -1;
            for (int j = 0; j < populationSize; ++j) {
                cumulativeFitness += population.individuals[j].fitness;
                if (cumulativeFitness >= pick1) {
                    parent1Index = j;
                    break;
                }
            }

            double pick2      = uniform_real_distribution<double>(0.0, totalFitness)(population.rng);
            cumulativeFitness = 0.0;
            int parent2Index  = -1;
            for (int j = 0; j < populationSize; ++j) {
                cumulativeFitness += population.individuals[j].fitness;
                if (cumulativeFitness >= pick2) {
                    parent2Index = j;
                    break;
                }
            }

            Individual offspring1(numPallets), offspring2(numPallets);
            tie(offspring1, offspring2) = crossover(
                population.individuals[parent1Index], population.individuals[parent2Index], crossoverRate,
                population.rng
            );
            population.individuals[eliteOffset + tournamentCount + i] = offspring1;
            if (i + 1 < rouletteCount) { population.individuals[eliteOffset + tournamentCount + i + 1] = offspring2; }
        }


        // Fill the rest with random individuals
        int randomCount = static_cast<int>(populationSize * random_p);
        for (int i = 0; i < randomCount; ++i)
            population.individuals[eliteOffset + tournamentCount + rouletteCount + i] = Individual(numPallets);

        // Apply mutations to every individual except the best
        for (int i = 1; i < populationSize; ++i) {
            auto &individual = population.individuals[i];
            for (uint64_t gene = 0; gene < individual.genomeSize; ++gene)
                if (population.rng() < mutationRate * population.rng.max()) individual.set(gene, !individual[gene]);
        }
    }

    // Calculate fitness and sort
    population.updateFitness(dataset);
    population.sortByFitness();

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        outputFile << "Final generation results:" << endl << endl;
        for (const auto &individual : population.individuals) {
            individual.status(outputFile, dataset);
            outputFile << endl << endl;
        }
        outputFile.close();
    } else cerr << "Unable to open file for writing." << endl;

    Individual bestIndividual = population.individuals[0];

    vector<Pallet> selectedPalletsVector;
    int            finalTotalWeight = 0;

    for (uint64_t i = 0; i < bestIndividual.genomeSize; ++i)
        if (bestIndividual[i] and finalTotalWeight + palletList[i].weight() <= truck.capacity()) {
            selectedPalletsVector.push_back(palletList[i]);
            finalTotalWeight += palletList[i].weight();
        }

    PalletList solution(selectedPalletsVector);

    return solution;
}
