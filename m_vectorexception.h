
#ifndef M_VECTOREXCEPTION_H
#define M_VECTOREXCEPTION_H
#include <iostream>

class m_vectorException: public std::exception
{
    char *message;
public:
    explicit m_vectorException(const char *msg) : std::exception(){message = (char *)msg;}
    const char *what() const noexcept{return message;} // noexcept - показывает, что никаких исключений не выдаст
};

#endif // M_VECTOREXCEPTION_H
