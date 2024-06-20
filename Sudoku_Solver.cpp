#include <bits/stdc++.h>

using namespace std;

const int n = 9;

// This function checks if the puzzle is solved or not
bool issolved(vector<vector<int>> &a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if there is any 0 in the puzzle then it is not complete.
            if (a[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// returns the position that needs to be filled
pair<int, int> tobefilled(vector<vector<int>> &a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if at certain position 0 is present it needs to be filled.
            if (a[i][j] == 0)
            {
                return {i, j};
            }
        }
    }
}

// prints the entire sudoku puzzle.
void print(vector<vector<int>> &a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

// This function checks if 'i' is present in particular row or not.
bool presentinrow(vector<vector<int>> &a, int row, int column, int i)
{
    for (int j = 0; j < n; j++)
    {
        if (a[row][j] == i)
        {
            return true;
        }
    }
    return false;
}

// This function checks if 'i' is present in particular column or not.
bool presentincolumn(vector<vector<int>> &a, int row, int column, int i)
{
    for (int j = 0; j < n; j++)
    {
        if (a[j][column] == i)
        {
            return true;
        }
    }
    return false;
}

// This function checks if 'i' is present in the corresponding 3×3 matrix.
bool presentinbox(vector<vector<int>> &a, int row, int column, int i)
{
    pair<int, int> topleft = {row - row % 3, column - column % 3};
    for (int j = topleft.first; j < topleft.first + 3; j++)
    {
        for (int k = topleft.second; k < topleft.second + 3; k++)
        {
            if (a[j][k] == i)
            {
                return true;
            }
        }
    }
    return false;
}

// This function checks if certain position can be filled with 'i'.
bool canbefilledwith(int i, vector<vector<int>> &a, int row, int column)
{
    // can be filled with 'i' only if it is not present in the corresponding
    // row,column and 3×3 matrix
    if (!presentinbox(a, row, column, i) &&
        !presentincolumn(a, row, column, i) &&
        !presentinrow(a, row, column, i))
    {
        return true;
    }

    return false;
}

// returns whether the sudoku can be solved with the progress made with it.
bool cansolve(vector<vector<int>> &a)
{

    if (issolved(a))
        return true;
    else
    {
        // finds an empty position.
        pair<int, int> tbf = tobefilled(a);
        for (int i = 1; i <= 9; i++)
        {
            // checks if it can be filled with any number from 1 to 9
            if (canbefilledwith(i, a, tbf.first, tbf.second))
            {
                // if yes it updates and recursively progresses.
                a[tbf.first][tbf.second] = i;
                if (cansolve(a))
                {
                    return true;
                }
                // if that update doesnot solve the sudoku
                // We backtrack and try different number.
                a[tbf.first][tbf.second] = 0;
            }
        }
    }
    return false;
}

int main()
{
    // this vector of vectors stores the sudoku.
    vector<vector<int>> a;
    int input;
    for (int i = 0; i < n; i++)
    {
        vector<int> b;
        // represents each row.
        for (int j = 0; j < n; j++)
        {
            cin >> input;
            if (input >= 0 && input <= n)
            {
                b.push_back(input);
            }
            else
            {
                cout << "Invalid input" << endl;
                return 0;
            }
        }
        a.push_back(b);
    }
    if (cansolve(a))
        print(a);
    else
    {
        cout << "No solution exists" << endl;
    }
}

/*
smaple inputs

0 4 0 1 0 2 6 5 7
2 7 3 6 8 5 4 1 9
0 6 0 9 0 4 2 8 3
0 9 0 3 2 8 7 0 5
0 5 7 4 0 9 0 6 2
4 2 8 5 6 7 3 9 1
0 3 2 0 0 1 0 7 4
7 1 4 2 0 6 9 3 8
0 8 0 7 4 0 1 2 6

0 0 6 0 0 1 4 8 0
0 3 2 0 0 0 0 7 0
0 0 0 8 2 0 3 0 9
0 0 8 0 1 3 0 0 0
2 0 5 0 4 7 0 3 0
0 0 7 0 0 6 5 0 0
0 0 0 1 7 2 0 0 3
1 0 0 3 0 0 9 0 0
7 0 0 0 0 0 0 0 8


*/
