#include "../../mytest.h"
#include <iostream>

bool foo(bool x) {
    std::cerr << "evaluate\n";
    return x;
}

int main() {
    std::cerr << "1\n";
    CHECK(foo(true));
    std::cerr << "2\n";
    CHECK(foo(false));
    std::cerr << "3\n";
}
