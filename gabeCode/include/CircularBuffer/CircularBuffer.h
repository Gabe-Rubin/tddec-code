#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

///////////////////////////////////////////////////////////////////////////////
//
//  CircularBuffer is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class CircularBuffer
  {
  public:
    explicit CircularBuffer();
    ~CircularBuffer();

    CircularBuffer(const CircularBuffer&);
    CircularBuffer& operator=(const CircularBuffer&);

  };

#endif  // D_CircularBuffer_H
