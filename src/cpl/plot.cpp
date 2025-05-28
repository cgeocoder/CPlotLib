#include "plot.h"
#include "cpl_math.h"
#include "primitives.h"
#include "paths.h"

namespace cpl {
	const float Quality::Low = 1.0f;
	const float Quality::Medium = 0.1f;
	const float Quality::High = 0.05f;
	const float Quality::UltraHigh = 0.01f;

	Plot::Plot(float radius, float step) : 
		m_Radius{ radius }, m_Step{ step }, m_Center{ 0.0f, 0.0f }, 
		m_FuncQuality{ cpl::Quality::Medium }, m_Title{ nullptr }, m_Font{nullptr} {

		redraw();
	}

	Plot::Plot(float radius, float step, const Vec2f& center) : 
		m_Radius{ radius }, m_Step{ step }, m_Center{ center }, 
		m_FuncQuality{ cpl::Quality::Medium }, m_Title{ nullptr }, m_Font{ nullptr } {

		redraw();
	}

	void Plot::draw_static_function(const Function& f) {
		auto check_hight = [&](float y) -> bool {
			return ((y >= -m_Radius) && (y <= m_Radius));
		};

		rangef_t rng = range(-m_Radius, m_Radius + m_FuncQuality, m_FuncQuality);
		Vec2f last_point = { -m_Radius, f.m_Func(m_Radius) };

		for (float x : rng) {
			float y = f.m_Func(x);

			if (check_hight(y)) {
				last_point = { x + m_Center.x, y + m_Center.y };
				break;
			}
		}

		for (float x : rng) {
			float y = f.m_Func(x);

			if (check_hight(y)) {
				Vec2f new_point = { x + m_Center.x, y + m_Center.y };

				Line ln = { last_point, new_point, f.m_Width };
				ln.m_Color = f.m_Color;

				m_StaticFuncLines.push_back(ln);

				last_point = new_point;
			}
		}
	}

	
	void Plot::add_function(const Function& f) {
		draw_static_function(f);
		m_StaticFunctions.push_back(f);
	}

	void Plot::add_function(const std::function<float(float)>& f) {
		Function fn{ f };

		draw_static_function(fn);
		m_StaticFunctions.push_back(fn);
	}

	void Plot::add_dynamic_function(Function& f) {
		m_DynamicFunctions.push_back(f);
	}

	void Plot::set_radius(float radius) { 
		m_Radius = radius; 
		redraw();
	}

	void Plot::set_step(float step) {
		m_Step = step;
		redraw();
	}

	void Plot::set_center(const Vec2f& xy) {
		m_Center = xy;
		redraw();
	}

	void Plot::set_center(float x, float y) {
		m_Center = Vec2f{ x, y };
		redraw();
	}

	void Plot::set_quality(float quality) {
		m_FuncQuality = quality;
		redraw();
	}

	void Plot::redraw() {
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

	void Plot::set_title(const std::string& title) {
		if (m_Title == nullptr)
			m_Title = new sf::Text;

		if (m_Font == nullptr) {
			m_Font = new sf::Font;

			if (!m_Font->loadFromFile(DEFAULT_FONT)) {
				std::cout << "Plot::set_title(): sf::Font::loadFromFile() failed\n";
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