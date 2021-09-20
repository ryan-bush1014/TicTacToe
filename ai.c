#include "ai.h"

// see ai.h for details
bool detect_win(const char *board, int *eval)
{
    // vertical
    for (int x = 0; x < 3; ++x)
    {
        if (board[x] == board[3 + x] && board[x] == board[6 + x])
        {
            if (board[x] == 'x')
            {
                *eval = 1;
                return true;
            }
            else if (board[x] == 'o')
            {
                *eval = -1;
                return true;
            }
        }
    }
    // horizontal
    for (int y = 0; y < 3; ++y)
    {
        if (board[3 * y] == board[1 + 3 * y] && board[3 * y] == board[2 + 3 * y])
        {
            if (board[3 * y] == 'x')
            {
                *eval = 1;
                return true;
            }
            else if (board[3 * y] == 'o')
            {
                *eval = -1;
                return true;
            }
        }
    }
    // diagonal
    if ((board[0] == board[4] && board[0] == board[8]) || (board[6] == board[4] && board[6] == board[2]))
    {
        if (board[4] == 'x')
        {
            *eval = 1;
            return true;
        }
        else if (board[4] == 'o')
        {
            *eval = -1;
            return true;
        }
    }
    return false;
}

// opposite(turn) generates the opposite value of turn
// requires: turn is either 'x' or 'o'
// time: O(1)
static char opposite(char turn)
{
    if (turn == 'x')
    {
        return 'o';
    }
    return 'x';
}

// see ai.h for details
int minimax(char *board, char turn, int *eval)
{
    if (detect_win(board, eval))
    {
        return -1;
    }
    int best_move = -1;
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == ' ')
        {
            board[i] = turn;
            int curr_eval = 0;
            minimax(board, opposite(turn), &curr_eval);
            board[i] = ' ';
            if (best_move == -1 || (turn == 'x' && curr_eval > *eval) || (turn == 'o' && curr_eval < *eval))
            {
                *eval = curr_eval;
                best_move = i;
            }
        }
    }
    return best_move;
}
