#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

#include "parsers.hpp"
#include "utils.hpp"

using namespace std;

Algorithms selectAlgorithm() {
    vector<string> algorithmNames
        = { "Brute-Force",        "Greedy", "Dynamic Programming", "Backtracking", "Integer Linear Programming",
            "Genetic Programming" };


    while (true) {
        clearScreen();

        setScreenColor(Color::Cyan);
        cout << "Available Algorithms: " << endl;
        setScreenColor(Color::Clear);

        for (size_t i = 0; i < algorithmNames.size(); ++i) cout << i + 1 << ". " << algorithmNames[i] << endl;

        cout << endl;

        setScreenColor(Color::Cyan);
        cout << "Algorithm to use: ";
        setScreenColor(Color::Clear);

        string input;
        readLine(cin, input);
        trim(input);

        if (input == "1") return Algorithms::BruteForce;
        else if (input == "2") return Algorithms::Greedy;
        else if (input == "3") return Algorithms::DynamicProgramming;
        else if (input == "4") return Algorithms::Backtracking;
        else if (input == "5") return Algorithms::ILP;
        else if (input == "6") return Algorithms::Genetic;
    }
}

DataSet selectDataSet() {
    vector<string> datasets = getAvailableDatasets();

    if (datasets.empty()) {
        cout << "No datasets available." << endl;
        throw runtime_error("No datasets available.");
    }


    while (true) {
        clearScreen();

        setScreenColor(Color::Cyan);
        cout << "Available datasets: ";
        setScreenColor(Color::Clear);

        for (string datasetId : datasets) cout << datasetId << " ";
        cout << endl << endl;

        setScreenColor(Color::Cyan);
        cout << "Dataset to load: ";
        setScreenColor(Color::Clear);

        string selectedDataset;
        readLine(cin, selectedDataset);
        trim(selectedDataset);

        if (find(datasets.begin(), datasets.end(), selectedDataset) != datasets.end())
            return getDataset(selectedDataset);
    }
}

int main() {
    Algorithms algorithm = selectAlgorithm();
    DataSet    dataSet   = selectDataSet();
    clearScreen();

    switch (algorithm) {
    case Algorithms::BruteForce:
        cout << "Brute-Force algorithm selected." << endl;
        // Add Brute-Force algorithm logic here
        break;

    case Algorithms::Greedy:
        cout << "Greedy algorithm selected." << endl;
        // Add Greedy algorithm logic here
        break;

    case Algorithms::DynamicProgramming:
        cout << "Dynamic Programming algorithm selected." << endl;
        // Add Dynamic Programming algorithm logic here
        break;

    case Algorithms::Backtracking:
        cout << "Backtracking algorithm selected." << endl;
        // Add Backtracking algorithm logic here
        break;

    case Algorithms::ILP:
        cout << "Integer Linear Programming algorithm selected." << endl;
        // Add ILP algorithm logic here
        break;

    case Algorithms::Genetic:
        cout << "Genetic Programming algorithm selected." << endl;
        // Add Genetic Programming algorithm logic here
        break;

    default: cout << "Unknown algorithm selected." << endl; break;
    }

    return 0;
}
