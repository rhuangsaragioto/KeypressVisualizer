// Copyright 2026 <Rhuan Saragioto>

#include "KeypressVisualizer.hpp"
#include <stdexcept>
#include <random>

// Some consts to make my life easier lmao

static const int KEY_SIZE = 222;        // each key is 222px by 222px
static const int GAP = 10;              // gap between keys is 10px
static const int SLOT = KEY_SIZE + GAP; // basically how much space is reserved per tile
static const int SPACEKEY_WIDTH = 1382; // space key is wider than the other keys but same height

static const float ROW_0X = 9.9f;
static const float ROW_0Y = 10.f;

static const float ROW_1X = 10.f + (SLOT * .49f);
static const float ROW_1Y = 10.f + (SLOT);

static const float ROW_2X = 10.f + (SLOT * 1.24f);
static const float ROW_2Y = 10.f + (SLOT * 2.f);

static const float ROW_3X = ((2320.f - 1382.f) / 2.f) - 48.9f;
static const float ROW_3Y = 10.f + (SLOT * 3);

static const sf::Color BASE_COLOR = sf::Color::White;

static const float FADE_SPEED = 2.f;

struct KeyInfo {
    sf::Keyboard::Scan key;
    sf::Vector2f position;
    bool is_space;
};

static const KeyInfo KEY_DATA[] = {
    // top row - QWERTYUIOP
    { QKEY, {ROW_0X + (SLOT * 0), ROW_0Y}, false },
    { WKEY, {ROW_0X + (SLOT * 1), ROW_0Y}, false },
    { EKEY, {ROW_0X + (SLOT * 2), ROW_0Y}, false },
    { RKEY, {ROW_0X + (SLOT * 3), ROW_0Y}, false },
    { TKEY, {ROW_0X + (SLOT * 4), ROW_0Y}, false },
    { YKEY, {ROW_0X + (SLOT * 5), ROW_0Y}, false },
    { UKEY, {ROW_0X + (SLOT * 6), ROW_0Y}, false },
    { IKEY, {ROW_0X + (SLOT * 7), ROW_0Y}, false },
    { OKEY, {ROW_0X + (SLOT * 8), ROW_0Y}, false },
    { PKEY, {ROW_0X + (SLOT * 9), ROW_0Y}, false },

    // middle row - ASDFGHJKL
    { AKEY, {ROW_1X + (SLOT * 0), ROW_1Y}, false },
    { SKEY, {ROW_1X + (SLOT * 1), ROW_1Y}, false },
    { DKEY, {ROW_1X + (SLOT * 2), ROW_1Y}, false },
    { FKEY, {ROW_1X + (SLOT * 3), ROW_1Y}, false },
    { GKEY, {ROW_1X + (SLOT * 4), ROW_1Y}, false },
    { HKEY, {ROW_1X + (SLOT * 5), ROW_1Y}, false },
    { JKEY, {ROW_1X + (SLOT * 6), ROW_1Y}, false },
    { KKEY, {ROW_1X + (SLOT * 7), ROW_1Y}, false },
    { LKEY, {ROW_1X + (SLOT * 8), ROW_1Y}, false },

    // bottom row - ZXCVBNM
    { ZKEY, {ROW_2X + (SLOT * 0), ROW_2Y}, false },
    { XKEY, {ROW_2X + (SLOT * 1), ROW_2Y}, false },
    { CKEY, {ROW_2X + (SLOT * 2), ROW_2Y}, false },
    { VKEY, {ROW_2X + (SLOT * 3), ROW_2Y}, false },
    { BKEY, {ROW_2X + (SLOT * 4), ROW_2Y}, false },
    { NKEY, {ROW_2X + (SLOT * 5), ROW_2Y}, false },
    { MKEY, {ROW_2X + (SLOT * 6), ROW_2Y}, false },

    //space - poor space all by itself :(
    { SPACE, {ROW_3X, ROW_3Y}, true }
};

sf::Color genRandomColor(unsigned long key) {
    std::minstd_rand0 rng(key);
    std::uniform_int_distribution<int> dist(0, 255);

    return sf::Color(dist(rng), dist(rng), dist(rng));
}

KeypressVisualizer::KeypressVisualizer() {
    if (!_keyTexture.loadFromFile("assets/key_spritesheet.png")) {
        throw std::runtime_error("Failed to load the spritesheet.");
    }

    sf::IntRect keyArea({GAP, GAP}, 
                        {KEY_SIZE, KEY_SIZE});

    sf::IntRect spaceArea({GAP + (2 * SLOT), GAP + (3 * SLOT)}, 
                          {SPACEKEY_WIDTH, KEY_SIZE});

    for (const KeyInfo& ki : KEY_DATA) {
        KeyDisplay kd {
            ._key = ki.key,
            ._keySprite = sf::Sprite(_keyTexture, ki.is_space ? spaceArea : keyArea),
            ._pressTimer = 0.f,
            ._pressed = false
        };

        kd._keySprite.setPosition(ki.position);
        _keyList.push_back(kd);
    }

}

KeypressVisualizer::~KeypressVisualizer() {}

void KeypressVisualizer::handleEvent(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        for (KeyDisplay& kd : _keyList) {
            if (kd._key == keyPressed->scancode) {
                kd._pressed = true;
                kd._pressTimer = 1.f;
                kd._highlight = genRandomColor(std::chrono::system_clock::now().time_since_epoch().count());
            }
        }
    }
    if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
        for (KeyDisplay& kd : _keyList) {
            if (kd._key == keyReleased->scancode) {
                kd._pressed = false;
            }
        }
    }
}

void KeypressVisualizer::update(float dt) {
    
    for (KeyDisplay& kd : _keyList) {
        if (!kd._pressed && (kd._pressTimer > 0.f)) {
            kd._pressTimer -= dt * FADE_SPEED;
            if (kd._pressTimer < 0.f)
            kd._pressTimer = 0.f;
        }
        
        float time_squared = kd._pressTimer * kd._pressTimer;
        
        sf::Color hue(
            static_cast<uint8_t>(BASE_COLOR.r + (kd._highlight.r - BASE_COLOR.r) * time_squared),
            static_cast<uint8_t>(BASE_COLOR.g + (kd._highlight.g - BASE_COLOR.g) * time_squared),
            static_cast<uint8_t>(BASE_COLOR.b + (kd._highlight.b - BASE_COLOR.b) * time_squared)
        );
        kd._keySprite.setColor(hue);
    }
}

void KeypressVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform scale;
    scale.scale({.5f, .5f});
    scale.translate({105.f, 300.f});
    states.transform *= scale;
    for (const KeyDisplay& kd : _keyList) {
        target.draw(kd._keySprite, states);
    }
}