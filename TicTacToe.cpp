#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

// ==========================================
// 1. ENUMS (Strict Type Definitions)
// ==========================================
enum class PieceType
{
    EMPTY,
    X,
    O
};

// Helper function to print enums cleanly
char getPieceChar(PieceType type)
{
    if (type == PieceType::X)
        return 'X';
    if (type == PieceType::O)
        return 'O';
    return ' ';
}

// ==========================================
// 2. PLAYER CLASS (Encapsulation)
// ==========================================
class Player
{
private:
    string name;
    PieceType playingPiece;

public:
    Player(string playerName, PieceType piece) : name(playerName), playingPiece(piece) {}

    string getName() const { return name; }
    PieceType getPiece() const { return playingPiece; }
};

// ==========================================
// 3. BOARD CLASS (State Management)
// ==========================================
class Board
{
private:
    int size;
    vector<vector<PieceType>> grid;
    int freeCells;

public:
    // Constructor initializes an NxN board
    Board(int boardSize) : size(boardSize), freeCells(boardSize * boardSize)
    {
        grid.resize(size, vector<PieceType>(size, PieceType::EMPTY));
    }

    void printBoard() const
    {
        cout << "\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << " " << getPieceChar(grid[i][j]) << " ";
                if (j < size - 1)
                    cout << "|";
            }
            cout << "\n";
            if (i < size - 1)
            {
                for (int k = 0; k < size; k++)
                    cout << "----";
                cout << "\n";
            }
        }
        cout << "\n";
    }

    bool isCellFree(int row, int col) const
    {
        if (row < 0 || row >= size || col < 0 || col >= size)
            return false;
        return grid[row][col] == PieceType::EMPTY;
    }

    void addPiece(int row, int col, PieceType piece)
    {
        grid[row][col] = piece;
        freeCells--;
    }

    bool hasFreeCells() const
    {
        return freeCells > 0;
    }

    int getSize() const { return size; }

    PieceType getPieceAt(int row, int col) const
    {
        return grid[row][col];
    }
};

// ==========================================
// 4. GAME CLASS (Main System Controller)
// ==========================================
class Game
{
private:
    Board *board;
    deque<Player *> players; // Queue to manage turns

    // Algorithm to check if the current move wins the game
    bool checkWinner(int row, int col, PieceType piece)
    {
        int n = board->getSize();
        bool rowMatch = true, colMatch = true, diagMatch = true, antiDiagMatch = true;

        for (int i = 0; i < n; i++)
        {
            if (board->getPieceAt(row, i) != piece)
                rowMatch = false;
            if (board->getPieceAt(i, col) != piece)
                colMatch = false;
            if (board->getPieceAt(i, i) != piece)
                diagMatch = false;
            if (board->getPieceAt(i, n - 1 - i) != piece)
                antiDiagMatch = false;
        }

        return rowMatch || colMatch || diagMatch || antiDiagMatch;
    }

public:
    Game(int boardSize, Player *p1, Player *p2)
    {
        board = new Board(boardSize);
        players.push_back(p1);
        players.push_back(p2);
    }

    ~Game()
    {
        delete board;
    }

    void play()
    {
        bool gameOver = false;

        cout << "--- Game Started ---";
        board->printBoard();

        while (!gameOver && board->hasFreeCells())
        {
            // Get the player whose turn it is
            Player *currentPlayer = players.front();
            players.pop_front();

            int row, col;
            bool validMove = false;

            // Input loop with move validation
            while (!validMove)
            {
                cout << currentPlayer->getName() << "'s turn (" << getPieceChar(currentPlayer->getPiece()) << "). Enter row and column (0 to " << board->getSize() - 1 << "): ";
                cin >> row >> col;

                if (board->isCellFree(row, col))
                {
                    validMove = true;
                }
                else
                {
                    cout << "Invalid move! Cell is out of bounds or already occupied. Try again.\n";
                }
            }

            // Place piece and print board
            board->addPiece(row, col, currentPlayer->getPiece());
            board->printBoard();

            // Check win condition
            if (checkWinner(row, col, currentPlayer->getPiece()))
            {
                cout << "WINNER: Congratulations " << currentPlayer->getName() << ", you won!\n";
                gameOver = true;
            }

            // Put player back at the end of the queue for the next turn
            players.push_back(currentPlayer);
        }

        if (!gameOver)
        {
            cout << "DRAW: The game ended in a tie!\n";
        }
    }
};

// ==========================================
// 5. DRIVER CODE (Simulation)
// ==========================================
int main()
{
    // Setup Players
    Player p1("Alice", PieceType::X);
    Player p2("Bob", PieceType::O);

    // Setup Game (3x3 Board)
    Game ticTacToeGame(3, &p1, &p2);

    // Start Game
    ticTacToeGame.play();

    return 0;
}