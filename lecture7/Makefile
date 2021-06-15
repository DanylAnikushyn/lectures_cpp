CXX = g++
TARGET = test
OBJS = test.o cobject.o my_unique_ptr.o my_shared_ptr.o my_weak_ptr.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

test.o: test.cpp 
	$(CXX) -c $<

%.o: %.cpp %.h
	$(CXX) -c $<

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean test