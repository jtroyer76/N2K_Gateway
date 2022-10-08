#pragma once

#include <string>
#include <cstring>
#include <unordered_map>

using std::string;

class SettingVariant
{
    union VariantContent
    {
        float asFloat;
        bool asBoolean;
        int asInteger;

        struct
        {
            const char *data;
            size_t size;
        } asString;

        struct
        {
            const SettingVariant *data;
            size_t size;
        } asList;

    } _content;

public:
    template <typename T>    
    void set(typename std::enable_if<std::is_same<T, int>::value, T>::type value)
    {
        _content.asInteger = value;
    }

    template <typename T>
    void set(typename std::enable_if<std::is_same<T, bool>::value, T>::type value)
    {
        _content.asBoolean = value;
    }

    template <typename T>
    void set(typename std::enable_if<std::is_same<T, string>::value, T>::type value)
    {
        _content.asString.data = value.c_str();
        _content.asString.size = value.size();
    }

    template <typename T>
    void set(typename std::enable_if<std::is_same<T, float>::value, T>::type value)
    {
        _content.asFloat = value;
    }

    template <typename T>
    void set(typename std::enable_if<std::is_same<T, const char*>::value, T>::type value)
    {
        _content.asString.data = value;
        _content.asString.size = std::strlen(value);
    }

    template <typename T>
    typename std::enable_if<std::is_same<T, int>::value, T>::type
    as() const
    {
        return _content.asInteger;
    }

    template <typename T>
    typename std::enable_if<std::is_same<T, string>::value, T>::type
    as() const
    {
        return _content.asString;
    }

    template <typename T>
    operator T() const
    {
        return as<T>();
    }

    template <typename T>
    void operator =(T value)
    {
        set<T>(value);
    }
};

class Settings
{
    std::unordered_map<std::string, SettingVariant *> _settings;

public:
    SettingVariant& operator[](std::string const &name)
    {
        auto it = _settings.find(name);
        if(it == _settings.end())
        {
            _settings[name] = new SettingVariant();
        }

        return *_settings[name];
    }
};
