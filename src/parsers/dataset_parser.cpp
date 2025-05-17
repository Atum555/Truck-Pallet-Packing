#include "parsers.hpp"
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

vector<int> getAvailableDatasets() {
    vector<int> availableDatasets;
    string      basePath = "datasets/";

    for (const auto &entry : filesystem::directory_iterator(basePath)) {
        string filename = entry.path().filename().string();

        // Check if the file matches the pattern "Pallets_<number>.csv"
        if (!(filename.find("Pallets_") == 0 && filename.find(".csv") == filename.size() - 4))
            continue;

        string numberStr = filename.substr(8, filename.size() - 12); // Extract the number part
        try {
            int datasetNumber = stoi(numberStr);

            // Check if the corresponding TruckAndPallets file exists
            string truckAndPalletsFile = basePath + "TruckAndPallets_" + numberStr + ".csv";
            if (filesystem::exists(truckAndPalletsFile)) availableDatasets.push_back(datasetNumber);
        }

        // Ignore files with invalid numbers
        catch (const invalid_argument &e) {}
    }

    sort(availableDatasets.begin(), availableDatasets.end());
    return availableDatasets;
}

bool checkDatasetExists(int number) {
    vector<int> availableDatasets = getAvailableDatasets();
    return find(availableDatasets.begin(), availableDatasets.end(), number)
           != availableDatasets.end();
}
