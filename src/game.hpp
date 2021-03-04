#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <span>
#include <thread>
#include <tl/numeric-aliases.hpp>

#include "board.hpp"

namespace Tre {

template <auto Row, auto Col>
class Game {
  constexpr static auto board_size = Row;

 public:
  constexpr Game() = default;

  constexpr void run(std::span<const Coord> arr) const {
    using namespace std::chrono_literals;
    static_assert(Row == Col, "Row and Col should be equal");

    this->board_.initialize_cells(arr);
    auto board = this->board_.board();

    // main loop
    while (true) {
      auto next_board = board;
      this->board_.print(next_board);
      for (auto row = 0ULL; row < board_size; ++row) {
        for (auto col = 0ULL; col < board_size; ++col) {
          // cell's neighbors
          const auto subrng = std::array<Cell, 8>{
            board[get_idx(row, -1)][get_idx(col, -1)],
            board[get_idx(row, -1)][get_idx(col, 0)],
            board[get_idx(row, -1)][get_idx(col, 1)],
            board[get_idx(row, 0)][get_idx(col, -1)],
            board[get_idx(row, 0)][get_idx(col, 1)],
            board[get_idx(row, 1)][get_idx(col, -1)],
            board[get_idx(row, 1)][get_idx(col, 0)],
            board[get_idx(row, 1)][get_idx(col, 1)],
          };
          auto &current = next_board[row][col];

          const auto n_neighbors = this->count_neighbors(subrng);
          if (current.state() == State::dead) {
            if (n_neighbors == 3) { current.make_alive(); }
          } else {
            if (n_neighbors < 2 || n_neighbors > 3) {
              current.make_dead();
            } else if (n_neighbors == 2 || n_neighbors == 3) {
              if (current.state() == State::alive) { current.make_alive(); }
            }
          }
        }
      }

      std::ranges::swap(board, next_board);
      std::this_thread::sleep_for(500ms);
    }
  }

 private:
  constexpr auto get_idx(tl::usize idx, int flag) const -> tl::usize {
    if (flag == -1) {
      const auto temp_idx = static_cast<tl::i64>(idx);
      const auto result   = temp_idx - 1;
      if (result < 0) {
        return static_cast<tl::usize>(board_size - std::abs(result));
      } else {
        return static_cast<tl::usize>((idx - 1) % board_size);
      }
    } else if (flag == 1) {
      return static_cast<tl::usize>((idx + 1) % board_size);
    } else if (flag == 0) {
      return static_cast<tl::usize>(idx);
    }
    // FIXME:
    return 0ULL;
  }

  constexpr auto count_neighbors(std::span<const Cell> cells) const {
    return std::ranges::count_if(
      cells, [](const auto &c) { return c.state() == State::alive; });
  }

  mutable Board<Row, Col> board_{};
};
}  // namespace Tre
