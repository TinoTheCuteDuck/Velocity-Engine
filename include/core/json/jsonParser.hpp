#pragma once

#include "core/json/jsonTypes.hpp"

class JsonParser {
public:
    static JsonValue load(const std::string &filePath);

private:
    static std::string readFile(const std::string &filePath);
    static std::vector<JsonToken> lex(const std::string &text);
    static JsonValue parse(const std::vector<JsonToken> &tokens);

    static ParseResult parseObject(const std::vector<JsonToken> &tokens, size_t index);
    static ParseResult parseArray(const std::vector<JsonToken> &tokens, size_t index);
};
