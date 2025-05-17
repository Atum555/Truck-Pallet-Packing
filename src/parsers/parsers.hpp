#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <string>
#include <utility>
#include <vector>

#include "pallet_list.hpp"
#include "truck.hpp"

// Parser Functions
std::vector<std::string>     getAvailableDatasets();
std::pair<Truck, PalletList> getDataset(std::string datasetId);

#endif // PARSERS_HPP
