#pragma once
#include <vector>
using namespace std;
#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

void find_minmax(vector<double> numbers, double& min, double& max);
void show_histogram_text(const vector<size_t>& bins);
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count);

#endif// HISTOGRAM_H_INCLUDED
