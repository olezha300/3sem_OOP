#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>

class Octal
{
private:
    unsigned char *data_;
    size_t size_;
    size_t capacity_;

public:
    Octal();

    Octal(const size_t &n, unsigned char t = '0');

    Octal(const std::string &other);

    Octal(const Octal &other);

    Octal(const std::initializer_list<unsigned char> &other);

    Octal(Octal &&other) noexcept;

    Octal &operator=(const Octal &other);

    Octal &operator=(Octal &&other);

    size_t Size() const noexcept;

    std::string toString() const;

    size_t Capacity() const noexcept;

    void Clear() noexcept;

    Octal operator+(const Octal &other) const;

    Octal operator-(const Octal &other) const;

    bool operator>(const Octal &other) const;

    bool operator<(const Octal &other) const;

    bool operator==(const Octal &other) const;

    bool operator!=(const Octal &other) const;

    void push_back(unsigned char digit);

    void push_front(unsigned char digit);

    virtual ~Octal() noexcept;
};
