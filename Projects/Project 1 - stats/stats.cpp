// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath>     // sqrt, modf

using namespace std;

// Can also iterate, not sure of project spec (both here work)
int count(vector<double> v)
{
    return v.size();
    // int count;
    // for (count = 0; count < v.size(); ++count) {}
    // return count;
}

double sum(vector<double> v)
{
    double sum = 0;
    for (int i = 0; i < v.size(); ++i) sum += v[i];
    return sum;
}

// double / count -> double
double mean(vector<double> v)
{
    int v_size = count(v);
    return v_size == 0 ? 0 : sum(v) / v_size; 
}

// modulo is lovely isn't it
double median(vector<double> v)
{
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    sort(v.begin(), v.end());
    if (v_size % 2 == 0)
        return (v[v_size / 2 - 1] + v[v_size / 2]) / 2;
    else
        return v[v_size / 2];
}

// Avoid using sort here, most likely an nlogn algorithm, but this is linear
double min(vector<double> v)
{
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    double min = v[0];
    for (int i = 1; i < v_size; ++i)
        if (v[i] < min)
            min = v[i];
    return min;
}

// Avoid using sort here, most likely an nlogn algorithm, but this is linear
double max(vector<double> v)
{
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
    double avg = mean(v);
    for (int i = 0; i < v_size; ++i)
        sum_squares += (v[i] - avg) * (v[i] - avg);
    return sqrt(sum_squares / (v_size - 1));
}

double percentile(vector<double> v, double p)
{
    if (p < 0 || p > 1)
        return 0;
    int v_size = count(v);
    if (v_size == 0)
        return 0;
    sort(v.begin(), v.end());
    int rank = p * v_size + 1;
    double int_part, frac_part;
    frac_part = modf(rank, &int_part);
    return v[int_part - 1] + frac_part * (v[int_part] - v[int_part - 1]); 
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
