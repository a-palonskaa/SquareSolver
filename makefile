CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=buffer_clean.cpp get_data.cpp main.cpp show_results.cpp solve_quadr.cpp compare_double.cpp test_solve_quadr.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=square

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
