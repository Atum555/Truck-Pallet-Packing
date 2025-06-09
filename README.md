# Truck Pallet Packing - Algorithm Design Project

This project consists in implementing a simple command-line C++ tool capable of parsing data files, running different algorithms and showing their proposed solution to the truck pallet packing problem (adapted version of Knapsack's problem).

## Implemented Algorithms

### 1. Brute Force

Explores all possible combinations of pallets to find the optimal solution. This approach guarantees the best answer but is only feasible for a small number of pallets due to its exponential time complexity.

### 2. Brute Force Backtracking

Uses recursion and backtracking to systematically explore all combinations, pruning branches early when the current selection exceeds the truck's capacity. This can be more efficient than plain brute force but still has exponential complexity.

### 3. Greedy Algorithm

Sorts pallets by a heuristic (profit-to-weight ratio) and selects them in order until the truck is full. This method is fast and simple but does not guarantee an optimal solution.

### 4. Dynamic Programming

Solves the problem using a bottom-up approach, building a table of optimal solutions for subproblems (combinations of pallets and capacities). This guarantees an optimal solution with much better performance than brute force for moderate input sizes.

### 5. Genetic Algorithm (In-Depth)

The genetic algorithm is a population-based metaheuristic inspired by natural evolution. It is designed to efficiently search large solution spaces and find near-optimal solutions for complex problems like the truck pallet packing problem.

**Key Steps:**

-   **Initialization:**  
    A population of random candidate solutions (individuals) is generated. Each individual represents a possible selection of pallets (a binary genome).

-   **Fitness Evaluation:**  
    Each individual is evaluated using a fitness function, which measures the total profit of the selected pallets without exceeding the truck's capacity.

-   **Selection:**  
    Multiple selection strategies are used to choose parents for reproduction:

    -   _Elitism:_ The top-performing individuals are preserved unchanged.
    -   _Tournament Selection:_ Groups of individuals compete, and the best in each group is selected as a parent.
    -   _Roulette Wheel Selection:_ Individuals are selected probabilistically based on fitness.
    -   _Random Selection:_ Some individuals are replaced with new random solutions to maintain diversity.

-   **Crossover (Recombination):**  
    Selected parents are paired, and their genomes are combined at a random crossover point to produce offspring, mixing features from both parents.

-   **Mutation:**  
    With a small probability, random bits in the offspring's genome are flipped to introduce new genetic material and prevent premature convergence.

-   **Replacement:**  
    The new generation replaces the old one, with elites preserved. The process repeats for a set number of generations or until no improvement is observed.

-   **Termination:**  
    The algorithm stops when the best solution does not improve for a specified number of generations.

**Advantages:**

-   Can efficiently explore large and complex solution spaces.
-   Balances exploitation (using good solutions) and exploration (trying new solutions).
-   Flexible and adaptable to different problem constraints.

**Limitations:**

-   Does not guarantee the absolute optimal solution.
-   Requires careful tuning of parameters (population size, mutation rate, etc.).

---

Each algorithm offers a different trade-off between speed and solution quality. The genetic algorithm is particularly useful for large instances where exact methods become impractical.
