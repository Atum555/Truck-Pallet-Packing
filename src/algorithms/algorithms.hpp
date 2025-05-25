#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "pallet_list.hpp"
#include "parsers.hpp"

#define BIT(n) (1ULL << n)

/**
 * @brief Brute Force Algorithm
 *
 * Explores all possible combinations of pallets to find the optimal solution.
 *
 * @param dataSet The dataset containing the truck and pallets.
 * @return PalletList The optimal list of pallets.
 *
 * @note
 * Time Complexity: O(2^n), where n is the number of pallets.
 * Each pallet can either be included or excluded, leading to 2^n combinations.
 *
 * Space Complexity: O(n), for storing the current combination.
 * The recursion stack or iteration requires space proportional to the number of pallets.
 */
PalletList bruteForce(const DataSet &dataSet);

/**
 * @brief Greedy Algorithm
 *
 * Selects pallets based on a heuristic (e.g., profit-to-weight ratio) to approximate the optimal solution.
 *
 * @param dataset The dataset containing the truck and pallets.
 * @return PalletList The approximated optimal list of pallets.
 *
 * @note
 * Time Complexity: O(n log n), due to sorting the pallets.
 * Sorting the pallets by the heuristic dominates the runtime.
 *
 * Space Complexity: O(n), for storing the sorted pallets.
 * The sorted list of pallets requires additional space.
 */
PalletList greedy(const DataSet &dataset);

/**
 * @brief Dynamic Programming Algorithm
 *
 * Solves the problem using a bottom-up approach to build solutions for subproblems.
 *
 * @param dataset The dataset containing the truck and pallets.
 * @return PalletList The optimal list of pallets.
 *
 * @note
 * Time Complexity: O(n * W), where n is the number of pallets and W is the truck's capacity.
 * The DP table has dimensions n (pallets) by W (capacity), and each cell is computed once.
 *
 * Space Complexity: O(n * W), for the DP table.
 * The DP table requires space proportional to its dimensions.
 */
PalletList dynamicProgramming(const DataSet &dataset);

/**
 * @brief Brute Force Backtracking Algorithm
 *
 * Uses backtracking to explore all combinations of pallets, pruning invalid solutions early.
 *
 * @param dataSet The dataset containing the truck and pallets.
 * @return PalletList The optimal list of pallets.
 *
 * @note
 * Time Complexity: O(2^n), where n is the number of pallets.
 * Each pallet can either be included or excluded, leading to 2^n combinations.
 *
 * Space Complexity: O(n), for the recursion stack.
 * The recursion stack depth is proportional to the number of pallets.
 */
PalletList bruteForceBacktracking(const DataSet &dataSet);

/**
 * @brief Genetic Algorithm
 *
 * Uses evolutionary techniques (selection, crossover, mutation) to find a near-optimal solution.
 *
 * @param dataset The dataset containing the truck and pallets.
 * @param print Whether to print the progress of the algorithm.
 * @return PalletList The near-optimal list of pallets.
 *
 * @note
 * Time Complexity: O(g * p * n), where g is the number of generations, p is the population size, and n is the number of
 * pallets. Each generation involves evaluating the fitness of p individuals, each with n pallets.
 *
 * Space Complexity: O(p * n), for storing the population.
 * The population consists of p individuals, each with n pallets.
 */
PalletList genetic(const DataSet &dataset, bool print = true);

#endif // ALGORITHMS_HPP
