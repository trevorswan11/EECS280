// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath>     // sqrt, modf

using namespace std;

int count(vector<double> v)
{
    // Can also iterate, not sure of project spec
    return v.size();
}

double sum(vector<double> v)
{
    double sum = 0;
    for (int i = 0; i < v.size(); ++i) sum += v[i];
    return sum;
}

double mean(vector<double> v)
{
    // double / count -> double
    int v_size = count(v);
    return v_size == 0 ? 0 : sum(v) / v_size; 
}

double median(vector<double> v)
{
    // modulo is lovely isn't it
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    sort(v.begin(), v.end());
    if (v_size % 2 == 0)
        return (v[v_size / 2 - 1] + v[v_size / 2]) / 2;
    else
        return v[v_size / 2];
}

double min(vector<double> v)
{
    // Avoid using sort here, most likely an nlogn algorithm, but this is linear
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    double min = v[0];
    for (int i = 1; i < v_size; ++i)
        if (v[i] < min)
            min = v[i];
    return min;
}

double max(vector<double> v)
{
    // Avoid using sort here, most likely an nlogn algorithm, but this is linear
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    double max = v[0];
    for (int i = 1; i < v_size; ++i)
        if (v[i] > max)
            max = v[i];
    return max;
}

double stdev(vector<double> v)
{
    double sum_squares = 0;
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    else if (v_size == 1)
        return v[0];
    double avg = mean(v);
    for (int i = 0; i < v_size; ++i)
        sum_squares += (v[i] - avg) * (v[i] - avg);
    return sqrt(sum_squares / (v_size - 1));
}

double percentile(vector<double> v, double p)
{
    // Handle edge cases
    if (p < 0 || p > 1)
        return 0;
    int v_size = count(v);
    if (v_size == 0)
        return 0;

    sort(v.begin(), v.end());
    double rank = p * (v_size - 1);
    double int_part, frac_part;

    // Split rank into integer and fractional parts
    frac_part = modf(rank, &int_part);
    int index = static_cast<int>(int_part); // also could use (int)int_part

    // Prevent index out of bounds
    if (index + 1 < v_size)
        return v[index] + frac_part * (v[index + 1] - v[index]);
    // If index is at the end of the vector
    else 
        return v[index];
}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target)
{
    int v_size = count(v);
    int criteria_size = count(criteria);
    if (v_size == 0 || criteria_size == 0 || v_size != criteria_size)
        return vector<double>();
    vector<double> filtered;
    for (int i = 0; i < v_size; ++i)
        if (criteria[i] == target)
            filtered.push_back(v[i]);
    return filtered;
}
