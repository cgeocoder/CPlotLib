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

    // Chart 1 - line

    cpl::Chart chart1{ 15.0f, 1.0f };
    chart1.set_title("Chart");

    for (float i = 1.0f; i < 10.0f; i += 1.0f) {

        cpl::Function df1{
            [&](float x) -> float {
                return 1.0f / i * x * x / i;
            }
        };

        chart1.add_function(df1);
    }
    
    wnd.add_chart(chart1);

    return 0;
}