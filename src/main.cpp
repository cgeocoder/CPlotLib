#include <iostream>

#include "cpl/cpl.h"

static float func1(float x) {
    return 2.0f * x;
}

static float func2(float x) {
    return x * x - 5.0f;
}

static float func3(float x) {
    return sin(x);
}

static float func4(float x) {
    return fabs(x);
}

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    // Plot 1 - line

    cpl::Plot plot1{ 8.0f, 1.0f, {-10.0f, 9.0f} };
    plot1.add_static_function(func1);

    wnd.add_plot(plot1);

    // Plot 2 - parabola

    cpl::Plot plot2{ 8.0f, 1.0f, {10.0f, 9.0f} };
    plot2.add_static_function(func2);

    wnd.add_plot(plot2);

    // Plot 3 - sinus

    cpl::Plot plot3{ 8.0f, 1.0f, {-10.0f, -9.0f} };
    plot3.add_static_function(func3);

    wnd.add_plot(plot3);

    // Plot 4 - |x|

    cpl::Plot plot4{ 8.0f, 1.0f, {10.0f, -9.0f} };
    plot4.add_static_function(func4);

    wnd.add_plot(plot4);

    return 0;
}