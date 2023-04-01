#pragma once

template <typename T>
class shared_ptr
{
public:
    // default ctor
    shared_ptr()
        : m_ptr(nullptr)
        , m_ref_count(new int(0))
    {
    }

    // ctor with param.
    shared_ptr(T* ptr)
        : m_ptr(ptr)
        , m_ref_count(new int(1))
    {
    }

    ~shared_ptr(); // dtor

    // copy semantics
    shared_ptr(const shared_ptr<T>& obj); // copy ctor
    shared_ptr<T>& operator=(const shared_ptr<T>& obj); // copy assignment

    // move semantics
    shared_ptr(shared_ptr<T>&& obj); // move ctor
    shared_ptr<T>& operator=(shared_ptr<T>&& obj); // move assignment

    // observers
    T& operator*() const;
    T* operator->() const;
    T& operator[](std::size_t index) const;

    int get_count() const;

    // Modifiers
    void swap(shared_ptr<T>& other);


private:
    void release();

private:
    T* m_ptr;
    int* m_ref_count;
};

template <typename T>
void shared_ptr<T>::release()
{
    if (m_ptr) {
        --(*m_ref_count);
        if (*m_ref_count == 0) {
            delete m_ptr;
            delete m_ref_count;

            m_ptr = nullptr;
            m_ref_count = nullptr;
        }
    }
}

// dtor
template <typename T>
shared_ptr<T>::~shared_ptr()
{
    release();
}

// copy semantics
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& other)
{
    m_ptr = other.m_ptr;
    m_ref_count = other.m_ref_count;
    ++(*m_ref_count);
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other)
{
    if (m_ptr != other.m_ptr) {
        release();
        m_ptr = other.m_ptr;
        m_ref_count = other.m_ref_count;
        ++(*m_ref_count);
    }
    return *this;
}

// move semantics
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& other)
{
    m_ptr = other.m_ptr;
    m_ref_count = other.m_ref_count;

    other.m_ptr = nullptr;
    other.m_ref_count = nullptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other)
{
    if (this != &other) {
        release();

        m_ptr = other.m_ptr;
        m_ref_count = other.m_ref_count;

        other.m_ptr = nullptr;
        other.m_ref_count = nullptr;
    }
    return *this;
}


template <typename T>
T& shared_ptr<T>::operator*() const
{
    return *m_ptr;
}

template <typename T>
T* shared_ptr<T>::operator->() const
{
    return m_ptr;
}

template <typename T>
T& shared_ptr<T>::operator[](std::size_t index) const
{
    return m_ptr[index];
}

template <typename T>
int shared_ptr<T>::get_count() const
{
    return *m_ref_count;
}


template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& other)
{
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_ref_count, other.m_ref_count);
}
