CXX = g++
TARGET = test
OBJS = test.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

test.o: test.cpp vector.h vector.tpp
	$(CXX) -c $<

clean:
	rm -rf $(OBJS) $(TARGET)

v: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: all clean test