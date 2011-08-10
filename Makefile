#---------
#
# LED Driver Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
#	SILENCE = 
endif

#--- Inputs ----#
#COMPONENT_NAME = CppUTestExamples
COMPONENT_NAME = LedDriver

ifndef CPPUTEST_HOME
	CPPUTEST_HOME = /Users/papabear/Sandbox/cUnitTesting/CppUTest
endif

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
#CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h

SRC_DIRS = \
	src

TEST_SRC_DIRS = \
	test

INCLUDE_DIRS =\
  .\
  include \
  $(CPPUTEST_HOME)/include\

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
