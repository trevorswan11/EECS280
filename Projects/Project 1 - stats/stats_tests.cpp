/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */

#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

// Precision for floating point comparison
const double epsilon = 0.00001;

static bool almost_equal(double x, double y)
{
    return abs(x - y) < epsilon;
}

void test_sum_small_data_set();

// Add prototypes for you test functions here.
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_min();
void test_max();
void test_stdev();
void test_percentile();
void test_filter();

int main()
{
    // Given test case
    test_sum_small_data_set();

    // Call your test functions here
    test_count();
    test_sum();
    test_mean();
    test_median();
    test_min();
    test_max();
    test_stdev();
    test_percentile();
    test_filter();

    return 0;
}

void test_sum_small_data_set()
{
    cout << "test_sum_small_data_set" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);

    assert(sum(data) == 6);
    assert(almost_equal(sum(data), 6));

    cout << "PASS!" << endl;
}

// Add the test function implementations here. I'm not going to do them
void test_count()
{
    cout << "test_count" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_sum()
{
    cout << "test_sum" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_mean()
{
    cout << "test_mean" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_median()
{
    cout << "test_median" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_min()
{
    cout << "test_min" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_max()
{
    cout << "test_max" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_stdev()
{
    cout << "test_stdev" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_percentile()
{
    cout << "test_percentile" << endl;

    assert(false);

    cout << "PASS!" << endl;
}

void test_filter()
{
    cout << "test_filter" << endl;

    assert(false);

    cout << "PASS!" << endl;
}