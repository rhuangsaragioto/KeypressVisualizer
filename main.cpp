// Copyright 2026 <Rhuan Saragioto>

#include "KeypressVisualizer.hpp"
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Keypress Visualizer");

    sf::Font font;
    sf::Text text(font);

    KeypressVisualizer visualizer;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            visualizer.handleEvent(*event);
        }
        window.clear(sf::Color(0xFFD3BAFF));
        window.draw(text);
        window.display();
    }
}