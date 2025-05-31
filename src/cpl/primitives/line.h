#pragma once

#ifndef __CchartLIB_LINE_H__
#define __CchartLIB_LINE_H__

#include "../cpl_math.h"
#include <vector>
#include <SFML/Graphics/Shader.hpp>

namespace cpl {
	static constexpr const float DEFAULT_LINE_WIDTH = 0.1f;

	class Line {
	private:
		sf::Color m_Color;
		float m_Width;

	public:
		friend class Window;
		friend class Chart;

		Vec2f a, b;

		Line();
		Line(Vec2f a, Vec2f b);
		Line(Vec2f a, Vec2f b, const char* color);
		Line(Vec2f a, Vec2f b, float width);
		Line(Vec2f a, Vec2f b, float width, const char* color);

		void set_color(const char* color);

		inline Vec2f vec() const {
			return Vec2f{ b.x - a.x, b.y - a.y };
		}

		inline float len() const {
			return vec().len(); 
		}

	private:
		Line(Vec2f a, Vec2f b, float width, sf::Color color);
	};
}

#endif // 