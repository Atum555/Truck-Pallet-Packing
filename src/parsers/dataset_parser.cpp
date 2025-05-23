#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "pallet_list.hpp"
#include "parsers.hpp"
#include "truck.hpp"

using namespace std;

bool checkDatasetExists(string datasetId) {
    vector<string> availableDatasets = getAvailableDatasets();
    return find(availableDatasets.begin(), availableDatasets.end(), datasetId)
           != availableDatasets.end();
}

Truck getTruckFromFile(ifstream &file) {
    string line, token;

    // Ignore the header line
    getline(file, line);

    getline(file, line);
    istringstream iss(line);

    u_int64_t capacity, pallets;

    getline(iss, token, ',');
    capacity = stoi(token);
    getline(iss, token, ',');
    pallets = stoi(token);

    return Truck(capacity, pallets);
}

PalletList getPalletListFromFile(ifstream &file) {
    PalletList palletList;
    string     line;

    // Ignore the header line
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string        token;

        u_int64_t id, weight, profit;

        // Parse the CSV line
        getline(iss, token, ',');
        id = stoi(token);

        getline(iss, token, ',');
        weight = stoi(token);

        getline(iss, token, ',');
        profit = stoi(token);

        // Create a Pallet object and add it to the list
        Pallet pallet(id, weight, profit);
        palletList.addPallet(pallet);
    }

    return palletList;
}

vector<string> getAvailableDatasets() {
    vector<string> availableDatasets;
    string         basePath = "datasets/";

    for (const auto &entry : filesystem::directory_iterator(basePath)) {
        string filename = entry.path().filename().string();

        // Check if the file matches the pattern "Pallets_<id>.csv"
        if (!(filename.find("Pallets_") == 0 && filename.find(".csv") == filename.size() - 4))
            continue;

        string datasetId = filename.substr(8, filename.size() - 12); // Extract the id

        // Check if the corresponding TruckAndPallets file exists
        string truckAndPalletsFile = basePath + "TruckAndPallets_" + datasetId + ".csv";
        if (filesystem::exists(truckAndPalletsFile)) availableDatasets.push_back(datasetId);
    }

    sort(availableDatasets.begin(), availableDatasets.end());
    return availableDatasets;
}

DataSet getDataset(string datasetId) {
    if (!checkDatasetExists(datasetId)) { throw invalid_argument("Dataset does not exist."); }

    string basePath   = "datasets/";
    string truckFile  = basePath + "TruckAndPallets_" + datasetId + ".csv";
    string palletFile = basePath + "Pallets_" + datasetId + ".csv";

    ifstream truckFileStream(truckFile);
    ifstream palletFileStream(palletFile);

    if (!truckFileStream.is_open() || !palletFileStream.is_open())
        throw runtime_error("Failed to open dataset files.");

    Truck      truck      = getTruckFromFile(truckFileStream);
    PalletList palletList = getPalletListFromFile(palletFileStream);

    return make_pair(truck, palletList);
}
