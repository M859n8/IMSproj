TARGET = model

CXX = g++
CXXFLAGS = -g -O2
LDFLAGS = -lsimlib -lm

SRCS = model.cc

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)
run: 
	make clean
	make
	./$(TARGET) summer
