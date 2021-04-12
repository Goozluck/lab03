#include "histogram.h"
#include "svg.h"
#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_positive1() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_positive2() {
    double min = 0;
    double max = 0;
    find_minmax({ 3, 3, 3 }, min, max);
    assert(min == 3);
    assert(max == 3);
}
void
test_positive3() {
    double min = 0;
    double max = 0;
    find_minmax({ 22 }, min, max);
    assert(min == 22);
    assert(max == 22);
}
void
test_positive4() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
void
test_positive5() {
    assert(fill01(5,5)=="#111");
}
void
test_positive6() {
    assert(fill01(4,4)== "#111");
}

int
main() {
    test_positive();
    test_positive1();
    test_positive2();
    test_positive3();
    test_positive4();
    test_positive5();
    test_positive6();
}
