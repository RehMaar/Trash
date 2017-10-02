CPP = g++
SYSTEMC_HOME    = /opt/systemc-2.3.1
TARGET_ARCH     = linux64

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR)
LDFLAGS         = -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = src/timer.cpp
OBJS = $(SRCS:.cpp=.o)
BIN = model
TEST_SRC = $(wildcard src/test/*.cpp)
TEST_OBJECTS = $(TEST_SRC:.cpp=.test)
WAVE = wave

all: $(BIN)

$(BIN): $(SRCS)
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

%.o: %.cpp
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

%.test: %.cpp $(SRCS)
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

compile_test: $(TEST_OBJECTS)

run:
	./$(BIN)

wave:
	gtkwave -z $(WAVE).vcd

.PHONY: wave run compile_test
