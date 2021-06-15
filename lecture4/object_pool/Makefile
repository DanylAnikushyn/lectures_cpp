CXX = g++
TARGET = main
OBJS = main.o object_pool.o object.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

main.o: main.cpp
	$(CXX) -c $<

%.o: %.cpp %.h
	$(CXX) -c $<

clean:
	rm -rf $(OBJS) $(TARGET)

test: $(TARGET)
	./$(TARGET) 

v: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: all clean test