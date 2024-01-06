#include "../../mytest.h"

int main() {
    CHECK(2 * 2 == 5), CHECK_MESSAGE(2 * 2 == 6, "msg1");
}
