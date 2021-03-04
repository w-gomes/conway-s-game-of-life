#pragma once

namespace Tre {

enum class State {
  alive,
  dead,
};

class Cell {
 public:
  constexpr Cell() = default;
  constexpr explicit Cell(State state)
    : state_(state) {}

  [[nodiscard]] constexpr State state() const { return state_; }
  constexpr void make_alive() { state_ = State::alive; }
  constexpr void make_dead() { state_ = State::dead; }

 private:
  State state_ = State::dead;
};

}  // namespace Tre
