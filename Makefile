CC = g++
CFLAGS = -std=c++11
TARGET = ESPICE
SOURCES = main.cpp Node.cpp Component.cpp Resistor.cpp DC_voltage.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)