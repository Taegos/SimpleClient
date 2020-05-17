#pragma once
#include <iostream>

class SimpleLogger
{
public:
    SimpleLogger(bool enabled = true) : enabled{ enabled } {}

    template<typename T>
    void out(T) const;

    template<typename T, typename ...Args>
    void out(T, Args...) const;

    template<typename T>
    void outnl(T) const;

    template<typename T, typename ...Args>
    void outnl(T, Args...) const;

private:
    const bool enabled;
};

template<>
inline void SimpleLogger::out(std::wstring str) const {
    if (!enabled) return;
    std::wcout << str;
}

template<>
inline void SimpleLogger::out(float f) const {
    if (!enabled) return;
    std::cout << f;
}

template<typename T>
void SimpleLogger::out(T t) const {
    if (!enabled) return;
    std::cout << t;
}

template<typename T, typename ...Args>
void SimpleLogger::out(T t, Args... args)const {
    out(t);
    out(args...);
}

template<typename T>
void SimpleLogger::outnl(T t) const {
    out(t, '\n');
}

template<typename T, typename ...Args>
void SimpleLogger::outnl(T t, Args... args) const {
    out(t, args..., '\n');
}