#pragma once

template <class T, class A = c_utl_memory<T>>
class c_utl_vector
{
    typedef A c_allocator;

public:
    T& operator[](int i);
    T& element(int i);
    const T& element(int i) const;

    int count() const
    {
        return m_size;
    }

    T& get_tail();
    const T& get_tail() const;

    inline void reset_dbg_info() {}
    int add_to_tail();
    int add_to_tail(const T& src);
    void remove(int elem);
    void remove_all();

    void purge();
    void shift_elements_right(int elem, int num = 1);
    void shift_elements_left(int elem, int num = 1);
    int insert_before(int elem);
    int insert_before(int elem, const T& src);

protected:
    void grow_vector(int num = 1)
    {
        if (m_size + num > m_memory.num_allocated())
        {
            m_memory.grow(m_size + num - m_memory.num_allocated());
        }

        m_size += num;
    }

    c_allocator m_memory;
    int m_size;
    T* m_p_elements;
};

template< typename T, class A >
void c_utl_vector<T, A>::shift_elements_right(int elem, int num)
{
    int num_to_move = m_size - elem - num;
    if ((num_to_move > 0) && (num > 0))
        memmove(&element(elem + num), &element(elem), num_to_move * sizeof(T));
}

template< typename T, class A >
void c_utl_vector<T, A>::shift_elements_left(int elem, int num)
{
    int num_to_move = m_size - elem - num;
    if ((num_to_move > 0) && (num > 0))
    {
        memmove(&element(elem), &element(elem + num), num_to_move * sizeof(T));
    }
}

template< typename T, class A >
int c_utl_vector<T, A>::insert_before(int elem)
{
    grow_vector();
    shift_elements_right(elem);
    construct(&element(elem));
    return elem;
}

template< typename T, class A >
int c_utl_vector<T, A>::insert_before(int elem, const T& src)
{
    grow_vector();
    shift_elements_right(elem);
    construct(&element(elem), src);
    return elem;
}

template< typename T, class A >
inline int c_utl_vector<T, A>::add_to_tail()
{
    return insert_before(m_size);
}

template< typename T, class A >
int c_utl_vector<T, A>::add_to_tail(const T& src)
{
    return insert_before(m_size, src);
}

template< typename T, class A >
void c_utl_vector<T, A>::remove(int elem)
{
    destruct(&element(elem));
    shift_elements_left(elem);
    --m_size;
}

template< typename T, class A >
void c_utl_vector<T, A>::remove_all()
{
    for (int i = m_size; --i >= 0; )
    {
        destruct(&element(i));
    }

    m_size = 0;
}

template< typename T, class A >
inline void c_utl_vector<T, A>::purge()
{
    remove_all();
    m_memory.purge();
    reset_dbg_info();
}

template< typename T, class A >
inline T& c_utl_vector<T, A>::operator[](int i)
{
    return m_memory[i];
}

template< typename T, class A >
inline T& c_utl_vector<T, A>::element(int i)
{
    return m_memory[i];
}

template< typename T, class A >
inline const T& c_utl_vector<T, A>::element(int i) const
{
    return m_memory[i];
}

template <typename T, class A>
T& c_utl_vector<T, A>::get_tail()
{
    return element(m_size - 1);
}

template <typename T, class A>
const T& c_utl_vector<T, A>::get_tail() const
{
    return element(m_size - 1);
}