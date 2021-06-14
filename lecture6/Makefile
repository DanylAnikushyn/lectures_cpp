CXX = g++
TARGET = main
OBJS = main.o sync_out_file_stream.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

main.o: main.cpp sync_out_file_stream.h
	$(CXX) -c $<

%.o: %.cpp %.h
	$(CXX) -c $<

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean test