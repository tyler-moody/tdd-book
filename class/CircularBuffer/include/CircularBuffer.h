//- Copyright (c) 2018 James Grenning -- See license.txt at https://github.com/jwgrenning/wingman-cyber-dojo

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

#include <array>
#include <memory>
#include <string>

class CircularBuffer
{
  public:
    CircularBuffer(const unsigned int capacity, const int defaultValue);
    virtual ~CircularBuffer();

    bool isEmpty() const;
    bool isFull() const;
    bool put(int);
    int get();
    int capacity() const;

  private:
    size_t m_capacity;
    int *m_storage;
    size_t m_write_index;
    size_t m_read_index;
    int m_default_value;


    CircularBuffer(const CircularBuffer&);
    CircularBuffer& operator=(const CircularBuffer&);
    void printState() const;
};

class CircularBufferException
{
    public:
        CircularBufferException(std::string message)
        : message_(message){}

        std::string message(){return message_;}

    private:
        std::string message_;

};

#endif  // D_CircularBuffer_H
