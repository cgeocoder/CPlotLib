#include "line.h"
#include "colors.h"
#include <iostream>

namespace cpl {
	Line::Line() : a{ 0.0f, 0.0f }, b{ 0.0f, 0.0f }, m_Width{ 0.5f } {
		m_Color = sf::Color::Black;
	}

	Line::Line(Vec2f a, Vec2f b) : a{ a }, b{ b }, m_Width{ 0.5f } {
		m_Color = sf::Color::Black;
	}

	Line::Line(Vec2f a, Vec2f b, const char* color) : a{ a }, b{ b }, m_Width{ 0.5f } {
		set_color(color);
	}

	Line::Line(Vec2f a, Vec2f b, float width) : a{ a }, b{ b }, m_Width{ width } {
		m_Color = sf::Color::Black;
	}

	Line::Line(Vec2f a, Vec2f b, float width, const char* color) : a{ a }, b{ b }, m_Width{ width } {
		set_color(color);
	}

	void Line::set_color(const char* color) {
		try {
			m_Color = ColorMap.at(color);
		}
		catch (std::exception ex) {
			std::cout << "Line::set_color() failed: " << ex.what() << '\n';
		}
	}
};
