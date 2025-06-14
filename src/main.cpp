#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "algorithms.hpp"
#include "parsers.hpp"
#include "utils.hpp"

using namespace std;

bool verboseMode = false;

vector<string> algorithmNames
    = { "Brute-Force", "Greedy", "Dynamic Programming", "Backtracking", "Genetic Programming" };

Algorithms selectAlgorithm() {
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

void writeResultsToCSV(
    const std::string &filename, const std::vector<std::tuple<std::string, std::string, double, int>> &results
) {
    std::ofstream file(filename);
    file << "Algorithm,Dataset,ExecutionTime(ms),Profit" << std::endl;
    for (const auto &[algorithm, dataset, time, profit] : results) {
        file << algorithm << "," << dataset << "," << time << "," << profit << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && string(argv[1]) == "measure") {
        // Check for verbose flag
        for (int i = 1; i < argc; ++i) {
            if (string(argv[i]) == "-v") {
                verboseMode = true;
                break;
            }
        }

        if (argc < 5) {
            cerr << "Usage: ./da_project measure (all | algorithm-number) dataset-number (number of runs) [-v]" << endl;
            return 1;
        }

        string      algorithm = argv[2];
        string      datasetId = argv[3];
        std::size_t runs      = std::stoull(argv[4]);

        cout << "Algorithm: " << algorithm << ", Dataset: " << datasetId << ", Runs: " << runs << endl;

        vector<Algorithms> algorithmsToTest;
        if (algorithm == "all") {
            algorithmsToTest = { Algorithms::BruteForce, Algorithms::Greedy, Algorithms::DynamicProgramming,
                                 Algorithms::Backtracking, Algorithms::GeneticProgramming };
        } else {
            int algorithmNumber;

            try {
                algorithmNumber = stoi(algorithm);
            } catch (const std::exception &e) {
                cerr << "Usage: ./da_project measure (all | algorithm-number) dataset-number (number of runs) [-v]"
                     << endl;
                return 1;
            }

            if (algorithmNumber < 1 || algorithmNumber > 5) {
                cerr << "Invalid algorithm number. Must be between 1 and 6." << endl;
                return 1;
            }
            algorithmsToTest = { static_cast<Algorithms>(algorithmNumber - 1) };
        }

        if (!checkDatasetExists(datasetId)) {
            cerr << "Dataset " << datasetId << " does not exist." << endl;
            return 1;
        }

        DataSet dataSet = getDataset(datasetId);

        // Map to store total execution time and count for each algorithm
        map<string, pair<double, int>> algorithmStats;

        // Update the output to display the algorithm name instead of its number
        for (const auto &algorithm : algorithmsToTest) {
            cout << "Testing algorithm: " << algorithmNames[static_cast<int>(algorithm)] << endl;
            for (std::size_t i = 0; i < runs; ++i) {
                if (verboseMode) cout << "Run " << i + 1 << " on dataset: " << datasetId;

                // Measure execution time and collect results
                auto       start = chrono::high_resolution_clock::now();
                PalletList solution;

                switch (algorithm) {
                case Algorithms::BruteForce        : solution = bruteForce(dataSet); break;
                case Algorithms::Greedy            : solution = greedy(dataSet); break;
                case Algorithms::DynamicProgramming: solution = dynamicProgramming(dataSet); break;
                case Algorithms::Backtracking      : solution = bruteForceBacktracking(dataSet); break;
                case Algorithms::GeneticProgramming: solution = genetic(dataSet, false); break;
                }

                auto   end           = chrono::high_resolution_clock::now();
                double executionTime = chrono::duration<double, milli>(end - start).count();

                if (verboseMode) cout << " Execution Time: " << executionTime << " ms" << endl;

                // Update algorithm stats
                algorithmStats[algorithmNames[static_cast<int>(algorithm)]].first += executionTime;
                algorithmStats[algorithmNames[static_cast<int>(algorithm)]].second++;
            }
        }

        // Display a summary of average results
        cout << "\nSummary of Average Results:" << endl;
        for (const auto &[algorithm, stats] : algorithmStats) {
            double averageTime = stats.first / stats.second;
            cout << "Algorithm: " << algorithm << ", Average Execution Time: " << averageTime << " ms" << endl;
        }

        return 0;
    }

    // Normal mode logic
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
        solution = bruteForceBacktracking(dataSet);
        clearScreen();
        cout << "Backtracking algorithm selected." << endl;
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
