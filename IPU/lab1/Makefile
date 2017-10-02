CPP = g++
SYSTEMC_INCLUDE    = /usr/include/systemc
TARGET_ARCH     = linux64


FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive
LDFLAGS         = -lsystemc -lm

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

run_test:
	$(foreach var,$(TEST_OBJECTS), ./$(var); )

run:
	./$(BIN)

wave:
	gtkwave -z $(WAVE).vcd

.PHONY: wave run compile_test run_test
