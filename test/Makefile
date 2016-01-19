LOCAL_CVS_ROOT=../..

MAC_BIT := $(shell /usr/bin/getconf LONG_BIT)
ifeq ($(MAC_BIT),64)
	LIB2_DIR=$(LOCAL_CVS_ROOT)/lib2-64
	THIRD_DIR=$(LOCAL_CVS_ROOT)/third-64
else
	LIB2_DIR=$(LOCAL_CVS_ROOT)/lib2
	THIRD_DIR=$(LOCAL_CVS_ROOT)/third
endif
BTEST_BASE := $(THIRD_DIR)/btest

CXXFLAGS=-fPIC -g -finline-functions -Wall -W -Winline -pipe -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Werror -Wno-unused-parameter -D_GNU_SOURCE -Wno-deprecated 
CFLAGS=$(CXXFLAGS)
INCPATH= -I.. -I$(LOCAL_CVS_ROOT)/com/btest/gtest/output/include -I.
DEP_LDFLAGS= -L.. -L$(LOCAL_CVS_ROOT)/com/btest/gtest/output/lib -L.
DEP_LDLIBS= -lsvm -lgtest -lgtest_main -lpthread
CXX=g++
CC = gcc

PATTERN=test*.cpp
TESTFILES=$(wildcard $(PATTERN))
EXE=$(basename $(TESTFILES))
all : $(EXE)
$(EXE) : % : %.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CFLAGS) $(INCPATH) $(DEP_LDFLAGS) $(DEP_LDLIBS)
.PHONY: list clean
list:
	@echo $(EXE)
clean:
	rm -f $(EXE)



