#pragma once

#ifndef __CPLOTLIB_PLOT_H__
#define __CPLOTLIB_PLOT_H__

#include "function.h"
#include "line.h"
#include <vector>

namespace cpl {
	class Quality {
	public:
		static const float Low;
		static const float Medium;
		static const float High;
		static const float UltraHigh;
	};

	class Plot {
	private:
		void redraw();
		void draw_static_function(const Function& f);

	public:
		friend class Window;

		Plot(float radius, float step);
		Plot(float radius, float step, const Vec2f& center);

		void set_radius(float radius);
		void set_step(float step);

		void set_center(float x, float y);
		void set_center(const Vec2f& xy);

		void set_quality(float quality);
		void add_static_function(const Function& f);
		void add_static_function(const std::function<float(float)>& f);
		void add_dynamic_function(Function& f);
		
		void set_title(const std::string& title);

	private:
		Vec2f m_Center;
		float m_Radius, m_Step, m_FuncQuality;

		sf::Text* m_Title;
		sf::Font* m_Font;

		std::vector<Line> m_Lines;
		std::vector<Line> m_StaticFuncLines;
		std::vector<Function> m_DynamicFunctions;
		std::vector<Function> m_StaticFunctions;
	};
}

#endif // 