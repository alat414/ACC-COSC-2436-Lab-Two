#include<iostream>
#include<cassert>
#include<string>
#include<vector>


bool validPosition(int row, int col, int rows, int left_dia, int right_dia, int n)
{
    return !((rows >> row) & 1) && 
           !((left_dia >> (row + col)) & 1) && 
           !((right_dia >> (row - col + n - 1)) & 1);
}

void queenPosition(int col, int n, std::vector<int>& board, 
                   std::vector<std::vector<int>>& result, 
                   int rows, int left_dia, int right_dia)
{

    if(col == n)
    {
        result.push_back(board);
        return;
    }

    for (int row = 0; row <= n; row++)
    {
        if(validPosition(row, col, rows, left_dia, right_dia, n))
        {
            board.push_back(row);

            queenPosition(col + 1, n, board, result, 
                          rows | (1 << row),
                         (left_dia | (1 << (row + col))),
                         (right_dia | (1 << (row - col + n))));
            
            board.pop_back();
        }
    }

}

std::vector<std::vector<int>> nQueen(int n)
{
    std::vector<std::vector<int>> result;

    std::vector<int> board;

    queenPosition(0, n, board, result, 0, 0, 0);

    return result;
}

void displayChessBoard(const std::vector<int> & solution)
{
    int n = solution.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (solution[j] == i)
            {
                std::cout << "Q ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
int main()
{
    int n = 8;
    std::vector<std::vector<int>> result = nQueen(n);

    std::cout<< "There are " << result.size() << " solutions for " << n << "queens\n\n";

    int solutionDisplay = 3;

    for (int i = 0; i < solutionDisplay && i < result.size(); i++)
    {
        std::cout << "Solution " << (i + 1) << ":\n";
        std::cout << "Board positions: [";
        for (int j = 0; j < n; j++)
        {
            std::cout << result[i][j];
            if(j != n - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << "]\n";

        std::cout << "Chess board display \n";

        displayChessBoard(result[i]);

        std::cout << "\n" << std::string(20, '-') << "\n\n";
    }
    return 0;
}

