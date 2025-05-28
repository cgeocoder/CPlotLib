#include "window.h"

#include <SFML/Graphics.hpp>
#include "paths.h"

namespace cpl {
	Window::Window() {
		m_WndThread = std::thread([&]() { this->run(); });
	}

	Window::~Window() {
		done();
	}

	void Window::run() {
		const auto monitor_param = sf::VideoMode::getDesktopMode();

		sf::Vector2u window_size = sf::Vector2u(
			(unsigned)(monitor_param.width / 2),
			(unsigned)(monitor_param.height / 1.5)
		);

		m_HalfWindowWidth = window_size.x / 2;
		m_HalfWindowHeight = window_size.y / 2;

		// Window setting

		sf::ContextSettings wc_settings;
		wc_settings.antialiasingLevel = 8;

		sf::RenderWindow wnd(
			sf::VideoMode(window_size.x, window_size.y),
			"CPlotLib",
			sf::Style::Titlebar | sf::Style::Close,
			wc_settings
		);

		// Window Icon

		// sf::Image window_logo;
		// window_logo.loadFromFile(ICON_PATH);
		// wnd.setIcon(
		// 	window_logo.getSize().x,
		// 	window_logo.getSize().y,
		// 	window_logo.getPixelsPtr()
		// );

		volatile bool view_move_enable = false;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);

		sf::View view(sf::FloatRect(
			-(float)window_size.x,
			(float)window_size.y,
			(float)window_size.x * 2,
			(float)window_size.y * 2
		));

		view.zoom(0.02f);
		view.setCenter(window_size.x / 2.0f, window_size.y / 2.0f);

		// _Size.store(window_size);

		// Main loop

		float a = 0.0f;
		signed int zoom_count = 0;
		while (wnd.isOpen()) {
			// while (!_Trace.load());

			sf::Event event;

			while (wnd.pollEvent(event)) {
				sf::Event::EventType event_type = event.type;

				// Close window event
				if (event_type == sf::Event::Closed) {
					wnd.close();
				}

				if (/*_ScreenMove.load()*/ true) {
					// Zooming map
					if (event.type == sf::Event::MouseWheelScrolled) {
						if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
							if (event.mouseWheelScroll.delta < 0) {
								if (zoom_count > -30) {
									view.zoom(1.1f);
									zoom_count -= 1;
								}
							}
							else {
								if (zoom_count < 30) {
									view.zoom(0.9f);
									zoom_count += 1;
								}
							}
						}
					}

					// Moving map
					else if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							view_move_enable = true;
						}
					}
					else if (event.type == sf::Event::MouseButtonReleased) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							view_move_enable = false;
						}
					}
					else if (event.type == sf::Event::MouseMoved) {
						if (view_move_enable) {
							float zoom_scale_offset = view.getSize().x / window_size.x;

							view.move(
								(mouse_pos.x - event.mouseMove.x) * zoom_scale_offset,
								(mouse_pos.y - event.mouseMove.y) * zoom_scale_offset
							);
						}

						mouse_pos = sf::Mouse::getPosition(wnd);
					}
				}
			}

			wnd.clear(sf::Color::White);
			wnd.setView(view);

			/*sf::Text tmp_text;
			sf::Font font;
			if (!font.loadFromFile(DEFAULT_FONT_PATH2)) {
				__debugbreak();
			}

			tmp_text.setFont(font);
			tmp_text.setCharacterSize(24);

			tmp_text.setScale({ 0.05f, 0.05f });
			tmp_text.setString("123");
			tmp_text.setFillColor(sf::Color::Red);
			tmp_text.setStyle(sf::Text::Bold);
			tmp_text.setPosition(from_map_to_real(Vec2f{ 0.0f, 0.0f }));

			wnd.draw(tmp_text);*/
			
			m_PlotMutex.lock();

			for (Plot& plot : m_Plots) {
				for (Line& lines : plot.m_Lines) {
					wnd.draw(make_line(lines));
				}

				for (Line& lines : plot.m_StaticFuncLines) {
					wnd.draw(make_line(lines));
				}

				if (plot.m_Title) {
					wnd.draw(*plot.m_Title);
				}
			}

			m_PlotMutex.unlock();

			wnd.display();
		}
	}

	void Window::add_plot(Plot& plot) {
		m_PlotMutex.lock();

		if (plot.m_Title)
			plot.m_Title->setPosition(from_map_to_real(plot.m_Title->getPosition()));

		m_Plots.push_back(plot);
		m_PlotMutex.unlock();
	}

	void Window::done() {
		if (m_WndThread.joinable())
			m_WndThread.join();
	}

	sf::RectangleShape Window::make_line(const Line& ln) {
		Vec2f last_pos_point = ln.a;
		Vec2f new_pos_point = ln.b;
		Vec2f vec{ new_pos_point.x - last_pos_point.x, new_pos_point.y - last_pos_point.y };

		float vec_len = sqrt(vec.x * vec.x + vec.y * vec.y);

		float cos_a = vec.x / vec_len;
		float alpha = std::copysignf(acos(cos_a), vec.y);
		float ang_degrees = (180.f / (float)M_PI) * alpha;

		sf::RectangleShape line(sf::Vector2f(vec_len, ln.m_Width));
		line.setFillColor(sf::Color::Black);
		line.setOrigin(sf::Vector2f(0.0f, ln.m_Width / 2.0f));
		line.setRotation(-ang_degrees);
		line.setPosition(from_map_to_real(last_pos_point));
		line.setFillColor(ln.m_Color);


		return line;
	}
}