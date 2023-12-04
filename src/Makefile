CXX = g++
CXXFLAGS = -std=c++17 -g -O2 -pedantic -Wall -Wextra

OBJS = main.o grid.o ward.o
DEPS = grid.hpp ward.hpp
EXEC = ca_simulation

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
