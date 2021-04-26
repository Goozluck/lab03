#include "histogram.h"
#include"svg.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Input{
vector<double> numbers;
size_t bin_count;
};

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in){
Input data;
cerr<<"Enter number count: ";
size_t number_count;
in >> number_count;

cerr<<" Enter numbers: ";
data.numbers =input_numbers(in,number_count);


cerr <<"Enter bin count: ";
size_t bin_count;
in >> bin_count;

return data;
}

vector<size_t>
make_histogram(Input data) {
    vector<size_t> bins(data.bin_count);
    double min, max, bin_size;
    find_minmax(data.numbers, min, max);
    bin_size = (max - min) / data.bin_count;
    for (double i :data. numbers)
    {
        bool found = false;
        for (size_t j = 0; (j < data.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= i) && (i < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[data.bin_count - 1]++;
        }
    }
    return bins;
}



void
show_histogram_text(const vector<size_t>& bins) {
    size_t max_count = bins[0];
    for (size_t j : bins)
    {
        if (max_count < j)
            max_count = j;
    }

    for (size_t j : bins)
    {
        if (j < 10)
            cout << "  " << j << "|";
        else  if (j < 100 && j>10)
            cout << " " << j << "|";
        else if (j >= 100)
            cout << j << "|";
        if (max_count == j)
        {
            for (size_t i = 0; i < MAX_ASTERISK; i++)
                cout << "*";
        }
        else
        {
            size_t height = MAX_ASTERISK * (static_cast<double>(j) / max_count);
            for (size_t q = 0; q < height; q++)
                cout << "*";
        }
        cout << endl;
    }
    return;
}



int main() {
    /*
    size_t number_count;
    cin >> number_count;
    const auto numbers = input_numbers(cin, number_count);
    size_t bin_count;
    cin >> bin_count;
    */
    const auto input = read_input(cin);
    const auto bins = make_histogram(input);


    //show_histogram_text(bins);
   // show_histogram_svg(bins);

    return 0;
}

