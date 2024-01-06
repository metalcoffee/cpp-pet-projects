#include "../../mytest.h"

int main() {
    int val = 2 * 2;  // To avoid warnings on VS for very naive implementations of CHECK.
    CHECK_MESSAGE(val == 4, "msg1");
    CHECK_MESSAGE(val == 5, "msg2");
}
