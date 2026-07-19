#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

enum class TokenType {
    BraceOpen,
    BraceClose,
    BracketOpen,
    BracketClose,
    Colon,
    Comma,
    String,
    Number,
    True,
    False,
    Null,
    EndOfFile
};

class JsonValue {
public:
    enum class JsonType {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };

    explicit JsonValue() {
        type = JsonType::Null;
        value = nullptr;
    }

    explicit JsonValue(const bool boolValue) {
        type = JsonType::Boolean;
        value = boolValue;
    }

    explicit JsonValue(const double numberValue) {
        type = JsonType::Number;
        value = numberValue;
    }

    explicit JsonValue(const std::string &stringValue) {
        type = JsonType::String;
        value = stringValue;
    }

    explicit JsonValue(const std::vector<JsonValue> &vectorValue) {
        type = JsonType::Array;
        value = vectorValue;
    }

    explicit JsonValue(const std::unordered_map<std::string, JsonValue> &objectValue) {
        type = JsonType::Object;
        value = objectValue;
    }

    template<typename T>
    const T& get() const {
        return std::get<T>(value);
    }

    const JsonValue& operator[](const std::string& key) const {
        if (type != JsonType::Object) {
            throw std::runtime_error(
                "Attempted object access with key '" + key + " but value is not an object"
            );
        }

        auto& map = std::get<std::unordered_map<std::string, JsonValue>>(value);

        const auto it = map.find(key);
        if (it == map.end()) {
            throw std::runtime_error(
                "JSON key not found: " + key
            );
        }

        return it->second;
    }

    const JsonValue& operator[](const size_t index) const {
        if (type != JsonType::Array) {
            throw std::runtime_error("Attempted array access with index: " + std::to_string(index) + " but value is not an array");
        }

        auto& vector = std::get<std::vector<JsonValue>>(value);

        try {
            return vector.at(index);
        }
        catch (const std::out_of_range&) {
            throw std::runtime_error(
                "Array index out of bounds: " + std::to_string(index)
            );
        }
    }

    JsonType type;
    std::variant<
        std::nullptr_t,
        bool,
        double,
        std::string,
        std::vector<JsonValue>,
        std::unordered_map<std::string, JsonValue>
    > value;
};

struct JsonToken {
    TokenType type;
    std::string value;
};

struct ParseResult {
    JsonValue value;
    size_t nextIndex{};
};