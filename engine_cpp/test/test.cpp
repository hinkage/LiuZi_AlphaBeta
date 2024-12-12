#include "../src/alphabeta.h"
#include <iostream>

int main() {
    printf("main\n");

    // 不减枝时，能不卡顿的最大层数是8
    AlphaBeta alphabeta(game, 10);

    while (true) {
        auto result = game.check_is_game_over();
        if (result.is_over) {
            printf("winner is %d\n", result.winner);
            break;
        }
        alphabeta.alphabeta(game.get_board_state().m_turned_piece, 0,
                            alphabeta.m_min_score, alphabeta.m_max_score);
        auto m = alphabeta.m_best_move;
        game.do_move(m);
        printf("%s\n", game.get_board_state().to_string().c_str());
        getchar();
    }

    return 0;
}
