#include <algorithm>
#include <iostream>

#include "utils.hpp"

using namespace std;

void clearScreen() { cout << "\033[2J\033[1;1H"; }

void setScreenColor(Color color) {
    switch (color) {
    case Color::Red   : cout << "\033[31m"; break;
    case Color::Cyan  : cout << "\033[36m"; break;
    case Color::Green : cout << "\033[32m"; break;
    case Color::Grey  : cout << "\033[90m"; break;
    case Color::Yellow: cout << "\033[33m"; break;

    default: cout << "\033[0m"; break;
    }
}

void readLine(istream &in, string &line) {
    if (not getline(in, line)) exit(EXIT_SUCCESS);
}

string &trim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
    return s;
}
