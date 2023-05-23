
#ifndef M_VECTOREXCEPTION_H
#define M_VECTOREXCEPTION_H
#include <iostream> // библиотека для использования пространства имен std

class m_vectorException: public std::exception // public, как наследуется - protected & public идет для всех
{ // что значит пространство имен std
private:
    char *message;
public:
    // параметртизированный конструктор - тут частично
    explicit m_vectorException(const char *msg) : std::exception(){message = (char *)msg;} // explicit - запрещает неявный вызов, используется только на конструкторах
    const char *what() const noexcept{return message;} // noexcept - показывает, что никаких исключений не выдаст
    // два const, первый показывает что вернет константый тип, второый показывает, что внутренний this метода будеи константый
};

#endif // M_VECTOREXCEPTION_H
