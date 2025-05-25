#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

#include "algorithms.hpp"
#include "parsers.hpp"
#include "utils.hpp"

using namespace std;

Algorithms selectAlgorithm() {
    vector<string> algorithmNames
        = { "Brute-Force",        "Greedy", "Dynamic Programming", "Backtracking", "Integer Linear Programming",
            "Genetic Programming" };

    bool error = false;
    while (true) {
        clearScreen();

        setScreenColor(Color::Cyan);
        cout << "Available Algorithms: " << endl;
        setScreenColor(Color::Clear);

        for (size_t i = 0; i < algorithmNames.size(); ++i) cout << i + 1 << ". " << algorithmNames[i] << endl;

        cout << endl;

        if (error) {
            setScreenColor(Color::Red);
            cout << "Invalid Input!" << endl;
            setScreenColor(Color::Clear);
        }

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
        else if (input == "6") return Algorithms::GeneticProgramming;
        error = true;
    }
}

DataSet selectDataSet() {
    vector<string> datasets = getAvailableDatasets();

    if (datasets.empty()) {
        cout << "No datasets available." << endl;
        throw runtime_error("No datasets available.");
    }

    bool error = false;
    while (true) {
        clearScreen();

        setScreenColor(Color::Cyan);
        cout << "Available datasets: ";
        setScreenColor(Color::Clear);

        for (string datasetId : datasets) cout << datasetId << " ";
        cout << endl << endl;

        if (error) {
            setScreenColor(Color::Red);
            cout << "Invalid Input!" << endl;
            setScreenColor(Color::Clear);
        }

        setScreenColor(Color::Cyan);
        cout << "Dataset to load: ";
        setScreenColor(Color::Clear);

        string selectedDataset;
        readLine(cin, selectedDataset);
        trim(selectedDataset);

        if (find(datasets.begin(), datasets.end(), selectedDataset) != datasets.end())
            return getDataset(selectedDataset);
        else error = true;
    }
}

int main() {
    Algorithms algorithm = selectAlgorithm();
    DataSet    dataSet   = selectDataSet();
    PalletList solution;
    clearScreen();

    switch (algorithm) {
    case Algorithms::BruteForce:
        solution = bruteForce(dataSet);
        clearScreen();
        cout << "Brute-Force algorithm selected." << endl;
        break;

    case Algorithms::Greedy:
        solution = greedy(dataSet);
        clearScreen();

        cout << "Greedy algorithm selected." << endl;
        break;

    case Algorithms::DynamicProgramming:
        solution = dynamicProgramming(dataSet);
        clearScreen();
        cout << "Dynamic Programming algorithm selected." << endl;
        // Add Dynamic Programming algorithm logic here
        break;

    case Algorithms::Backtracking:
        clearScreen();
        cout << "Backtracking algorithm selected." << endl;
        // Add Backtracking algorithm logic here
        break;

    case Algorithms::ILP:
        clearScreen();
        cout << "Integer Linear Programming algorithm selected." << endl;
        // Add ILP algorithm logic here
        break;

    case Algorithms::GeneticProgramming:
        solution = genetic(dataSet);
        clearScreen();
        cout << "Genetic Programming algorithm selected." << endl;
        break;

    default: cout << "Unknown algorithm selected." << endl; break;
    }

    cout << solution << endl;

    return 0;
}
