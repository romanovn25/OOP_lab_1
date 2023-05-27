#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <initializer_list>
#include <m_vectorexception.h>

template<typename Type>
class m_vector
{
private:
    Type *m_vec;
    int amount;
public:
    class Iterator
    {
    private:
        m_vector<Type> it_m_vector;
        int it_m_vector_index = -1;
    public:
        Iterator(m_vector<Type> container_obj);
        Iterator next();
        Type value();
        bool is_end();
        Iterator &operator++();
        Type &operator*();
        bool operator ==(Iterator &b);
        bool operator !=(Iterator &b);
    };
    m_vector(int length);
    m_vector(const m_vector<Type> &vect);
    m_vector(m_vector<Type> &&vect);
    explicit m_vector(std::initializer_list<Type> lst);
    ~m_vector();
    m_vector<Type> &operator=(const m_vector<Type> &lst);
    Type &operator[](int index) const;
    int get_length() const;
    void set_elem(int index, const Type &elem);
    Type &get_elem(int index) const;
    Type *to_array();
    template <class X> friend std::ostream &operator<<(std::ostream &os, const m_vector<X> &lst);
    m_vector<Type> &operator+=(const m_vector<Type> &vect);
    m_vector<Type> &operator-=(const m_vector<Type> &vect);
    m_vector<Type> &operator*=(const Type &val);
    m_vector<Type> &operator/=(const Type &val);
    template<typename _T> friend m_vector<_T> operator+(const m_vector<_T> &v1, const m_vector<_T> &v2);
    template<typename _T> friend m_vector<_T> operator-(const m_vector<_T> &v1, const m_vector<_T> &v2);
    template<typename _T, typename T> friend m_vector<_T> operator*(const m_vector<_T> &v1, const T &val);
    template<typename _T, typename T> friend m_vector<_T> operator/(const m_vector<_T> &v1, const T &val);
    Iterator iterator_begin();
    Iterator iterator_end();
};

template <typename Type>
bool m_vector<Type>::Iterator::operator!=(Iterator &b)
{
    return !(*this == b);
}

template <typename Type>
bool m_vector<Type>::Iterator::operator==(Iterator &b)
{
    return (&it_m_vector + it_m_vector_index) == (&(b.it_m_vector) + b.it_m_vector_index);
}

template <typename Type>
Type &m_vector<Type>::Iterator::operator*()
{
    return it_m_vector[it_m_vector_index];
}

template <typename Type>
typename m_vector<Type>::Iterator &m_vector<Type>::Iterator::operator++()
{
    m_vector<Type>::Iterator::next();
    return *this;
}

template <typename Type>
bool m_vector<Type>::Iterator::is_end()
{
    return (it_m_vector_index == it_m_vector.get_length()-1 || it_m_vector.get_length() == 0);
}

template <typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::Iterator::next()
{
    if(!this->is_end())
        it_m_vector_index += 1;
    return *this;
}

template <typename Type>
Type m_vector<Type>::Iterator::value()
{
    return it_m_vector[it_m_vector_index];
}

template <typename Type>
m_vector<Type>::Iterator::Iterator(m_vector<Type> container_obj) : it_m_vector(container_obj), it_m_vector_index(0){}

template<typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::iterator_begin()
{
    return m_vector<Type>::Iterator(*this);
}

template<typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::iterator_end()
{
    m_vector<Type>::Iterator it = m_vector<Type>::Iterator(*this);
    while(!it.is_end())
        it.next();
    return it;
}

template<typename _T, typename T>
m_vector<_T> operator/(const m_vector<_T> &v1, const T &val)
{
    if(val == 0)
        throw m_vectorException("devide to zero");
    m_vector<_T> local = v1;
    for(int i = 0; i < local.amount; i++)
        local.m_vec[i] /= val;
    return local;
}

template<typename _T, typename T>
m_vector<_T> operator*(const m_vector<_T>& v1, const T &val)
{
    m_vector<_T> local = v1;
    for(int i = 0; i < local.amount; i++)
        local.m_vec[i] *= val;
    return local;
}

