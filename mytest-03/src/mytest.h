#ifndef MYTEST_H_
#define MYTEST_H_

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace mytest {
bool run_tests();
void check_failed(bool cond,
                  const std::string &expr,
                  const std::string &file,
                  int line,
                  std::optional<std::string> msg = std::nullopt);

std::map<std::string, std::function<void()>> &get_map();
int &get_test_failed();
bool &get_check();
int get_size();

#define MYTEST_CHECK(expr) \
    ::mytest::check_failed(static_cast<bool>(expr), #expr, __FILE__, __LINE__)

#define CHECK(expr) MYTEST_CHECK(expr)

#define MYTEST_CHECK_MESSAGE(expr, msg)                                        \
    ::mytest::check_failed(static_cast<bool>(expr), #expr, __FILE__, __LINE__, \
                           msg)
#define CHECK_MESSAGE(expr, msg) MYTEST_CHECK_MESSAGE(expr, msg)

#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)

#define MYTEST_REGISTER_FUNC(func_name, test_case_name)              \
    namespace {                                                      \
    struct CONCATENATE(func_name, _struct) {                         \
        static void func_name();                                     \
        CONCATENATE(func_name, _struct)() {                          \
            ::mytest::get_map().insert({test_case_name, func_name}); \
        }                                                            \
    } CONCATENATE(func_name, _struct_instance);                      \
    }                                                                \
    inline void CONCATENATE(func_name, _struct)::func_name()

#define MYTEST_REGISTER_FUNCTION4(name_x, name_y, test_case_name) \
    MYTEST_REGISTER_FUNC(CONCATENATE(name_x, name_y), test_case_name)

#define MYTEST_REGISTER_FUNCTION2(name_x, name_y, test_case_name)       \
    MYTEST_REGISTER_FUNCTION4(CONCATENATE(name_x, name_y), __COUNTER__, \
                              test_case_name)

#define MYTEST_REGISTER_FUNCTION(name_x, name_y, test_case_name) \
    MYTEST_REGISTER_FUNCTION2(name_x, name_y, test_case_name)

#define MYTEST_CASE(name) MYTEST_REGISTER_FUNCTION(mytest_func_, __LINE__, name)

#define TEST_CASE(name) MYTEST_CASE(name)

}  // namespace mytest
#endif
