CPP = g++
SYSTEMC_INCLUDE    = /usr/include/systemc
TARGET_ARCH     = linux64


FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive
LDFLAGS         = -lsystemc -lm

SRC_PATH  = src
TEST_PATH = src/test
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
BIN = model
TEST_SRC =  $(wildcard src/test/*.cpp)
TEST_OBJECTS = $(TEST_SRC:.cpp=.test)
WAVE = wave

all: $(BIN)

$(BIN): $(SRCS)
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

%.o: %.cpp
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

run:
	./$(BIN)

test_timer.test: $(TEST_PATH)/test_timer.cpp $(SRC_PATH)/timer.cpp
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc
	
test_oc.test: $(TEST_PATH)/test_oc.cpp $(SRC_PATH)/timer.cpp $(SRC_PATH)/output_compare.cpp
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

test_bus.test: $(TEST_PATH)/test_bus.cpp $(SRCS)
	$(CPP) -o $@ $(LDFLAGS) $(FLAGS) $^ -Isrc

compile_test: test_timer.test test_oc.test test_bus.test

test_timer: test_timer.test
	./$^
	gtkwave wave_timer.vcd config_timer.gtkw;
	
test_oc: test_oc.test
	./$^
	gtkwave wave_oc.vcd config_oc.gtkw;

test_bus: test_bus.test
	./$^
	gtkwave wave_bus.vcd config_bus.gtkw;

clean:
	rm $(TEST_PATH)/*.test
	rm $(BIN)

report:
	pdflatex report/report.tex --output-directory=report
	
.PHONY: wave run compile_test test_timer test_oc clean report
