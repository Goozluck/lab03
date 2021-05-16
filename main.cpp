#include "histogram.h"
#include"svg.h"
#include <iostream>
#include <vector>
#include <string>

#include <curl/curl.h>
#include <sstream>
#include <string>

using namespace std;

struct Input{
vector<double> numbers;
size_t bin_count;
};

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;



vector<double>
input_numbers(istream& in,size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
         in >> result[i];
    }
    return result;
}


Input
read_input(istream& in, bool prompt){
Input data;
if(prompt)
cerr<<"Enter number count: ";

size_t number_count;
in >> number_count;

if(prompt)
cerr<<"Enter numbers: ";

data.numbers =input_numbers(in,number_count);

if(prompt)
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
    for (double i : data.numbers)
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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
  auto data_size = item_size * item_count;
 stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
 buffer->write(reinterpret_cast<char*>(items), data_size);
    return data_size;
}

Input
download(const string& address) {
    curl_global_init(CURL_GLOBAL_ALL);
    stringstream buffer;

    CURL* curl=curl_easy_init();

     if(curl) {
           CURLcode res;
           curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
           curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
           curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
           res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
            cout << address<<endl;
            cout << curl_easy_strerror(res);
                exit(1);
               }
           curl_easy_cleanup(curl);
           }
    return read_input(buffer, false);
}




int main(int argc, char* argv[]) {
  Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins);

    return 0;
}
