#pragma once

#ifndef __CchartLIB_chart_H__
#define __CchartLIB_chart_H__

#include "../function.h"
#include "../primitives/line.h"
#include <vector>
#include "../primitives/point.h"

namespace cpl {
	static const sf::Vector2f DEFAULT_FONT_SCALE = { 0.051f, 0.051f };
	static const sf::Color DEFAULT_FONT_COLOR = sf::Color::Black;

	static constexpr const unsigned int DEFAULT_FONT_CHAR_SIZE = 20;
	static constexpr const sf::Text::Style DEFAULT_FONT_STYLE = sf::Text::Regular;

	class Quality {
	public:
		static const float Low;
		static const float Medium;
		static const float High;
		static const float UltraHigh;
	};

	class ScatterChart {
	private:
		void redraw();

	public:
		friend class Window;

		ScatterChart(float radius, float step);
		ScatterChart(float radius, float step, const Vec2f& center);

		void set_radius(float radius);
		void set_step(float step);

		void set_center(float x, float y);
		void set_center(const Vec2f& xy);

		void set_quality(float quality);

		// add static function
		void add_function(const Function& f);
		void add_dynamic_function(Function& f);

		void add_point(const Point& point);
		void add_dynamic_point(Point& point);

		void set_title(const std::string& title);

	private:
		Vec2f m_Center;
		float m_Radius, m_Step, m_FuncQuality;

		sf::Text* m_Title;
		sf::Font* m_Font;

		std::vector<Line> m_Lines;
		std::vector<Line> m_StaticFuncLines;
		std::vector<Point> m_StaticPoints;
		std::vector<Function> m_DynamicFunctions;
		std::vector<Function> m_StaticFunctions;
	};
}

#endif // 