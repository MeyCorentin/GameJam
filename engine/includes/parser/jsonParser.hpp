#pragma once

#include "../main.hpp"

class JsonParser {
public:
    JsonParser() {}

    static Variant ParseSpriteValue(const json& arg_value) {
        sf::Sprite sprite;
        sf::Texture texture;
        std::shared_ptr<sf::Texture> texture_ptr;

        if (!arg_value.is_string()) {
            std::cerr << "Invalid value for Sprite type." << std::endl;
            return Variant();
        }
        if (!texture.loadFromFile(arg_value)) {
            std::cerr << "Failed to load texture for sprite." << std::endl;
            return Variant();
        }
        texture_ptr = std::make_shared<sf::Texture>(texture);
        sprite.setTexture(*texture_ptr);
        return std::make_pair(texture_ptr, sprite);
    }

    static Variant ParseIntValue(const json& arg_value) {
        int int_value;

        if (!arg_value.is_number_integer()) {
            std::cerr << "Invalid value for Int type." << std::endl;
            return Variant();
        }
        int_value = arg_value;
        return int_value;
    }

    static Variant ParseDoubleValue(const json& arg_value) {

        double double_value = arg_value;
        return double_value;
    }

    static Variant ParsePairDoubleValue(const json& arg_value) {
        double x;
        double y;
        std::pair<double, double> pair_value;

        if (!arg_value.is_object() || !arg_value.contains("x") || !arg_value.contains("y")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }
        x = arg_value["x"];
        y = arg_value["y"];
        pair_value = std::make_pair(x, y);
        return pair_value;
    }

    static Variant ParsePairIntValue(const json& arg_value) {
        int x;
        int y;
        std::pair<int, int> pair_value;

        if (!arg_value.is_object() || !arg_value.contains("x") || !arg_value.contains("y")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }
        x = arg_value["x"];
        y = arg_value["y"];
        pair_value = std::make_pair(x, y);
        return pair_value;
    }

    static Variant ParseBoolValue(const json& arg_value) {
        bool bool_value;

        if (!arg_value.is_boolean()) {
            std::cerr << "Invalid value for Bool type." << std::endl;
            return Variant();
        }
        bool_value = arg_value;
        return bool_value;
    }

    static Variant ParseClockValue(const json& value) {
        sf::Clock clock;
        return clock;
    }

    static Variant ParseIntRectValue(const json& value) {
        if (!value.is_object() || !value.contains("left") || !value.contains("top") || !value.contains("width") || !value.contains("height")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }

        int left = value["left"];
        int top = value["top"];
        int width = value["width"];
        int height = value["height"];

        sf::IntRect rect = {left, top, width, height};
        return rect;
    }

    static Variant ParsePairPairIntValue(const json& arg_value) {
        int x;
        int y;
        int start_x;
        int start_y;

        std::pair<int, int> pair_value;
        std::pair<int, int> pair_value_start;
        std::pair<std::pair<int, int>, std::pair<int, int>> pair_value_comp;

        if (!arg_value.is_object() || !arg_value.contains("x") || !arg_value.contains("y") || !arg_value.contains("start_x") || !arg_value.contains("start_y")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }
        x = arg_value["x"];
        y = arg_value["y"];
        start_x = arg_value["start_x"];
        start_y = arg_value["start_y"];

        pair_value = std::make_pair(x, y);
        pair_value_start = std::make_pair(start_x, start_y);

        pair_value_comp = std::make_pair(pair_value, pair_value_start);
        return pair_value_comp;
    }

    static Variant ParseSinFuncValue(const json& arg_value) {
        double amplitude = arg_value["a"];
        double frequency = arg_value["f"];
        double phase = arg_value["p"];
        SinusoidalFunction sin_func = {amplitude, frequency, phase};
        return sin_func;
    }

    static Variant ParseValue(const std::string& arg_value_type, const json& arg_value) {
        if (arg_value_type == "Sprite") {
            return ParseSpriteValue(arg_value);
        } else if (arg_value_type == "Int") {
            return ParseIntValue(arg_value);
        } else if (arg_value_type == "PairDouble") {
            return ParsePairDoubleValue(arg_value);
        } else if (arg_value_type == "PairInt") {
            return ParsePairIntValue(arg_value);
        } else if (arg_value_type == "Bool") {
            return ParseBoolValue(arg_value);
        } else if (arg_value_type == "Double") {
            return ParseDoubleValue(arg_value);
        } else if (arg_value_type == "Clock") {
            return ParseClockValue(arg_value);
        } else if (arg_value_type == "IntRect") {
            return ParseIntRectValue(arg_value);
        } else if (arg_value_type == "PairPairInt") {
            return ParsePairPairIntValue(arg_value);
        } else if (arg_value_type == "SinFunc") {
            return ParseSinFuncValue(arg_value);
        } else {
            std::cerr << "Unsupported value type: " << arg_value_type << std::endl;
        }

        return Variant();
    }
};