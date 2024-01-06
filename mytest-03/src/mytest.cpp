#include "mytest.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "mytest_internal.h"

namespace mytest {
namespace {
std::map<std::string, std::function<void()>> test_cases;
int test_cases_passed = 0;
bool check_status = false;

}  // namespace
void check_failed(bool cond,
                  const std::string &expr,
                  const std::string &file,
                  int line,
                  std::optional<std::string> msg) {
    if (cond) {
        return;
    }
    ::mytest::get_check() = true;
    std::cerr << "CHECK(" << expr << ") at " << file << ":" << line
              << " failed!\n";
    if (msg) {
        std::cerr << "    message: " << msg.value() << '\n';
    }
}

std::map<std::string, std::function<void()>> &get_map() {
    return test_cases;
}

int &get_test_failed() {
    return test_cases_passed;
}

bool &get_check() {
    return check_status;
}
int get_size() {
    return ::mytest::get_map().size();
}

}  // namespace mytest
