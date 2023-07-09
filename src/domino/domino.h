#ifndef DOMINO_H
#define DOMINO_H

#include <ostream>
#include <vector>

namespace domino {
struct Tile {
  int left;
  int right;
};

struct Player {
  std::vector<Tile> hand;
};

enum class LineEnd { left, right };

struct Move {
  int player;
  Tile tile;
  LineEnd end;
};

class Game {
 public:
  Game();
  std::vector<Player> players;
  std::vector<Tile> board;
  int turn;

  inline int numPlayers() const { return players.size(); }

  void move(Move move);
  std::vector<Move> moves();

 private:
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);
std::ostream& operator<<(std::ostream& os, const Player& player);
}
#endif
