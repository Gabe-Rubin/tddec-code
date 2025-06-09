#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

///////////////////////////////////////////////////////////////////////////////
//
//  CircularBuffer is responsible for practicing TDD for making a Circular Buffer.
//
///////////////////////////////////////////////////////////////////////////////

class CircularBuffer
{
  public:
    explicit CircularBuffer(int capacity);
    ~CircularBuffer();

    CircularBuffer(const CircularBuffer&);
    CircularBuffer& operator=(const CircularBuffer&);

    void push(int val);
    int pop();

    bool empty() const;
    int size() const;
    int capacity() const;

  private:
    bool _empty = true;
    int _size = 0;
    const int _capacity = 0;
    int * _vals = nullptr;
    int _pos = 0;

};

#endif  // D_CircularBuffer_H
