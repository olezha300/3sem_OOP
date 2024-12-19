#include "../include/Octal.hpp"
#include <string>
#include <cstring>
#include <stdexcept>

Octal::Octal() : size_{0}, data_{nullptr}, capacity_{0}
{
  std::cout << "Default constructor" << std::endl;
}

Octal::Octal(const size_t &n, unsigned char t) : size_{n}, data_{new unsigned char[n]}, capacity_{n}
{
  for (size_t i{0}; i < size_; ++i)
  {
    if (t > 7)
    {
      throw std::invalid_argument("Недопустимая восьмеричная цифра.");
    }
    data_[i] = t;
  }
}

Octal::Octal(const std::string &other) : size_{other.size()}, data_{new unsigned char[other.size()]},
                                         capacity_{other.size()}
{
  size_t temp = size_ - 1;
  for (size_t i = 0; i < other.size(); ++i)
  {
    if (other[i] < '0' || other[i] > '7')
    {
      throw std::invalid_argument("Некорректный восьмеричный символ.");
    }
    data_[temp--] = other[i] - '0'; // Преобразуем символ обратно в число
  }
}

Octal::Octal(const std::initializer_list<unsigned char> &other)
    : size_{other.size()}, capacity_{other.size()}, data_{new unsigned char[other.size()]}
{
  size_t i = 0;
  for (const unsigned char &val : other)
  {
    if (val > 7)
    {
      throw std::invalid_argument("Недопустимая восьмеричная цифра.");
    }
    data_[i++] = val; // Храним восьмеричную цифру как есть, без преобразования
  }
}

Octal::Octal(const Octal &other) : data_(new unsigned char[other.Size()]), size_(other.Size()),
                                   capacity_(other.Capacity())
{
  std::memcpy(data_, other.data_, size_);
}

Octal::Octal(Octal &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Octal &Octal::operator=(const Octal &other)
{
  if (this != &other)
  {
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new unsigned char[capacity_];
    std::memcpy(data_, other.data_, size_);
  }
  return *this;
}

Octal &Octal::operator=(Octal &&other)
{
  if (this != &other)
  {
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new unsigned char[capacity_];
    std::memcpy(data_, other.data_, size_);
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
  }
  return *this;
}

size_t Octal::Size() const noexcept
{
  return size_;
}

std::string Octal::toString() const
{
  std::string result;
  result.reserve(size_); // Резервируем память для повышения эффективности
  for (size_t i = size_; i > 0; --i)
  {
    result += static_cast<char>(data_[i - 1] + '0'); // Преобразуем цифры обратно в символы
  }
  return result;
}

Octal Octal::operator+(const Octal &other) const
{
  Octal result;
  size_t sizeMax = std::max(size_, other.size_); // Максимальный размер между двумя числами
  result.capacity_ = sizeMax + 1;                // Резервируем место для возможного переноса в следующий разряд
  result.data_ = new unsigned char[result.capacity_];
  result.size_ = 0;
  unsigned char carry = 0; // Перенос для восьмеричной системы

  for (size_t i = 0; i < sizeMax || carry; ++i)
  {
    unsigned char sum = carry; // Добавляем перенос от предыдущего разряда
    if (i < size_)
    {
      sum += data_[i]; // Добавляем текущий разряд первого числа
    }
    if (i < other.size_)
    {
      sum += other.data_[i]; // Добавляем текущий разряд второго числа
    }

    carry = sum >= 8;                       // Если сумма больше или равна 8, переносим 1 в следующий разряд
    result.data_[result.size_++] = sum % 8; // Остаток от деления на 8 — это текущий разряд
  }

  return result;
}

Octal Octal::operator-(const Octal &other) const
{
  if (*this < other)
  {
    throw std::invalid_argument("Результат вычитания не может быть отрицательным.");
  }

  Octal result;
  result.capacity_ = size_;
  result.data_ = new unsigned char[result.capacity_];
  result.size_ = 0;
  unsigned char borrow = 0; // Переменная для заема при необходимости

  for (size_t i = 0; i < size_; ++i)
  {
    // Вычитаем текущий разряд и заем
    unsigned char diff = data_[i] - borrow;

    // Если есть соответствующий разряд в other, вычитаем его
    if (i < other.size_)
    {
      diff -= other.data_[i];
    }

    // Если результат отрицательный, берем заем из следующего разряда
    if (diff < 0)
    {
      borrow = 1;
      diff += 8; // Добавляем 8, чтобы получить корректную цифру в восьмеричной системе
    }
    else
    {
      borrow = 0;
    }

    // Записываем результат в массив
    result.data_[result.size_++] = diff;
  }

  // Удаление ведущих нулей
  while (result.size_ > 1 && result.data_[result.size_ - 1] == 0)
  {
    result.size_--;
  }

  return result;
}

bool Octal::operator<(const Octal &other) const
{
  if (size_ != other.size_)
    return size_ < other.size_;
  for (size_t i = size_; i-- > 0;)
  {
    if (data_[i] != other.data_[i])
      return data_[i] < other.data_[i];
  }
  return false;
}

bool Octal::operator>(const Octal &other) const
{
  if (size_ != other.size_)
    return size_ > other.size_;
  for (size_t i = size_; i-- > 0;)
  {
    if (data_[i] != other.data_[i])
      return data_[i] > other.data_[i];
  }
  return false;
}

bool Octal::operator==(const Octal &other) const
{
  if (size_ != other.size_)
    return false;
  return std::equal(data_, data_ + size_, other.data_);
}

bool Octal::operator!=(const Octal &other) const
{
  return !(*this == other);
}

void Octal::Clear() noexcept
{
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

size_t Octal::Capacity() const noexcept
{
  return capacity_;
}

void Octal::push_back(unsigned char digit)
{
  if (digit > 7)
  {
    throw std::invalid_argument("Недопустимая восьмеричная цифра.");
  }

  if (size_ == capacity_)
  {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    unsigned char *newDigits = new unsigned char[newCapacity];
    if (data_)
    {
      std::memcpy(newDigits, data_, size_);
      delete[] data_;
    }
    data_ = newDigits;
    capacity_ = newCapacity;
  }
  data_[size_++] = digit;
}

Octal::~Octal() noexcept
{
  delete[] data_;
}
