// Copyright 2026 <Rhuan Saragioto>

#pragma once

#ifndef KEYPRESSVISUALIZER_HPP
#define KEYPRESSVISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

#include "keys.hpp"

struct KeyDisplay {
    sf::Keyboard::Scan _key;
    sf::Sprite _keySprite;
    float _pressTimer = 0.f;
    bool _pressed = false;
};

class KeypressVisualizer : public sf::Drawable {
 private:
    std::vector<KeyDisplay> _keyList;
    sf::Texture _keyTexture;
    
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
    KeypressVisualizer();
    ~KeypressVisualizer();

    void handleEvent(const sf::Event& event);
    void update(float dt);
};

#endif