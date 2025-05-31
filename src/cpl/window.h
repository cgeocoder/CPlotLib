#pragma once

#ifndef __CchartLIB_WINDOW_H__
#define __CchartLIB_WINDOW_H__

#include "charts/Chart.h"
#include <thread>
#include <vector>
#include <mutex>
#include "cpl_math.h"
#include <corecrt_math_defines.h>


namespace cpl {

	// CPlotLib window for easy rendering graphics
	class Window {
	public:
		friend class Chart;
		friend class Line;

	private:
		void run();
		void done();

		inline sf::Vector2f from_map_to_real(const float& x, const float& y) {
			return sf::Vector2f(m_HalfWindowWidth + x, m_HalfWindowHeight - y);
		}

		inline sf::Vector2f from_map_to_real(const sf::Vector2f& cood) {
			return sf::Vector2f(m_HalfWindowWidth + cood.x, m_HalfWindowHeight - cood.y);
		}

		inline sf::Vector2f from_map_to_real(const Vec2f& cood) {
			return sf::Vector2f(m_HalfWindowWidth + cood.x, m_HalfWindowHeight - cood.y);
		}

		inline sf::Vector2f from_real_to_map(const float& x, const float& y) {
			return sf::Vector2f(x - m_HalfWindowWidth, m_HalfWindowHeight - y);
		}

		inline sf::Vector2f from_real_to_map(const sf::Vector2f& cood) {
			return sf::Vector2f(cood.x - m_HalfWindowWidth, m_HalfWindowHeight - cood.y);
		}

		inline sf::Vector2f from_real_to_map(const Vec2f& cood) {
			return sf::Vector2f(cood.x - m_HalfWindowWidth, m_HalfWindowHeight - cood.y);
		}

		sf::RectangleShape make_line(const Line& ln);
		sf::CircleShape make_point(const Point& pt);

	public:
		Window();
		~Window();

		// Add a chart
		void add_chart(Chart& Chart);

	private:
		std::mutex m_chartMutex;
		std::vector<Chart> m_charts;

		std::thread m_WndThread;
		unsigned int m_HalfWindowWidth, m_HalfWindowHeight;
	};
}

#endif // 