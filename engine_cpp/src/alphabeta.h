#pragma once
#include "game.h"

class AlphaBeta {
  public:
    AlphaBeta(Game &game, int max_depth)
        : m_game(game), m_max_depth(max_depth) {}

    int evaluate(int max_piece);
    int alphabeta(int max_piece, int depth, int alpha, int beta);

    int m_min_score = -1000;
    int m_max_score = 1000;
    Move m_best_move;

  private:
    int m_max_depth = 6;
    Game &m_game;
};
