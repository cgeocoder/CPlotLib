#include "cpl/cpl.h"

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    // Plot 1

    cpl::Plot plot1{ 8.0f, 1.0f, {-10.0f, 9.0f} };
    plot1.set_title("Line");

    cpl::Function f1(
        [&](float x) -> float {
            return x;
        }, "red"
    );

    plot1.add_function(f1);

    wnd.add_plot(plot1);

    // Plot 2

    cpl::Plot plot2{ 8.0f, 1.0f, {10.0f, 9.0f} };
    plot2.set_title("Parabola");

    cpl::Function f2(
        [&](float x) -> float {
            return 0.1f * x * x;
        }, "blue"
    );

    plot2.add_function(f2);

    wnd.add_plot(plot2);

    // Plot 3

    cpl::Plot plot3{ 8.0f, 1.0f, {-10.0f, -9.0f} };
    plot3.set_title("Giperbola");

    cpl::Function f3(
        [&](float x) -> float {
            return 1 / x;
        }, "green"
    );

    plot3.add_function(f3);

    wnd.add_plot(plot3);

    // Plot 4

    cpl::Plot plot4{ 8.0f, 1.0f, {10.0f, -9.0f} };
    plot4.set_title("Log and 2^x");

    plot4.add_function({ 
        [&](float x) -> float {
            return std::log2(x);
        }
    });

    plot4.add_function({
        [&](float x) -> float {
            return std::pow(2, x);
        }
    });

    wnd.add_plot(plot4);

    return 0;
}
