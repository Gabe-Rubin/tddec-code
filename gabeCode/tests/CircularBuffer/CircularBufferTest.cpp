#include "CircularBuffer.h"

extern "C"
{
#include "RuntimeErrorStub.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer)
{
  CircularBuffer* circularBuffer;

  void setup()
  {
    circularBuffer = new CircularBuffer(5);
  }
  void teardown()
  {
    delete circularBuffer;
  }
};

TEST(CircularBuffer, EmptyAtStart)
{
  CHECK_EQUAL(true, circularBuffer->empty());
}

TEST(CircularBuffer, AddOneValue)
{
  circularBuffer->push(42);
  CHECK_EQUAL(false, circularBuffer->empty());
}

TEST(CircularBuffer, RemoveOneValue)
{
  circularBuffer->push(9);
  CHECK_EQUAL(9, circularBuffer->pop());
}

TEST(CircularBuffer, AddMultipleValues)
{
  circularBuffer->push(42);
  circularBuffer->push(-1);
  circularBuffer->push(7);
  circularBuffer->push(17);
  CHECK_EQUAL(4, circularBuffer->size());
}

TEST(CircularBuffer, RemoveMultipleValues)
{
  circularBuffer->push(12);
  circularBuffer->push(-900);
  circularBuffer->push(42);
  CHECK_EQUAL(42, circularBuffer->pop());
}

TEST(CircularBuffer, RemoveValueDecrementsSize)
{
  circularBuffer->push(-9);
  circularBuffer->push(12);
  circularBuffer->pop();
  CHECK_EQUAL(1, circularBuffer->size());
}

TEST(CircularBuffer, GetCapacity)
{
  CircularBuffer circularBuffer(21);
  CHECK_EQUAL(21, circularBuffer.capacity());
}

TEST(CircularBuffer, RemoveValueWhenEmpty)
{
  circularBuffer->pop();
  STRCMP_EQUAL("Circular Buffer: buffer empty", RuntimeErrorStub_GetLastError());
  CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
  CHECK_EQUAL(0, circularBuffer->size());
}

TEST(CircularBuffer, RemoveMoreValuesThanSpaces)
{
  circularBuffer->push(0);
  circularBuffer->push(10);
  circularBuffer->push(20);
  circularBuffer->push(30);
  circularBuffer->push(40);
  circularBuffer->push(50);
  CHECK_EQUAL(5, circularBuffer->size());
  CHECK_EQUAL(50, circularBuffer->pop());
  CHECK_EQUAL(40, circularBuffer->pop());
  CHECK_EQUAL(30, circularBuffer->pop());
  CHECK_EQUAL(20, circularBuffer->pop());
  CHECK_EQUAL(10, circularBuffer->pop());
  CHECK_EQUAL(0, circularBuffer->size());
  circularBuffer->push(-2);
  circularBuffer->push(-3);
  circularBuffer->push(-4);
  circularBuffer->push(5);
  circularBuffer->push(6);
  circularBuffer->push(7);
  CHECK_EQUAL(5, circularBuffer->size());
  CHECK_EQUAL(7, circularBuffer->pop());
  circularBuffer->push(8);
  circularBuffer->push(9);
  circularBuffer->push(10);
  CHECK_EQUAL(5, circularBuffer->size());
  CHECK_EQUAL(10, circularBuffer->pop());
  CHECK_EQUAL(9, circularBuffer->pop());
  CHECK_EQUAL(8, circularBuffer->pop());
}
