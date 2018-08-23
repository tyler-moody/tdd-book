//- Copyright (c) 2018 James Grenning -- See license.txt at https://github.com/jwgrenning/wingman-cyber-dojo

#include <iostream>
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(const unsigned int capacity, const int defaultValue) :
    m_capacity(capacity+1),         // lazy way to manage wrapping for full/empty
    m_storage(new int[m_capacity]),
    m_write_index(0),
    m_read_index(0),
    m_default_value(defaultValue)
{
}

CircularBuffer::~CircularBuffer()
{
    delete[] m_storage;
}

bool CircularBuffer::isEmpty() const {
    return m_read_index == m_write_index;
}

bool CircularBuffer::isFull() const {
    return (m_write_index == m_read_index - 1) || 
        (m_write_index == m_capacity-1 && m_read_index == 0);
}

void CircularBuffer::printState() const {
    std::cout << "wi " << m_write_index << " ri " << m_read_index << " storage";
    for (size_t i = 0; i < m_capacity; ++i){
        std::cout << " " << m_storage[i];
    }
    std::cout << std::endl;
}

bool CircularBuffer::put(int i) {
    if (!isFull()){
        m_storage[m_write_index] = i;
        m_write_index = (m_write_index+1) % m_capacity;
        return true;
    } else {
        return false;
    }
}

int CircularBuffer::get() {
    if (isEmpty()){
        return m_default_value;
    } else {
        int r = m_storage[m_read_index];
        m_read_index = (m_read_index+1) % m_capacity;
        return r;
    }
}

int CircularBuffer::capacity() const {
    return m_capacity-1;
}
