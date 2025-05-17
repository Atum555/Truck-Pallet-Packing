#include "parsers/parsers.hpp"
#include <iostream>

using namespace std;

int main() {
    vector<int> datasets = getAvailableDatasets();

    cout << "Available datasets: ";
    for (int dataset : datasets) cout << dataset << " ";
    cout << endl;

    return 0;
}
