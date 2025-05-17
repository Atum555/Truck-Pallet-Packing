#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <string>
#include <utility>
#include <vector>

#include "pallet_list.hpp"
#include "truck.hpp"

// Types
typedef std::pair<Truck, PalletList> DataSet;

// Parser Functions
std::vector<std::string> getAvailableDatasets();
DataSet                  getDataset(std::string datasetId);

#endif // PARSERS_HPP
