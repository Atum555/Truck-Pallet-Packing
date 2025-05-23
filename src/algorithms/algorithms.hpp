#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "pallet_list.hpp"
#include "parsers.hpp"

#define BIT(n) (1ULL << n)

PalletList bruteForce(const DataSet &dataSet);

PalletList greedy(const DataSet &dataset);

#endif // ALGORITHMS_HPP
