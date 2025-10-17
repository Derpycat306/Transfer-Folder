#include <iostream>
#include <math.h>
using namespace std;

// total cost = 3n^2 + 3n + 3
void cartesianProduct(int arr[], int n, int &cost)
{
    int i = 0;
    cost++;

    while (i < n) // 3n^2 + 3n + 1
    {
        int j = 0;
        while (j < n) // 3n: 2 prints and j++
        {
            cout << "{" << arr[i] << "," << arr[j] << "}";
            j++;
            cout << " ";
            cost += 3;
        }

        cout << endl;
        i++;
        cost += 3;
    }

    cost++;
}

void triangle(int x, int &cost)
{
    int i = 0;
    while (i < x)
    {
        int j = 0;
        while (j <= i)
        {
            cout << j << " ";
            j++;
        }

        cout << endl;
        i++;
    }

    while (i > 0)
    {
        i--;
        int j = 0;
        while (j <= i)
        {
            cout << j << " ";
            j++;
        }
        cout << endl;
    }
}

// Returns the index of a 1d array representing a matrix
// given row (r) and column (c) values
int rcIndex(int r, int c, int columns, int &cost)
{
    cost++;
    return r * columns + c;
}

// PRE: m represents a square matrix of size rows * rows
// PARAM: rows represents the number of both rows and columns
// POST: Returns a pointer to an array (matrix) of the same size as m
// NOTE: values are indexed r0c0,r0c1,…,r0cn-1,r1c0,…
int *matrixSelfMultiply(int *m, int rows, int &cost)
{
    // Create result array
    int columns = rows;
    int *result = new int[rows * columns];
    int r = 0;

    while (r < rows)
    {
        int c = 0;
        while (c < columns)
        { // columns = rows
            int next = 0;
            int iNext = 0;

            while (iNext < rows)
            {
                next += m[rcIndex(r, iNext, columns, cost)] * m[rcIndex(iNext, c, columns, cost)];
                iNext++;
            }

            result[rcIndex(r, c, columns, cost)] = next;
            c++;
        }
        r++;
    }
    return result;
}

// PARAM: arr is array to be sorted, n is size of array, i should initially = 0
void bsort(int arr[], int n, int i, int &cost)
{
    // Bubble down each element
    if (i < n - 1)
    {
        // Last i elements are in correct position
        int j = 0;
        while (j < n - i - 1)
        {
            // Compare elements
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        bsort(arr, n, i + 1, cost);
    }
}

// PRE: n is a power of 2 greater than zero.
// PRE: Initial call should be to i = 0
// e.g. pattern(8, 0)
void pattern(int n, int i, int &cost)
{
    if (n > 0)
    {
        pattern(n / 2, i, cost);
        // Print i spaces
        cout << string(i, ' ');

        // A loop to print n asterisks, each one followed by a space
        int ast = 0;
        while (ast < n)
        {
            cout << "* ";
            ast++;
        }

        cout << endl;
        i += n;
        pattern(n / 2, i, cost);
    }
}

// Desc: Prints the first n columns of an n variable truth table
void tt(int n, int &cost)
{
    int rows = (int)pow(2, n);
    int columns = n;
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < columns)
        {
            if ((r / (int)pow(2, n - c - 1)) < 1)
            {
                cout << "T ";
            }
            else
            {
                cout << "F ";
            }
            c++;
        }
        r++;
        cout << endl;
    }
}