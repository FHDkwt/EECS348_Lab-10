# compiler g++
CC = g++
# compiler flags
CFLAGS = -Wall -g
# output executable name
TARGET = calculator
# source files
SOURCES = main.cpp calculator.cpp
# object files
OBJECTS = $(SOURCES:.cpp=.o)
# building the program
all: $(TARGET)
# linking objects to create executable files
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
# compiling source files to objects
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# removing all generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

