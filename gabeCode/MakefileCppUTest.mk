#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = GabeBookCode_CppUTest

#--- Inputs ----#
#CPPUTEST_HOME = CppUTest
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/LedDriver \
	src/CircularBuffer\
	../code/src/IO \
	../code/src/util \

TEST_SRC_DIRS = \
	.\
	tests/LedDriver\
	tests/CircularBuffer\
	tests\
	../code/mocks\

	
INCLUDE_DIRS =\
  .\
  include/LedDriver\
  include/CircularBuffer\
  $(CPPUTEST_HOME)/include\
  include/IO\
  ../code/mocks\
  ../code/include/util \
  ../code/include/IO \

MOCKS_SRC_DIRS = \
	../code/mocks\

include ../CppUTestCompileFlags.mk

LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

