#include "CircularBuffer.h"

extern "C"
{
#include "RuntimeError.h"
}

namespace
{
    void nextPosition(int &position, int capacity)
    {
        ++position;
        if (position == capacity)
        {
            position = 0;
        }
    }

    void prevPosition(int &position, int size)
    {
        --position;
        if(position < 0)
        {
            position = size;
        }
    }

    void incrementSizeIfAvailableCapacity(int &size, int capacity)
    {
        if(size < capacity)
        {
            ++size;
        }
    }
}

CircularBuffer::CircularBuffer(int capacity) : _capacity{capacity}
{
    this->_vals = new int[this->_capacity];
}

CircularBuffer::~CircularBuffer()
{
    delete[] this->_vals;
}

void CircularBuffer::push(int val)
{
    this->_vals[this->_pos] = val;
    nextPosition(this->_pos, this->_capacity);
    incrementSizeIfAvailableCapacity(this->_size, this->_capacity);
}

int CircularBuffer::pop()
{
    int val = 0;
    if (!this->empty())
    {
        prevPosition(this->_pos, this->_size);
        val = this->_vals[this->_pos];
        --this->_size;
    }
    else
    {
        RUNTIME_ERROR("Circular Buffer: buffer empty", -1);
    }
    return val;
}

bool CircularBuffer::empty() const
{
    return this->_size == 0;
}

int CircularBuffer::size() const
{
    return this->_size;
}

int CircularBuffer::capacity() const
{
    return this->_capacity;
}
