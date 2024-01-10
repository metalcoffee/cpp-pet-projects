#include "ball_icon.h"
#include <memory>
#include <type_traits>
#include <utility>
#include "ball_icon.h"  // Ensure include guards
#include "doctest.h"
#include "test_utils.h"

#ifdef TEST_BALL_ICON
static_assert(!std::is_convertible_v<int, widgets::ball_icon>);
static_assert(!std::is_copy_constructible_v<widgets::ball_icon>);
static_assert(!std::is_copy_assignable_v<widgets::ball_icon>);
static_assert(!std::is_move_constructible_v<widgets::ball_icon>);
static_assert(!std::is_move_assignable_v<widgets::ball_icon>);

TEST_CASE("ball_icon works") {
    widgets::ball_icon ico(10);
    CHECK_DIMENSIONS(ico, 21, 21);
    CHECK(std::as_const(ico).radius() == 10);
#ifdef TEST_PARENT
    CHECK(std::as_const(ico).parent() == nullptr);
#endif
#ifdef TEST_CHILD_AT
    CHECK(ico.child_at(0, 0) == nullptr);
    CHECK(ico.child_at(5, 5) == &ico);
    CHECK(ico.child_at(20, 10) == &ico);
    CHECK(ico.child_at(21, 10) == nullptr);
#endif

    ico.radius(20);
    CHECK_DIMENSIONS(ico, 41, 41);
    CHECK(ico.radius() == 20);
}

TEST_CASE("make_ball_icon") {
    std::unique_ptr<widgets::ball_icon> ico = widgets::make_ball_icon(10);
    CHECK_DIMENSIONS(*ico, 21, 21);
}
#endif  // TEST_BALL_ICON
