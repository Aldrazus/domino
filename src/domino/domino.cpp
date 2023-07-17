#include "domino.h"
#include <array>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>
#include <unordered_set>
#include <vector>

namespace domino {
std::ostream& operator<<(std::ostream& os, const Tile& tile) {
  return os << tile.left << ":" << tile.right;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
  for (Tile tile : player.hand) {
    os << tile << ",";
  }
  return os;
}

Domino::Domino() {
  // TODO: allow for 2-4 players
  const int numPlayers = 4;

  std::vector<Tile> tiles;

  const int maxPips = 6;

  // Generate tiles
  for (int i = 0; i <= maxPips; i++) {
    for (int j = i; j <= maxPips; j++) {
      tiles.push_back(Tile{i, j});
    }
  }

  // Shuffle tiles
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(tiles.begin(), tiles.end(), g);

  const int numTiles = (maxPips + 1) * (maxPips + 2) / 2;
  const int handSize = numTiles / numPlayers;

  // Distribute tiles to each player
  for (int i = 0; i < numPlayers; i++) {
    std::unordered_set<Tile, Tile::HashFunction> hand{};
    for (int j = 0; j < handSize; j++) {
      hand.insert(tiles[(i * handSize) + j]);
    }
    players.push_back(Player{hand});
  }
}

Domino::Domino(std::vector<Player> players, std::deque<Tile> board,
               std::size_t turn)
    : players(players), board(board), turn(turn) {}

void Domino::move(Move m) {
  if (!isValid(m)) {
    // TODO: do something here lol
    return;
  }

  players[m.player].hand.erase(m.tile);
  if (m.end == LineEnd::left) {
    board.push_front(m.tile);
  } else {
    board.push_back(m.tile);
  }

  // TODO: support 2-4 players
  turn = (turn + 1) % 4;
}

bool Domino::isValid(Move m) {
  if (!players[m.player].hand.contains(m.tile)) {
    return false;
  }

  if (board.size() == 0) {
    return m.tile.left + m.tile.right == 12;
  }

  if (m.end == LineEnd::left) {
    return m.tile.right == board.front().left;
  } else {
    return m.tile.left == board.back().right;
  }
}

// Checks if board is valid
bool Domino::isValid() {
  // TODO
  return true;
}

MoveSet Domino::moves() {
  const Player player = players[turn];
  MoveSet moves{};

  for (Tile tile : player.hand) {
    bool isDoubleSix = tile.left + tile.right == 12;
    if (board.size() == 0 && isDoubleSix) {
      moves.insert(Move{turn, tile, LineEnd::left});
      continue;
    }

    if (board.front().left == tile.right) {
      moves.insert(Move{turn, tile, LineEnd::left});
    }

    if (board.back().right == tile.left) {
      moves.insert(Move{turn, tile, LineEnd::right});
    }

    if (tile.left != tile.right) {
      Tile flipped = tile.flip();
      if (board.front().left == flipped.right) {
        moves.insert(Move{turn, flipped, LineEnd::left});
      }

      if (board.back().right == flipped.left) {
        moves.insert(Move{turn, flipped, LineEnd::right});
      }
    }
  }
  return moves;
};
}
