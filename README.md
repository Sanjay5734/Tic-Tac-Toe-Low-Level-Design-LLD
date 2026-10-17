# Tic Tac Toe - Low-Level Design (LLD)

This repository contains a Low-Level Design (LLD) implementation of a terminal-based **Tic Tac Toe** game in C++. The project demonstrates scalable Object-Oriented Programming (OOP) principles, state management, and an algorithmic approach to evaluating win conditions on an NxN grid.

## Problem Statement
Design an object-oriented system for a terminal-based Tic Tac Toe game. The system must manage a game board, multiple players taking turns, strict move validation, and dynamic detection of win or draw conditions.

### System Requirements
* **The Board:** An NxN scalable grid (default 3x3).
* **Players:** Two players participate, uniquely assigned playing pieces (e.g., 'X' and 'O').
* **Turn Management:** Players alternate turns. The system must manage a queue of players.
* **Move Validation:** Players can only place symbols on empty cells within the grid boundaries. Invalid moves trigger a retry prompt.
* **Win Condition:** The game immediately ends when a player places *N* of their symbols in a continuous horizontal, vertical, or diagonal line.
* **Draw Condition:** The game ends in a tie if the board reaches capacity without a winner.

---

## System Architecture & OOP Concepts (Interview Guide)

When presenting this LLD in an interview, you must articulate the core OOP principles and algorithms driving the logic.

### Core OOP Principles Applied:
* **Single Responsibility Principle (SOLID):** The `Board` class is strictly responsible for maintaining state and boundaries. The `Game` class strictly handles business logic, turn-taking, and win validation.
* **Encapsulation:** The 2D grid matrix and the count of `freeCells` are hidden within the `Board` class as private variables, modifiable only through the secure `addPiece` method.
* **Type Safety:** Used strictly scoped `enum class PieceType` for pieces to eliminate logical bugs caused by arbitrary character or integer inputs.

### Class Relationships:
* **Composition:** The `Game` *has-a* `Board`. When the `Game` instance is destroyed, the dynamically allocated `Board` is cleaned up.
* **Aggregation:** The `Game` holds references to `Player`s via a double-ended queue (`std::deque`). Players exist independently of the game session.

### Scalable Algorithms (NxN Matrix):
* **O(N) Win Validation:** Instead of brute-forcing the entire board to check for a winner (which is $O(N^2)$), the `checkWinner` algorithm only evaluates the specific row, column, and diagonals associated with the *most recently placed piece*, resulting in highly efficient $O(N)$ time complexity.

---

## System Flow

1. **Initialization:** `Player` objects are created and passed to the `Game` controller along with the desired board size. The `Board` initializes an NxN matrix of empty enums.
2. **Turn Flow:** `Game` pops the front `Player` from a `deque` and requests coordinates.
3. **Validation:** `Board` checks array boundaries and cell occupancy. If valid, the piece is placed.
4. **Evaluation:** `Game` runs `checkWinner()` to scan the active row, column, and diagonals. 
5. **Loop/End:** If a win or draw is detected, the loop breaks. Otherwise, the current player is pushed to the back of the queue, and the cycle continues.

---

## How to Run

1. Clone the repository to your local machine.
2. Open your terminal and navigate to the project directory.
3. Compile the C++ file using GCC or Clang:
   ```bash
   g++ tic_tac_toe.cpp -o tic_tac_toe
   ./tic_tac_toe
