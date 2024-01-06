#include "../../mytest.h"

int main() {
    int val = 2 * 2;  // To avoid warnings on VS for very naive implementations of CHECK.
    CHECK(val == 4);
    CHECK(val == 5);
}
