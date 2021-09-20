#include <stdbool.h>

// detect_win determines if board represents a winning state
// requires: eval and board are valid pointers
// effects: modifies *eval
// time: O(1)
bool detect_win(const char *board, int *eval);

// minimax(board, turn, eval) generates the optimal move for
//   turn player given board state
// requires: eval and board are valid pointers
// effects: modifies *eval
// time: O(n) where n is the number of states stemming from board
int minimax(char *board, char turn, int *eval);
