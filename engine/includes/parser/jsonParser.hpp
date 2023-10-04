#pragma once

#include "../main.hpp"

class JsonParser {
public:
    JsonParser() {}

    static Variant parseSpriteValue(const json& _value) {
        if (!_value.is_string()) {
            std::cerr << "Invalid value for Sprite type." << std::endl;
            return Variant();
        }

        sf::Sprite sprite;
        sf::Texture texture;
        if (!texture.loadFromFile(_value)) {
            std::cerr << "Failed to load texture for sprite." << std::endl;
            return Variant();
        }

        std::shared_ptr<sf::Texture> texturePtr = std::make_shared<sf::Texture>(texture);
        std::shared_ptr<sf::Sprite> spritePtr = std::make_shared<sf::Sprite>(sprite);
        spritePtr->setTexture(*texturePtr);
        return std::make_pair(texturePtr, spritePtr);
    }

    static Variant parseIntValue(const json& value) {
        if (!value.is_number_integer()) {
            std::cerr << "Invalid value for Int type." << std::endl;
            return Variant();
        }

        int intValue = value;
        return intValue;
    }

    static Variant parseDoubleValue(const json& value) {

        double doubleValue = value;
        return doubleValue;
    }

    static Variant parsePairDoubleValue(const json& value) {
        if (!value.is_object() || !value.contains("x") || !value.contains("y")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }

        double x = value["x"];
        double y = value["y"];
        std::pair<double, double> pairValue = std::make_pair(x, y);
        return pairValue;
    }

    static Variant parsePairIntValue(const json& value) {
        if (!value.is_object() || !value.contains("x") || !value.contains("y")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }

        int x = value["x"];
        int y = value["y"];
        std::pair<int, int> pairValue = std::make_pair(x, y);
        return pairValue;
    }

    static Variant parseBoolValue(const json& value) {
        if (!value.is_boolean()) {
            std::cerr << "Invalid value for Bool type." << std::endl;
            return Variant();
        }

        bool boolValue = value;
        return boolValue;
    }

    static Variant parseClockValue(const json& value) {
        sf::Clock clock;
        std::shared_ptr<sf::Clock> clockValue = std::make_shared<sf::Clock>(clock);
        return clockValue;
    }

    static Variant parseIntRectValue(const json& value) {
        if (!value.is_object() || !value.contains("left") || !value.contains("top") || !value.contains("width") || !value.contains("height")) {
            std::cerr << "Invalid value for Pair type." << std::endl;
            return Variant();
        }

        int left = value["left"];
        int top = value["top"];
        int width = value["width"];
        int height = value["height"];

        sf::IntRect rect = {left, top, width, height};
        std::shared_ptr<sf::IntRect> rectValue = std::make_shared<sf::IntRect>(rect);
        return rectValue;
    }

    static Variant parseValue(const std::string& valueType, const json& value) {
        if (valueType == "Sprite") {
            return parseSpriteValue(value);
        } else if (valueType == "Int") {
            return parseIntValue(value);
        } else if (valueType == "PairDouble") {
            return parsePairDoubleValue(value);
        } else if (valueType == "PairInt") {
            return parsePairIntValue(value);
        } else if (valueType == "Bool") {
            return parseBoolValue(value);
        } else if (valueType == "Double") {
            return parseDoubleValue(value);
        } else if (valueType == "Clock") {
            return parseClockValue(value);
        } else if (valueType == "IntRect") {
            return parseIntRectValue(value);
        }

        std::cerr << "Unsupported value type: " << valueType << std::endl;
        return Variant();
    }
};