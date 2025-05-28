#pragma once

#ifndef __CPLOTLIB_WINDOW_H__
#define __CPLOTLIB_WINDOW_H__

#include "plot.h"
#include <thread>
#include <vector>
#include <mutex>
#include "cpl_math.h"
#include <corecrt_math_defines.h>


namespace cpl {
	class Window {
	public:
		friend class Plot;
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

	public:
		Window();
		~Window();

		void add_plot(Plot& plot);

		// friend static sf::RectangleShape make_line(cpl::Vec2f, cpl::Vec2f, float);

	private:
		std::mutex m_PlotMutex;
		std::vector<Plot> m_Plots;

		std::thread m_WndThread;
		unsigned int m_HalfWindowWidth, m_HalfWindowHeight;
	};
}

#endif // 