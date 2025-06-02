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

TEST_SRC_DIRS = \
	.\
	mocks\
	tests/LedDriver\
	tests\

	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  mocks\
  include/LedDriver\

MOCKS_SRC_DIRS = \
	mocks\

include ../CppUTestCompileFlags.mk

LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

