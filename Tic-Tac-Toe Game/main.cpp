#include <iostream>

using namespace std;

constexpr size_t GRID_SIZE = 3;
constexpr size_t PLAYERS_COUNT = 2;
constexpr size_t WINNING_LINE_LENGTH = 3;
constexpr char EMPTY_SPACE = ' ';

void playGame(char grid[][GRID_SIZE], bool& isWinner);

unsigned getSequenceCount(const char grid[][GRID_SIZE], size_t row, size_t column, int rowDirection, int columnDirection);
unsigned getSequenceOnLine(const char grid[][GRID_SIZE], size_t row, size_t column, int rowDirection, int columnDirection);
bool checkForWinner(const char grid[][GRID_SIZE], size_t row, size_t column);

void readInput(const char grid[][GRID_SIZE], int& x, int& y);
bool isValidInput(int x, int y);

void init(char grid[][GRID_SIZE], size_t rows, size_t columns, char ch);
void printGrid(char grid[][GRID_SIZE], size_t rows, size_t columns);
void refreshScreen();

int main()
{
    char grid[GRID_SIZE][GRID_SIZE];

    init(grid, GRID_SIZE, GRID_SIZE, EMPTY_SPACE);
    printGrid(grid, GRID_SIZE, GRID_SIZE);

    bool isWinner = false;
    playGame(grid, isWinner);

    cout << (isWinner ? "Congratulations! You won the game!" : "Draw!") << endl;

    return 0;
}

void playGame(char grid[][GRID_SIZE], bool& isWinner)
{
    for (int i = 0, currentPlayer = 0; i < GRID_SIZE * GRID_SIZE && !isWinner; i++, (++currentPlayer) %= PLAYERS_COUNT)
    {
        int x, y;
        readInput(grid, x, y);

        grid[x][y] = 'A' + currentPlayer;

        refreshScreen();
        printGrid(grid, GRID_SIZE, GRID_SIZE);

        isWinner = checkForWinner(grid, x, y);
    }
}

bool checkForWinner(const char grid[][GRID_SIZE], size_t row, size_t column)
{
    return getSequenceOnLine(grid, row, column, 1, 0) >= WINNING_LINE_LENGTH ||
        getSequenceOnLine(grid, row, column, 0, 1) >= WINNING_LINE_LENGTH ||
        getSequenceOnLine(grid, row, column, 1, 1) >= WINNING_LINE_LENGTH ||
        getSequenceOnLine(grid, row, column, 1, -1) >= WINNING_LINE_LENGTH;
}

unsigned getSequenceOnLine(const char grid[][GRID_SIZE], size_t row, size_t column, int rowDirection, int columnDirection)
{
    return getSequenceCount(grid, row, column, rowDirection, columnDirection) +
        getSequenceCount(grid, row, column, -rowDirection, -columnDirection) - 1;
}

unsigned getSequenceCount(const char grid[][GRID_SIZE], size_t row, size_t column, int rowDirection, int columnDirection)
{
    char symbol = grid[row][column];
    unsigned count = 0;

    while (isValidInput(row, column) && grid[row][column] == symbol)
    {
        count++;
        row += rowDirection;
        column += columnDirection;
    }

    return count;
}

void readInput(const char grid[][GRID_SIZE], int& x, int& y)
{
    do
    {
        cin >> x >> y;
    } while (!isValidInput(x, y) || grid[x][y] != EMPTY_SPACE);
}

bool isValidInput(int x, int y)
{
    return x >= 0 && y >= 0 && x < GRID_SIZE && y < GRID_SIZE;
}

void init(char grid[][GRID_SIZE], size_t rows, size_t columns, char ch)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            grid[i][j] = ch;
}

void printGrid(char grid[][GRID_SIZE], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
            cout << '[' << grid[i][j] << ']';
        cout << endl;
    }
}

void refreshScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}