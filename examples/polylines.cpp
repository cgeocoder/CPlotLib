#include "cpl/cpl.h"

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    cpl::Plot plot{ 8.0f, 1.0f };
    plot.set_title("Logo");

    cpl::Polyline pline;
    pline.set_width(0.05f);
    pline.set_color("purple");

    for (auto t : cpl::range(0.0f, 12.0f * 180.0f, .5f)) {
        pline.add_point({
            cpl::sin(t) * (std::exp(cpl::cos(t)) - 2.0f * cpl::cos(4.0f * t) + pow(cpl::sin((1.0f / 12.0f) * t), 5.0f)),
            cpl::cos(t) * (std::exp(cpl::cos(t)) - 2.0f * cpl::cos(4.0f * t) + pow(cpl::sin((1.0f / 12.0f) * t), 5.0f))
        });
    }

    plot.add_polyline(pline);
    wnd.add_plot(plot);

    return 0;
}
