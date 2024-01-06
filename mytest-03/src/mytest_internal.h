#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace mytest {
bool run_tests(){
    for (const auto &[name, func_name] : ::mytest::get_map()) {
        ::mytest::get_check() = false;
        std::cerr << "Running \"" << name << "\"...\n";
        func_name();
        if (::mytest::get_check()) {
            ::mytest::get_test_failed()++;
        }
    }

    std::cerr << "===== Tests passed: "
              << ::mytest::get_map().size() - ::mytest::get_test_failed() << "/"
              << ::mytest::get_map().size() << " =====\n";
    return bool(::mytest::get_test_failed() != 0);
}


}  // namespace mytest
