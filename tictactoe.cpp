/* filename: tictactoe.cpp:
Tic Tac Toe AI using Minimax algorithm

1. AI engine
** Main idea of the algorithm: Represents winning conditions as 1 for X and -1 for O. X will make actions trying to maximize the final
score, while O trying to minimize the score.

- Define state of board as a vector of vectors of chars (vector<std::vector<char>>)
- Define a move as a vector of two integers i and j, where i corresponding to the row of the move and j corresponding to the collumn 
of the move

- Main functions:
    + getPlayer(s): Given state s, return which player's turn it is
    + getMoves(s): Given state s, return all the legal moves in that state
    + play(s, a, p): Given state s, action a, player p, return the board resulted from player p performing the action a on state s
    + isFinalState: Given state s, check whether this is the final state
    + getFinalStateScore(s): Given a final state s, return its score (1 if X won, -1 if O won, 0 if draw)
    + getScore(s): Given state s, return its score

2. User interface
- Prompt the user for their move inputs
- Response if the move is ilegal
- Print the result base on the outcome of the game ("X win!" if X has won the game, "O win!" if O has won the game, "Draw!" if the 
game has ended in a tie)
*/

#include <iostream>
#include <vector>

using namespace std;

// Define state of board as a vector of vectors of chars
typedef vector<vector<char> > State;

void renderGame(State board)
// Take a state as input and render it to the terminal
{
    for (int r = 0; r < 3; r++)
    {
        cout << "|";
        for (int c = 0; c < 3; c++)
        {
            cout << board[r][c] << "|";
        }
        cout << endl;
    }
}

char getPlayer (State board)
// Accept a state as input and return which player's turn it is (X or O)
{
    int count = 0;
    for (int  r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == 'X')
            {
                count++;
            }
            else if (board[r][c] == 'O') 
            {
                count--;
            }
        }
    }
    if (count == 0)
    {
        return 'X';
    }
    return 'O';
}

vector <vector<int>> getMoves(State board)
// Accept a state as input and return all the legal moves in this state (what cells are free on the board).
{
    vector <vector<int>> available_moves;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            // If tile is empty, add tile to availabe moves
            if (board[r][c] == ' ')
            {
                available_moves.push_back({r, c});
            }
        }
    }
    return available_moves;
}

State play(State board, vector<int> moves, char player)
// Take a state, a moves (represented by vector of two integers i and j, where i corresponding to the row of the move 
//and j corresponding to the collumn of the move), a player whose turn it is as inputs

// Return a new state result from taking the input the action to the original input state
{
    State newBoard;
    for (int r = 0; r < 3; r++)
    {
        newBoard.push_back(board[r]);
    }
    newBoard[moves[0]][moves[1]] = player;
    return newBoard;
}

vector <State> getNextStates(State board, char player)
// Accept a state as input and return all the possible outcomes from that state
{
    vector <State> nextStates;
    vector <vector<int>>  moves = getMoves(board);
    for (vector <int> move: moves)
    {
        nextStates.push_back(play(board, move, player));
    }
    return nextStates;
}

bool isFinalState(State board)
// Take a state as input and return  a boolean value indicating whether the game is over or not (true if the game's ended, false otherwise)

// The returned score should be 1 if X won the game, -1 if O won the game, 0 if the game ended in a tie
{

    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') return true;

    // Check columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ') return true;

    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') return true;
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') return true;

    // Check full
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

int getFinalStateScore(State board)
// Accept a state as input and return its score

// The returned score should be 1 if X won the game, -1 if O won the game, 0 if the game ended in a tie
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
        {
            return (board[i][0] == 'X') ? 1: -1;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
        {
            return (board[0][i] == 'X') ? 1: -1;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
    {
        return (board[0][0] == 'X') ? 1: -1;
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
    {
        return (board[0][2] == 'X') ? 1: -1;
    }
    return 0;
}

pair <int, vector<int>> getScore(State board)
// Accept a state as input and get the scores of all the possible next states (using recursion)

// The function should then return the action with the best score it found (highest if the player is X, lowest if the player is O), along with the score
{
    if (isFinalState(board))
    {
        vector <int> test = {0, 0};
        return make_pair(getFinalStateScore(board), test);
    }
    char player = getPlayer(board);
    int bestScore = 100;
    vector <int> bestMove;
    for (vector <int> m: getMoves(board))
    {
        State new_board = play(board, m, getPlayer(board));
        pair <int, vector<int>> best = getScore(new_board);
        int score = best.first;
        if (player == 'X')
        {
            if (score > bestScore || bestScore == 100)
            {   
                bestScore = score;
                bestMove = m;
            }
        }
        else
        {
            if (score < bestScore || bestScore == 100)
            {
                bestScore = score;
                bestMove = m;
            }
        }
    }
    return make_pair(bestScore, bestMove);
}

int main()
{
    State board {{' ',' ',' '},
                 {' ',' ',' '},
                 {' ',' ',' '}};
    char player;
    cout << "Choose your player (X or O): ";
    cin >> player;
    int i = 0;
    while (!isFinalState(board))
    {
        int currentPlayer = (i % 2 == 0) ? 'X': 'O';    
        if (currentPlayer == player)
        {
            vector <int> moves (2, 0);
            cout << "You play: ";
            cin >> moves[0] >> moves[1];
            board = play(board, moves, player);
            renderGame(board);
        }
        else
        {
            vector <int> botMove = getScore(board).second;
            cout << "I play: " << botMove[0] << " " << botMove[1] << endl;
            board = play(board, botMove, currentPlayer);
            renderGame(board);
        }

        // Check if the game ended
        if (isFinalState(board))
        {
            int finalScore =  getFinalStateScore(board);
            if (finalScore == 1)
            {
                cout << "X win!" << endl;
            }
            else if (finalScore == 0)
            {
                cout << "Draw!" << endl;
            }
            else
            {
                cout << "O win!" << endl;
            }
            break;
        }

        // Switch player
        i++;
    }
    return 0;
}