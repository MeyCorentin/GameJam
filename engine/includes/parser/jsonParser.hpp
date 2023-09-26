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

    static Variant parsePairValue(const json& value) {
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

    static Variant parseValue(const std::string& valueType, const json& value) {
        if (valueType == "Sprite") {
            return parseSpriteValue(value);
        } else if (valueType == "Int") {
            return parseIntValue(value);
        } else if (valueType == "Pair") {
            return parsePairValue(value);
        } else if (valueType == "Bool") {
            return parseBoolValue(value);
        }

        std::cerr << "Unsupported value type: " << valueType << std::endl;
        return Variant();
    }
};