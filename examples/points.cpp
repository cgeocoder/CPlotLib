#include "cpl/cpl.h"

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    cpl::Plot plot{ 12.0f, 1.0f };
    plot.set_title("Points");

    for (float x : cpl::range(-12.0f, 12.0f, 1.0f)) {
        plot.add_point({ {0.0f + x, -2.0f * x}, "red" });
        plot.add_point({ {-3.0f * x, 0.5f + x}, "blue" });
    }

    wnd.add_plot(plot);

    return 0;
}
