#include "Chart.h"
#include "../cpl_math.h"
#include "../function.h"
#include "../paths.h"
#include "../primitives/line.h"
#include "../primitives/point.h"

namespace cpl {
	const float Quality::Low = 1.0f;
	const float Quality::Medium = 0.1f;
	const float Quality::High = 0.05f;
	const float Quality::UltraHigh = 0.01f;

	Chart::Chart(float radius, float step) : 
		m_Radius{ radius }, m_Step{ step }, 
		m_FuncQuality{ cpl::Quality::Medium } {

		m_Center = { 0.0f, 0.0f };
		m_Title = { nullptr };
		m_Font = { nullptr };

		redraw();
	}

	Chart::Chart(float radius, float step, const Vec2f& center) : 
		m_Radius{ radius }, m_Step{ step },
		m_FuncQuality{ cpl::Quality::Medium } {

		m_Center = center;
		m_Title = { nullptr };
		m_Font = { nullptr };
		redraw();
	}

	void Chart::draw_static_function(const Function& f) {
		rangef_t rng = range(-m_Radius, m_Radius + m_FuncQuality, m_FuncQuality);
		Vec2f last_point = { *rng.begin() + m_Center.x, f.m_Func(*rng.begin()) + m_Center.y };

		for (float x : rng) {
			Vec2f new_point = { x + m_Center.x, f.m_Func(x) + m_Center.y };

			Line ln = { last_point, new_point, f.m_Width, f.m_Color };
			check_line_boundaries(ln);
			m_StaticFuncLines.push_back(ln);

			last_point = new_point;
		}
	}
	
	void Chart::add_function(const Function& f) {
		draw_static_function(f);
		m_StaticFunctions.push_back(f);
	}

	void Chart::set_radius(float radius) { 
		m_Radius = radius; 
		redraw();
	}

	void Chart::set_step(float step) {
		m_Step = step;
		redraw();
	}

	void Chart::set_center(const Vec2f& xy) {
		m_Center = xy;
		redraw();
	}

	void Chart::set_center(float x, float y) {
		m_Center = Vec2f{ x, y };
		redraw();
	}

	void Chart::set_quality(float quality) {
		m_FuncQuality = quality;
		redraw();
	}

	void Chart::redraw() {
		m_Lines.clear();
		for (auto i : cpl::range(-m_Radius, m_Radius + m_Step, m_Step)) {
			m_Lines.push_back({ { i + m_Center.x, -m_Radius + m_Center.y }, { i + m_Center.x, m_Radius + m_Center.y }, 0.05f });
			m_Lines.push_back({ { -m_Radius + m_Center.x, i + m_Center.y }, { m_Radius + m_Center.x, i + m_Center.y }, 0.05f });
		}

		m_Lines.push_back({ { -m_Radius + m_Center.x, m_Center.y }, { m_Radius + m_Center.x, m_Center.y }, 0.1f });
		m_Lines.push_back({ { m_Center.x, -m_Radius + m_Center.y }, { m_Center.x, m_Radius + m_Center.y }, 0.1f });

		m_StaticFuncLines.clear();
		for (Function& f : m_StaticFunctions) {
			draw_static_function(f);
		}
	}

	void Chart::add_point(const Point& point) {
		Point p{ 
			{point.coords.x + m_Center.x, point.coords.y + m_Center.y },
			point.m_Radius, point.m_Color
		};

		m_StaticPoints.push_back(p);
	}

	void Chart::check_line_boundaries(Line& line) const {
		Vec2f line_vec = line.vec();

		// y = k1 * x + k2
		float k1 = line_vec.y / line_vec.x;
		float k2 = line.a.y - k1 * line.a.x;

		// Check B vector

		Vec2f vec_b = { (line.b.x + m_Center.x), (line.b.y + m_Center.y) };

		if (vec_b.y > m_Radius) {
			vec_b.y = m_Radius;
			vec_b.x = (m_Radius - k2) / k1;
		}
		else if (vec_b.y < -m_Radius) {
			vec_b.y = -m_Radius;
			vec_b.x = (-m_Radius - k2) / k1;
		}

		if (vec_b.x > m_Radius) {
			vec_b.x = m_Radius;
			vec_b.y = k1 * m_Radius + k2;
		}
		else if (vec_b.x < -m_Radius) {
			vec_b.x = -m_Radius;
			vec_b.y = -k1 * m_Radius + k2;
		}

		// Check A vector

		Vec2f vec_a = { (line.a.x + m_Center.x), (line.a.y + m_Center.y) };

		if (vec_a.y > m_Radius) {
			vec_a.y = m_Radius;
			vec_a.x = (m_Radius - k2) / k1;
		}
		else if (vec_a.y < -m_Radius) {
			vec_a.y = -m_Radius;
			vec_a.x = (-m_Radius - k2) / k1;
		}

		if (vec_a.x > m_Radius) {
			vec_a.x = m_Radius;
			vec_a.y = k1 * m_Radius + k2;
		}
		else if (vec_a.x < -m_Radius) {
			vec_a.x = -m_Radius;
			vec_a.y = -k1 * m_Radius + k2;
		}

		line.a = vec_a;
		line.b = vec_b;
	}

	void Chart::add_line(Line& line) {
		check_line_boundaries(line);
		m_StaticLines.push_back(line);
	}

	void Chart::set_title(const std::string& title) {
		if (m_Title == nullptr)
			m_Title = new sf::Text;

		if (m_Font == nullptr) {
			m_Font = new sf::Font;

			if (!m_Font->loadFromFile(DEFAULT_FONT)) {
				std::cout << "Chart::set_title(): sf::Font::loadFromFile() failed\n";
				return;
			}
		}
		
		m_Title->setFont(*m_Font);
		m_Title->setString(title);
		m_Title->setStyle(DEFAULT_FONT_STYLE);
		m_Title->setScale(DEFAULT_FONT_SCALE);
		m_Title->setFillColor(sf::Color::Black);
		m_Title->setCharacterSize(DEFAULT_FONT_CHAR_SIZE);

		sf::FloatRect title_rect = m_Title->getLocalBounds();
		m_Title->setOrigin(title_rect.width / 2.0f, title_rect.height / 2.0f);
		m_Title->setPosition({ m_Center.x, m_Radius + m_Center.y + m_Step });
	}
}