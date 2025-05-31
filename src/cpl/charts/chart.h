#pragma once

#ifndef __CchartLIB_chart_H__
#define __CchartLIB_chart_H__

#include "chart_base.h"
#include "../function.h"
#include "../primitives/line.h"
#include "../primitives/point.h"

#include <vector>

namespace cpl {
	static const sf::Vector2f DEFAULT_FONT_SCALE = { 0.051f, 0.051f };
	static const sf::Color DEFAULT_FONT_COLOR = sf::Color::Black;

	static constexpr const unsigned int DEFAULT_FONT_CHAR_SIZE = 20;
	static constexpr const sf::Text::Style DEFAULT_FONT_STYLE = sf::Text::Regular;

	// 
	class Chart : public ChartBase {
	private:
		// redraw all entities
		void redraw();

		// draw all Function entities
		void draw_static_function(const Function& f);

		/*
			Crop the line extending beyond the boundaries 
			of the square with a side of 2 m_Radius
		*/
		void check_line_boundaries(Line& line) const;

	public:
		friend class Window;

		Chart(float radius, float step);
		Chart(float radius, float step, const Vec2f& center);

		// Set new chart radius
		void set_radius(float radius);

		// Set new chart drawing step
		void set_step(float step);

		// Set new chart center
		void set_center(float x, float y) override;
		// Set new chart center
		void set_center(const Vec2f& xy) override;

		// Set drawing entities (Function, Point, Line) rendering quality
		// @param quality - from cpl::Quality
		void set_quality(float quality);

		// Add a static function to the chart
		// @param func - cpl::Function object
		void add_function(const Function& func);

		// Add a static point to the chart
		// @param point - cpl::Point object
		void add_point(const Point& point);

		// Add a static line to the chart
		// @param line - cpl::Line object
		void add_line(Line& line);
		
		// Set the title for the chart
		void set_title(const std::string& title) override;

	private:
		float m_Radius, m_Step, m_FuncQuality;

		std::vector<Line> m_Lines;
		std::vector<Line> m_StaticLines;
		std::vector<Line> m_StaticFuncLines;
		std::vector<Point> m_StaticPoints;
		std::vector<Function> m_StaticFunctions;
	};
}

#endif // !__CchartLIB_chart_H__