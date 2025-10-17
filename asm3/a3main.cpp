#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "a3.h"
using namespace std;

struct TestResult
{
    string funcName;
    string testName;
    int reported;
    int expected;
    int diff;
};

int cartesianProductCost(int arr[], int n)
{
    return 3 * n * n + 3 * n + 3;
}

// Generic runner for a function and its cost version
template <typename Func, typename CostFunc, typename... Args>
void runTest(vector<TestResult> &results,
             const string &funcName,
             const string &testName,
             Func func,
             CostFunc costFunc,
             Args... args)
{
    int reportedCost = 0;
    func(args..., reportedCost);
    int expectedCost = costFunc(args...);
    int diff = abs(expectedCost - reportedCost);

    results.push_back({funcName, testName, reportedCost, expectedCost, diff});
}

int main()
{
    vector<TestResult> results;

    int arr1[] = {1, 2, 3};
    int arr2[] = {5, 10, 15, 20};
    int mat1[] = {1, 2, 3, 4};
    int mat2[] = {2, 0, 0, 2};

    // Silence function output
    streambuf *oldCout = cout.rdbuf();
    ofstream devnull("/dev/null");
    cout.rdbuf(devnull.rdbuf());

    // ---- TEST CASES ----

    // cartesianProduct
    runTest(results, "cartesianProduct", "3 elements",
            cartesianProduct, cartesianProductCost, arr1, 3);
    runTest(results, "cartesianProduct", "4 elements",
            cartesianProduct, cartesianProductCost, arr2, 4);

    // triangle
    runTest(results, "triangle", "n=3",
            triangle, triangleCost, 3);
    runTest(results, "triangle", "n=10",
            triangle, triangleCost, 10);

    // matrixSelfMultiply
    runTest(results, "matrixSelfMultiply", "2x2 #1",
            matrixSelfMultiply, matrixSelfMultiplyCost, mat1, 2);
    runTest(results, "matrixSelfMultiply", "2x2 #2",
            matrixSelfMultiply, matrixSelfMultiplyCost, mat2, 2);

    // bsort
    runTest(results, "bsort", "3 elements",
            bsort, bsortCost, arr1, 3, 0);
    runTest(results, "bsort", "4 elements",
            bsort, bsortCost, arr2, 4, 0);

    // pattern
    runTest(results, "pattern", "n=3",
            pattern, patternCost, 3, 0);
    runTest(results, "pattern", "n=8",
            pattern, patternCost, 8, 0);

    // tt
    runTest(results, "tt", "n=3",
            tt, ttCost, 3);
    runTest(results, "tt", "n=6",
            tt, ttCost, 6);

    // Restore output
    cout.rdbuf(oldCout);

    // ---- PRINT RESULTS ----
    cout << "=== COST TEST SUMMARY ===\n\n";
    cout << "Function                 Test Case          Reported  Expected  Diff\n";
    cout << "---------------------------------------------------------------------\n";

    for (const auto &r : results)
    {
        cout << left
             << setw(24) << r.funcName
             << setw(18) << r.testName
             << setw(10) << r.reported
             << setw(10) << r.expected
             << setw(5) << r.diff
             << "\n";
    }

    cout << "\n=== ALL TESTS COMPLETE ===\n";
    return 0;
}
