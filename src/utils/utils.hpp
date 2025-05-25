
#ifndef UTILS_HPP
#define UTILS_HPP

#include <istream>
#include <string>

// Types
enum Algorithms { BruteForce, Greedy, DynamicProgramming, Backtracking, GeneticProgramming };

enum Color { Clear, Red, Cyan, Green, Grey, Yellow };

// Functions
void         clearScreen();
void         setScreenColor(Color color);
std::string &trim(std::string &s);
void         readLine(std::istream &in, std::string &line);

#endif // UTILS_HPP
