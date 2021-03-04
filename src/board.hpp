#pragma once
#include <fmt/format.h>

#include <algorithm>
#include <array>
#include <span>
#include <string>
#include <tl/numeric-aliases.hpp>

#include "cell.hpp"

namespace Tre {
struct Coord {
  constexpr Coord() = default;
  constexpr Coord(tl::usize r, tl::usize c)
    : row(r)
    , col(c) {}

  tl::usize row;
  tl::usize col;
};

template <auto Row, auto Col>
class Board {
 public:
  constexpr Board() {
    for (auto row = 0ULL; row < Row; ++row) {
      for (auto col = 0ULL; col < Col; ++col) { b_[row][col] = Cell{}; }
    }
  }

  constexpr void initialize_cells(std::span<const Coord> indexes) const {
    std::ranges::for_each(indexes, [&](auto const &coord) {
      this->b_[coord.row][coord.col].make_alive();
    });
  }

  void print(const auto &board) const {
    fmt::print("+{:-^{}}+\n", "", Col);
    auto result = std::string{};
    for (auto row = 0ULL; row < Row; ++row) {
      result.push_back('|');
      for (auto col = 0ULL; col < Col; ++col) {
        if (board[row][col].state() == State::alive) {
          result.push_back('*');
        } else {
          result.push_back(' ');
        }
      }
      result.push_back('|');
      result.push_back('\n');
    }
    fmt::print("{}", result);
    fmt::print("+{:-^{}}+\n", "", Col);
  }

  auto board() const { return this->b_; }

 private:
  mutable std::array<std::array<Cell, Row>, Col> b_{};
};
}  // namespace Tre
