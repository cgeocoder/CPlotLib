#include "cpl/cpl.h"

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    cpl::Plot plot{ 12.0f, 1.0f };
    plot.set_title("Lines");

    plot.add_line({ {-30.0f, -2.0f}, {30.0f, 3.0f}, "red" });
    plot.add_line({ {-3.0f, 100.0f}, {4.0f, -100.0f}, "blue" });

    wnd.add_plot(plot);

    return 0;
}
