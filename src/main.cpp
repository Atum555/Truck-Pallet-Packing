#include <algorithm>
#include <iostream>
#include <string>

#include "parsers.hpp"

using namespace std;

int main() {
    vector<string> datasets = getAvailableDatasets();

    cout << "Available datasets: ";
    for (string datasetId : datasets) cout << datasetId << " ";
    cout << endl;

    if (datasets.empty()) {
        cout << "No datasets available." << endl;
        return 0;
    }

    string selectedDataset;
    while (true) {
        cout << "Enter the dataset ID to load: ";
        cin >> selectedDataset;

        if (find(datasets.begin(), datasets.end(), selectedDataset) != datasets.end()) break;
        else cout << "Invalid dataset ID. Please try again." << endl;
    }


    try {
        auto [truck, palletList] = getDataset(selectedDataset);

        cout << "Truck Information:" << endl;
        cout << truck << endl;

        cout << "Pallets Information:" << endl;
        cout << palletList << endl;
    } catch (const exception &e) { cout << "Error: " << e.what() << endl; }

    return 0;
}
