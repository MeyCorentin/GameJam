#pragma once

#include "../main.hpp"

class JsonParser {
public:
    JsonParser() {}

    static Variant parseSpriteValue(const json& arg_value) {
        sf::Sprite sprite;
        sf::Texture texture;
        std::shared_ptr<sf::Texture> texture_ptr; 
        std::shared_ptr<sf::Sprite> sprite_ptr;

        if (!arg_value.is_string()) {
            std::cerr << "Invalid value for Sprite type." << std::endl;
            return Variant();
        }
        if (!texture.loadFromFile(arg_value)) {
            std::cerr << "Failed to load texture for sprite." << std::endl;
            return Variant();
        }
        texture_ptr = std::make_shared<sf::Texture>(texture);
        sprite_ptr = std::make_shared<sf::Sprite>(sprite);
        sprite_ptr->setTexture(*texture_ptr);
        return std::make_pair(texture_ptr, sprite_ptr);
    }

    static Variant parseIntValue(const json& arg_value) {
        int int_value;

        if (!arg_value.is_number_integer()) {
            std::cerr << "Invalid value for Int type." << std::endl;
            return Variant();
        }
        int_value = arg_value;
        return int_value;
    }

    static Variant parseDoubleValue(const json& arg_value) {

        double double_value = arg_value;
        return double_value;
    }

    static Variant parsePairDoubleValue(const json& arg_value) {
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

    static Variant parsePairIntValue(const json& arg_value) {
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

    static Variant parseBoolValue(const json& arg_value) {
        bool bool_value;

        if (!arg_value.is_boolean()) {
            std::cerr << "Invalid value for Bool type." << std::endl;
            return Variant();
        }
        bool_value = arg_value;
        return bool_value;
    }

    static Variant parseValue(const std::string& arg_value_type, const json& arg_value) {
        if (arg_value_type == "Sprite") {
            return parseSpriteValue(arg_value);
        } else if (arg_value_type == "Int") {
            return parseIntValue(arg_value);
        } else if (arg_value_type == "PairDouble") {
            return parsePairDoubleValue(arg_value);
        } else if (arg_value_type == "PairInt") {
            return parsePairIntValue(arg_value);
        } else if (arg_value_type == "Bool") {
            return parseBoolValue(arg_value);
        } else if (arg_value_type == "Double") {
            return parseDoubleValue(arg_value);
        }

        std::cerr << "Unsupported value type: " << arg_value_type << std::endl;
        return Variant();
    }
};