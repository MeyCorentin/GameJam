#pragma once

#include "../main.hpp"

class JsonParser {
public:
    JsonParser();

    static Variant ParseSpriteValue(const json& arg_value);

    static Variant ParseIntValue(const json& arg_value);

    static Variant ParseDoubleValue(const json& arg_value);

    static Variant ParsePairDoubleValue(const json& arg_value);

    static Variant ParsePairIntValue(const json& arg_value);

    static Variant ParseBoolValue(const json& arg_value);

    static Variant ParseClockValue(const json& value);

    static Variant ParseIntRectValue(const json& value);

    static Variant ParsePairPairIntValue(const json& arg_value);

    static Variant ParseSinFuncValue(const json& arg_value);

    static Variant ParseValue(const std::string& arg_value_type, const json& arg_value);

    static Variant ParseVectorEntityValue(const json& arg_value);

    static Variant ParseSoundValue(const json& arg_value);

    static Variant ParseSoundBufferValue(const json& arg_value);

    static Variant ParseStringValue(const json& arg_value);

    static Variant ParseTextureValue(const json& arg_value);

    static Variant ParseTextValue(const json& arg_value);
};