#pragma once

#ifndef __CchartLIB_POINT_H__
#define __CchartLIB_POINT_H__

#include "../cpl_math.h"
#include <vector>
#include <SFML/Graphics/Shader.hpp>

namespace cpl {
	static constexpr const float DEFAULT_POINT_RADIUS = 0.15f;

	class Point {
	private:
		sf::Color m_Color;
		float m_Radius;

	public:
		friend class Window;
		friend class Chart;

		Vec2f coords;

		Point();
		Point(Vec2f coords);
		Point(Vec2f coords, const char* color);
		Point(Vec2f coords, float radius);
		Point(Vec2f coords, float radius, const char* color);

		void set_color(const char* color);
		void set_radius(float radius);

	private:
		Point(Vec2f coords, float radius, sf::Color color);
	};
}

#endif // !__CchartLIB_POINT_H__