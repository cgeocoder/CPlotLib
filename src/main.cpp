#include <iostream>

#include "cpl/cpl.h"

static float func1(float x) {
    return 2.0f * x * x;
}

static float func1_2(float x) {
    return -0.2f * x * x - 1.0f;
}

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    // Plot 1 - line

    cpl::Plot plot1{ 5.0f, 1.0f };
    plot1.set_quality(cpl::Quality::UltraHigh);
    plot1.set_title("Chart");

    plot1.add_function({ func1 });
    plot1.add_function({ func1_2 });

    plot1.add_point({ {1.0f, 1.0f} });

    cpl::Line line;
    line.b = { -12.0f, 23.0f };
    line.a = { 3.0f, 0.0f };

    plot1.add_line(line);

    wnd.add_plot(plot1);

    return 0;
}