#include "histogram.h"
#include"svg.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include<windows.h>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}


string
make_info_text() {
    std::stringstream buffer;
    DWORD info =GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD version_major = version & 0x00ff;
    DWORD version_minor = version & 0xff00;
    version_minor = version >>8;
    DWORD platform = info>>16;
    DWORD build;
    if ((platform &0x8000) == 0) build =platform;
    return buffer.str();
}


int main() {
    make_info_text();
    return 0;
    size_t number_count;
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);
    //show_histogram_text(bins);
    show_histogram_svg(bins);
    return 0;
}
