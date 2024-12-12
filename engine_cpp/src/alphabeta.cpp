#include "./alphabeta.h"

int AlphaBeta::evaluate(int max_piece) {
    auto rival_piece = 1 - max_piece;
    auto num_turned_moves = m_game.get_available_moves(max_piece).size();
    auto num_rival_moves = m_game.get_available_moves(rival_piece).size();
    int turned_score = 0;
    int rival_score = 0;
    if (num_turned_moves == 0) {
        turned_score = m_min_score;
    } else {
        turned_score = num_turned_moves * 2;
    }
    if (num_rival_moves == 0) {
        rival_score = m_min_score;
    } else {
        rival_score = num_rival_moves * 2;
    }
    turned_score =
        m_game.get_board_state().m_pieces_count[max_piece] * 10 + turned_score;
    rival_score =
        m_game.get_board_state().m_pieces_count[rival_piece] * 10 + rival_score;
    return turned_score - rival_score;
}

int AlphaBeta::alphabeta(int max_piece, int depth, int alpha, int beta) {
    auto result = m_game.check_is_game_over();
    if (result.is_over) {
        if (result.winner == max_piece) {
            return m_max_score - depth;
        }
        return m_min_score + depth;
    }
    if (depth == m_max_depth) {
        return evaluate(max_piece);
    }
    bool is_max_player = false;
    if (depth % 2 == 0) {
        is_max_player = true;
    }
    auto turned_piece = m_game.get_board_state().m_turned_piece;
    auto moves = m_game.get_available_moves(turned_piece);
    for (int i = 0; i < moves.size(); i++) {
        auto &move = moves[i];
        game.do_move(move);
        auto score = alphabeta(max_piece, depth + 1, alpha, beta);
        game.undo_the_last_move();
        if (is_max_player) {
            if (score > alpha) {
                alpha = score;
                if (depth == 0) {
                    m_best_move = move;
                }
                if (score >= beta) {
                    return beta;
                }
            }
        } else {
            if (score < beta) {
                beta = score;
                if (score <= alpha) {
                    return alpha;
                }
            }
        }
    }
    if (is_max_player) {
        return alpha;
    }
    return beta;
}
