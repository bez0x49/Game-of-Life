#include "Universe.h"

#include <algorithm>
#include <array>
#include <thread>

using namespace std;

Universe::Universe(const size_t width, const size_t height)
    : _rows(height), _columns(width), _grid(width * height), dist(0, 4) {
  random_device rd;
  auto seed_data = array<int, mt19937::state_size>{};
  generate(begin(seed_data), end(seed_data), ref(rd));
  seed_seq seq(begin(seed_data), end(seed_data));
  mt.seed(seq);
}

void Universe::run(const Seed seed, const int generations,
                   const chrono::milliseconds ms) {
  reset();
  initialize(seed);
  display();

  int i = 0;
  do {
    nextGeneration();
    display();

    using namespace chrono_literals;
    this_thread::sleep_for(ms);
  } while (i++ < generations || generations == 0);
}

void Universe::nextGeneration() {
  vector<unsigned char> newgrid(_grid.size());

  for (size_t r = 0; r < _rows; r++) {
    for (size_t c = 0; c < _columns; c++) {
      auto count = countNeighbors(r, c);

      if (cell(c, r) == Alive) {
        newgrid[r * _columns + c] = (count == 2 || count == 3) ? Alive : Dead;
      } else {
        newgrid[r * _columns + c] = (count == 3) ? Alive : Dead;
      }
    }
  }

  _grid.swap(newgrid);
}

void Universe::resetDisplay() {
#ifdef __linux__
  system("clear");
#elif _WIN32
  system("cls");
#endif
}

void Universe::display() {
  resetDisplay();

  for (size_t r = 0; r < _rows; r++) {
    for (size_t c = 0; c < _columns; c++) {
      cout << (cell(c, r) ? "\u258a" : " ");
    }
    cout << endl;
  }
}

void Universe::initialize(const Seed seed) {
  if (seed == Seed::TenCellRow) {
    for (size_t c = _columns / 2 - 5; c < _columns / 2 + 5; c++)
      cell(c, _rows / 2) = Alive;
  } else {
    for (size_t r = 0; r < _rows; r++) {
      for (size_t c = 0; c < _columns; c++) {
        cell(c, r) = dist(mt) == 0 ? Alive : Dead;
      }
    }
  }
}

void Universe::reset() {
  for (size_t r = 0; r < _rows; r++) {
    for (size_t c = 0; c < _columns; c++) {
      cell(c, r) = Dead;
    }
  }
}

int Universe::countNeighbors(const size_t row, const size_t col) {
  if (row == 0 && col == 0)
    return countAlive(cell(1, 0), cell(1, 1), cell(0, 1));
  if (row == 0 && col == _columns - 1)
    return countAlive(cell(_columns - 2, 0), cell(_columns - 2, 1),
                      cell(_columns - 1, 1));
  if (row == _rows - 1 && col == 0)
    return countAlive(cell(0, _rows - 2), cell(1, _rows - 2),
                      cell(1, _rows - 1));
  if (row == _rows - 1 && col == _columns - 1)
    return countAlive(cell(_columns - 1, _rows - 2),
                      cell(_columns - 2, _rows - 2),
                      cell(_columns - 2, _rows - 1));
  if (row == 0 && col > 0 && col < _columns - 1)
    return countAlive(cell(col - 1, 0), cell(col - 1, 1), cell(col, 1),
                      cell(col + 1, 1), cell(col + 1, 0));
  if (row == _rows - 1 && col > 0 && col < _columns - 1)
    return countAlive(cell(col - 1, row), cell(col - 1, row - 1),
                      cell(col, row - 1), cell(col + 1, row - 1),
                      cell(col + 1, row));
  if (col == 0 && row > 0 && row < _rows - 1)
    return countAlive(cell(0, row - 1), cell(1, row - 1), cell(1, row),
                      cell(1, row + 1), cell(0, row + 1));
  if (col == _columns - 1 && row > 0 && row < _rows - 1)
    return countAlive(cell(col, row - 1), cell(col - 1, row - 1),
                      cell(col - 1, row), cell(col - 1, row + 1),
                      cell(col, row + 1));
  return countAlive(cell(col - 1, row - 1), cell(col, row - 1),
                    cell(col + 1, row - 1), cell(col + 1, row),
                    cell(col + 1, row + 1), cell(col, row + 1),
                    cell(col - 1, row + 1), cell(col - 1, row));
}

unsigned char &Universe::cell(const size_t col, const size_t row) {
  return _grid[row * _columns + col];
}