template<typename _T>
m_vector<_T> operator-(const m_vector<_T> &v1, const m_vector<_T> &v2)
{
    if(v1.get_length() != v2.get_length())
        throw m_vectorException("bad lenght of v1 and v2");
    m_vector<_T> local(v1.get_length());
    for(int i = 0; i < local.amount; i++)
        local[i] = (v1[i] - v2[i]);
    return local;
}

template<typename _T>
m_vector<_T> operator+(const m_vector<_T>& v1, const m_vector<_T>&v2)
{
    if(v1.get_length() != v2.get_length())
        throw m_vectorException("bad lenght of v1 and v2");
    m_vector<_T> local(v1.get_length());
    for(int i = 0; i < local.amount; i++)
        local[i] = (v1[i] + v2[i]);
    return v1;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator /=(const Type &val)
{
    *this = *this / val;
    return *this;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator *=(const Type& val)
{
    *this = *this * val;
    return *this;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator -=(const m_vector<Type>& vect)
{
    *this = *this - vect;
    return *this;
}

template<typename Type>
m_vector<Type> &m_vector<Type>::operator+=(const m_vector<Type> &vect)
{
    *this = *this + vect;
    return *this;
}

template<typename Type>
std::ostream &operator<<(std::ostream& os, const m_vector<Type> &lst)
{
    std::string container = "m_vector{amount: " + std::to_string(lst.amount) + ", list: [";
    for(int i = 0; i < lst.amount; i++)
        container += std::to_string(lst.m_vec[i]) + ", ";
    if(lst.amount > 0)
        container = container.substr(0, container.size()-2); // Удалить два лишних ", "
    container += "]}";
    return os << container;
}

template<typename Type>
Type *m_vector<Type>::to_array()
{
    try{
        Type *array = new Type[amount];
        for(int i =0; i < amount; i++)
            array[i] = m_vec[i];
        return array;
    } catch (std::bad_alloc const&){
        m_vec = nullptr;
        throw m_vectorException("bad alloc");
    }
}

template<typename Type>
Type &m_vector<Type>::get_elem(int index) const
{
    if(index < 0 || amount <= index)
        throw m_vectorException("Wrong index of m_vector");
    return m_vec[index];
}

template<typename Type>
void m_vector<Type>::set_elem(int index, const Type &elem)
{
    get_elem(index) = elem;
}

template<typename Type>
int m_vector<Type>::get_length() const
{
    return amount;
}

template<typename Type>
m_vector<Type>::m_vector(int length)
{
    try {
        if(length <= 0)
            throw m_vectorException("Bad length of m_vector");
        amount = length;
        m_vec = new Type[length]{};
    } catch (std::bad_alloc const&){
        m_vec = nullptr;
        throw m_vectorException("bad alloc");
    }
}

template<typename Type>
m_vector<Type>::m_vector(const m_vector<Type> &vect)
{
    try {
        amount = vect.amount;
        m_vec = new Type[amount];
        for(int i = 0; i < amount; i++)
            m_vec[i] = vect.m_vec[i];
    } catch (std::bad_alloc const&){
        m_vec = nullptr;
        throw m_vectorException("bad alloc");
    }
}

template<typename Type>
m_vector<Type>::m_vector(m_vector<Type> &&vect)
{
    m_vec = vect.m_vec;
    amount = vect.amount;
    vect.amount = 0;
    vect.m_vec = nullptr;
}

template<typename Type>
m_vector<Type>::m_vector(std::initializer_list<Type> lst) : amount(lst.size())
{
    if(amount < 0)
        throw m_vectorException("Bad length of m_vector");
    try{
        m_vec = new Type[amount]{};
        int i = 0;
        for(Type item : lst)
            m_vec[i++] = item;
    } catch (std::bad_alloc const&){
        m_vec = nullptr;
        throw m_vectorException("bad alloc");
    }
}

template<typename Type>
m_vector<Type>::~m_vector()
{
    if(m_vec != nullptr)
        delete[] m_vec;
}

template<typename Type>
m_vector<Type> &m_vector<Type>::operator=(const m_vector<Type> &lst)
{
    m_vector<Type> local(lst);
    *this = local;
    return *this;
}

template<typename Type>
Type &m_vector<Type>::operator[](int index) const
{
    return get_elem(index);
}

#endif // M_VECTOR_H
