#include "CircularBuffer.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer)
{
  CircularBuffer* circularBuffer;

  void setup()
  {
    circularBuffer = new CircularBuffer();
  }
  void teardown()
  {
    delete circularBuffer;
  }
};

TEST(CircularBuffer, Create)
{
  FAIL("Start here");
}

