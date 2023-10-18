#include <vector>
#include <cstdio>
#include <memory>
#include <typeinfo>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <map>
#include <nlohmann/json.hpp>
#include <functional>
#include <any>
#include <random>
#include <variant>
#include <list>

#pragma once

class Entity;

struct SinusoidalFunction {
    double amplitude;
    double frequency;
    double phase;
};

using Variant = std::variant<
                std::pair<std::shared_ptr<sf::Texture>, sf::Sprite>,
                int, 
                std::pair<double, double>, 
                std::pair<int, int>, 
                bool, 
                double, 
                sf::Clock,
                sf::Sound,
                sf::SoundBuffer,
                sf::IntRect, 
                std::pair<std::pair<int, int>, std::pair<int, int>>,
                std::vector<std::shared_ptr<Entity>>,
                SinusoidalFunction>;
using json = nlohmann::json;
