// Copyright 2026 <Rhuan Saragioto>

#include "KeypressVisualizer.hpp"
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Keypress Visualizer");

    sf::Font font;
    sf::Text text(font);

    KeypressVisualizer visualizer;

    sf::Texture t;
    if (!t.loadFromFile("assets/background_image.png")) {
        throw std::runtime_error("Something went wrong when loading the image.");
    }
    sf::Sprite background(t);

    sf::Clock clock;
    
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            visualizer.handleEvent(*event);
        }

        visualizer.update(dt);

        window.clear(sf::Color(sf::Color::Transparent));
        window.draw(background);
        window.draw(visualizer);
        window.display();
    }
}