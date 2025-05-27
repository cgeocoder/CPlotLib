#pragma once

#ifndef __CPLOTLIB_PRIMITIVES_H__
#define __CPLOTLIB_PRIMITIVES_H__

#include <corecrt_math_defines.h>
#include "function.h"
#include "window.h"
#include <vector>
#include "cpl_math.h"

namespace cpl {
    static sf::RectangleShape make_line___(
        cpl::Vec2f vec1, cpl::Vec2f vec2, float width
    ) {
        sf::Vector2f last_pos_point{ vec1.x, vec1.y };

        // this->m_Pos.store(this->from_map_to_real(x, y));
        sf::Vector2f new_pos_point = { vec2.x, vec2.y };
        sf::Vector2f vec{ new_pos_point.x - last_pos_point.x, new_pos_point.y - last_pos_point.y };

        float vec_len = sqrt(vec.x * vec.x + vec.y * vec.y);

        float cos_a = vec.x / vec_len;
        float alpha = std::copysignf(acos(cos_a), vec.y);
        float ang_degrees = (180.f / (float)M_PI) * alpha;

        sf::RectangleShape line(sf::Vector2f(vec_len, width));
        line.setFillColor(sf::Color::Black);
        line.setOrigin(sf::Vector2f(0.0f, width / 2.0f));
        line.setRotation(-ang_degrees);
        // line.setPosition(Window::from_map_to_real(last_pos_point));
        line.setFillColor(sf::Color::Black);

        return line;
    }
}

#endif // !__CPLOTLIB_PRIMITIVES_H__