#pragma once

template <class T>
inline T* construct(T* p_memory)
{
    return ::new(p_memory) T;
}

template <class T, typename ARG1>
inline T* construct(T* p_memory, ARG1 a1)
{
    return ::new(p_memory) T(a1);
}

template <class T, typename ARG1, typename ARG2>
inline T* construct(T* p_memory, ARG1 a1, ARG2 a2)
{
    return ::new(p_memory) T(a1, a2);
}

template <class T, typename ARG1, typename ARG2, typename ARG3>
inline T* construct(T* p_memory, ARG1 a1, ARG2 a2, ARG3 a3)
{
    return ::new(p_memory) T(a1, a2, a3);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
inline T* construct(T* p_memory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4)
{
    return ::new(p_memory) T(a1, a2, a3, a4);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
inline T* construct(T* p_memory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4, ARG5 a5)
{
    return ::new(p_memory) T(a1, a2, a3, a4, a5);
}

template <class T, class P>
inline void construct_one_arg(T* p_memory, P const& arg)
{
    ::new(p_memory) T(arg);
}

template <class T, class P1, class P2>
inline void construct_two_arg(T* p_memory, P1 const& arg1, P2 const& arg2)
{
    ::new(p_memory) T(arg1, arg2);
}

template <class T, class P1, class P2, class P3>
inline void construct_three_arg(T* p_memory, P1 const& arg1, P2 const& arg2, P3 const& arg3)
{
    ::new(p_memory) T(arg1, arg2, arg3);
}

template <class T>
inline T* copy_construct(T* p_memory, T const& src)
{
    return ::new(p_memory) T(src);
}

template <class T>
inline void destruct(T* p_memory)
{
    p_memory->~T();
}

inline int utl_memory_calc_new_allocation_count(int n_allocation_count, int n_grow_size, int n_new_size, int n_bytes_item)
{
    if (n_grow_size)
    {
        n_allocation_count = ((1 + ((n_new_size - 1) / n_grow_size)) * n_grow_size);
    }
    else
    {
        if (!n_allocation_count)
        {
            n_allocation_count = (31 + n_bytes_item) / n_bytes_item;
        }

        while (n_allocation_count < n_new_size)
        {
            n_allocation_count *= 2;
        }
    }

    return n_allocation_count;
}

inline void staging_utl_vector_bounds_check(int i, int size)
{
    if ((unsigned)i >= (unsigned)size)
    {
        // Handle out-of-bounds case
    }
}

template <class T, class I = int>
class c_utl_memory
{
public:
    T& operator[](I i)
    {
        return m_p_memory[i];
    }
    T* base();
    const T* base() const;

    void purge();

    bool is_externally_allocated() const;

    int num_allocated() const;
    int count() const;
    void grow(int num = 1);

protected:
    T* m_p_memory;
    int m_n_allocation_count;
    int m_n_grow_size;
};

template <class T, class I>
void c_utl_memory<T, I>::purge()
{
    if (!is_externally_allocated())
    {
        if (m_p_memory)
        {
            free((void*)m_p_memory);
            m_p_memory = 0;
        }
        m_n_allocation_count = 0;
    }
}

template <class T, class I>
inline T* c_utl_memory<T, I>::base()
{
    return m_p_memory;
}

template <class T, class I>
inline const T* c_utl_memory<T, I>::base() const
{
    return m_p_memory;
}

template <class T, class I>
bool c_utl_memory<T, I>::is_externally_allocated() const
{
    return (m_n_grow_size < 0);
}

template <class T, class I>
inline int c_utl_memory<T, I>::num_allocated() const
{
    return m_n_allocation_count;
}

template <class T, class I>
inline int c_utl_memory<T, I>::count() const
{
    return m_n_allocation_count;
}

template <class T, class I>
void c_utl_memory<T, I>::grow(int num)
{
    if (is_externally_allocated())
        return;

    int n_allocation_requested = m_n_allocation_count + num;

    int n_new_allocation_count = utl_memory_calc_new_allocation_count(m_n_allocation_count, m_n_grow_size, n_allocation_requested, sizeof(T));

    if ((int)(I)n_new_allocation_count < n_allocation_requested)
    {
        if ((int)(I)n_new_allocation_count == 0 && (int)(I)(n_new_allocation_count - 1) >= n_allocation_requested)
        {
            --n_new_allocation_count;
        }
        else
        {
            if ((int)(I)n_allocation_requested != n_allocation_requested)
            {
                return;
            }
            while ((int)(I)n_new_allocation_count < n_allocation_requested)
            {
                n_new_allocation_count = (n_new_allocation_count + n_allocation_requested) / 2;
            }
        }
    }

    m_n_allocation_count = n_new_allocation_count;

    if (m_p_memory)
    {
        m_p_memory = (T*)realloc(m_p_memory, m_n_allocation_count * sizeof(T));
    }
    else
    {
        m_p_memory = (T*)malloc(m_n_allocation_count * sizeof(T));
    }
}