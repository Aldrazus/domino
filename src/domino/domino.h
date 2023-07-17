#ifndef DOMINO_H
#define DOMINO_H

#include <cstddef>
#include <deque>
#include <ostream>
#include <unordered_set>
#include <vector>

namespace domino {
struct Tile {
  int left;
  int right;

  Tile flip() { return Tile{right, left}; }

  bool operator==(const Tile& otherTile) const {
    return left == otherTile.left && right == otherTile.right;
  }

  struct HashFunction {
    std::size_t operator()(const Tile& tile) const {
      return std::hash<int>()(tile.left) ^ (std::hash<int>()(tile.right) << 1);
    }
  };
};

using TileSet = std::unordered_set<Tile, Tile::HashFunction>;

struct Player {
  TileSet hand;
};

using PlayerId = std::size_t;

enum class LineEnd { left, right };

struct Move {
  PlayerId player;
  Tile tile;
  LineEnd end;

  bool operator==(const Move& m) const {
    return player == m.player && tile == m.tile && end == m.end;
  }

  struct HashFunction {
    std::size_t operator()(const Move& m) const {
      // I HAVE NO IDEA WHAT I'M DOING
      return std::hash<PlayerId>()(m.player) ^ std::hash<int>()(m.tile.left) ^
             std::hash<int>()(m.tile.right) ^ std::hash<LineEnd>()(m.end);
    }
  };
};

using MoveSet = std::unordered_set<Move, Move::HashFunction>;

class Domino {
 public:
  Domino();
  Domino(std::vector<Player> players, std::deque<Tile> board, PlayerId);
  std::vector<Player> players;
  std::deque<Tile> board;
  PlayerId turn;

  inline int numPlayers() const { return players.size(); }

  void move(Move m);

  bool isValid(Move m);

  bool isValid();

  MoveSet moves();

 private:
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);
std::ostream& operator<<(std::ostream& os, const Player& player);
}
#endif
