#include <iostream>
#include <vector>
#include <string>
#include "fiil.h"
using namespace std;
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height,
        string stroke="#111", string fill="#111") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
   // svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
   // svg_rect(TEXT_WIDTH,0, BLOCK_WIDTH, BIN_HEIGHT);
    double top = 0;
    size_t max_count = bins[0];
    for (size_t j : bins)
        if (max_count < j)
            max_count = j;

    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        string A=fill01(bin,max_count);
        if (bin==max_count)
            svg_rect(TEXT_WIDTH, top, IMAGE_WIDTH, BIN_HEIGHT);
        else
            svg_rect(TEXT_WIDTH, top, IMAGE_WIDTH*(static_cast<double>(bin)/max_count), BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();

}
