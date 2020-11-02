/**
 * @file Universe.h
 * @author bez0x49 (bez0x49@github.com, nevedrb@gmail.com)
 * @brief The class universe presented below implements the game as described.
 * @version 0.1
 * @date 2020-11-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once
#include "stdafx.h"

class Universe {
 private:
  // Deleting default constructor
  Universe() = delete;

 public:
  // Seed for the starting layout
  enum class Seed {
    // Random layout
    Random,
    // Line of 10 cells in the middle of the grid
    TenCellRow
  };

 public:
  /**
   * @brief Create layout with width and height
   *
   * @param width   Width of layout
   * @param height  Height of layout
   */
  Universe(const size_t width = DefaultWidth,
           const size_t height = DefaultHeight);


  /**
   * @brief Initializes the starting layout and then produces a new generation
   *   at a user-specified interval, for a user-specified number of
   *   iterations, or indefinitely  (if the number of iterations was set to 0).
   *
   * @param seed        Generation of layout
   * @param generations Number of generations
   * @param ms          Time after a new generation appeared
   */
  void run(const Seed seed, const int generations,
           const std::chrono::milliseconds ms = std::chrono::milliseconds(100));

 private:
  // Produces a new stage of the game based on the transition rules.
  void nextGeneration();

  // Clear the console
  void resetDisplay();

  // Shows the game status on the console; this uses a system call to earase
  // the console, although you could use other means to do so, such as specific
  // operating system APIs
  void display();

  /**
   * @brief Generates a starting layout
   *
   * @param seed  Option to generation
   */
  void initialize(const Seed seed);

  // Sets all the cells as dead
  void reset();

  template <typename... T>
  auto countAlive(T&&... args) {
    return (args + ...);
  }

  /**
   * @brief It uses a helper variadic function template countAlive().
   *
   * @param row Row of grid
   * @param col Column of grid
   * @return Number of alive neighbors
   */
  int countNeighbors(const size_t row, const size_t col);

  /**
   * @brief Returns the cell depending on the position in layout
   *
   * @param col Column of grid
   * @param row Row of grid
   * @return Cell
   */
  unsigned char& cell(const size_t col, const size_t row);

  static const size_t DefaultWidth = 50;
  static const size_t DefaultHeight = 50;

 private:
  size_t _rows;
  size_t _columns;

  enum Life : unsigned char { Dead, Alive };

  std::vector<unsigned char> _grid;

  std::uniform_int_distribution<> dist;
  std::mt19937 mt;
};