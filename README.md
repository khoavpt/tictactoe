# Tic Tac Toe AI using Minimax algorithm

## 1. AI engine
###  Main idea of the algorithm:
Represents winning conditions as 1 for X and -1 for O. X will make actions trying to maximize the final
score, while O trying to minimize the score.

### Implementation
- Define state of board as a vector of vectors of chars (vector<std::vector<char>>)

- Define a move as a vector of two integers i and j, where i corresponding to the row of the move and j corresponding to the collumn 
of the move

- Main functions:
    + getPlayer(s): Given state s, return which player's turn it is (X or O)
    + getMoves(s): Accept state s as input and return all the legal moves in this state (what cells are free on the board).
    + play(s, a, p): Take a state s, a moves a (represented by vector of two integers i and j, where i corresponding to the row of the move and j corresponding to the collumn of the move), a player p whose turn it is as inputs. The function return a new state resulted from player p performing the action a on state s
    + isFinalState: Take a state s as input and return  a boolean value indicating whether the game is over or not (true if the game's ended, false otherwise)
    + getFinalStateScore(s): Accept a state s as input and return its score. The returned score should be 1 if X won the game, -1 if O won the game, 0 if the game ended in a tie
    + getScore(s): Accept a state s as input and get the scores of all the possible next states (using recursion). The function should then return the action with the best score it found (highest if the player is X, lowest if the player is O), along with the score

## 2. User interface
- Prompt the user for their move inputs
- Response if the move is ilegal
- Print the result base on the outcome of the game ("X win!" if X has won the game, "O win!" if O has won the game, "Draw!" if the 
game has ended in a tie)
