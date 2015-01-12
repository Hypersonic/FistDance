# Platform identifier
MACHINE = $(shell uname -s)
# Our source, so we can include relative to src/
INCLUDES = -Isrc/
# Directories inside src that we should look in for compilation
DIRS = 
# Object files, by keeping the directory structure from src/ in obj/
OBJS = $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp) $(foreach d, $(DIRS), $(wildcard src/$(d)/*.cpp)))

# Our compiler
CXX = g++
# initialize $PLATFORM_LIBS to blank so the platform-specfic section can fill it in later
PLATFORM_LIBS = 
# Warnings
WARNINGS = -Wall -Wextra
# compiler features
FEATURES =
CFLAGS = -O -g -march=native $(WARNINGS) $(FEATURES)

# Handle platform-specific setup
ifeq ($(MACHINE), Darwin)
	CXX = clang++
	PLATFORM_LIBS = 
endif

# The libs we build with should be our platform libs plus whatver platform-independent libs we want
LIBS = $(PLATFORM_LIBS)

# The name of our executable
EXEC = FistDance_$(MACHINE).out

# Link into an executable
main: dirs $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Compile for each thing
obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Create empty dirs if they don't exist
dirs:
	@test -d obj || mkdir obj
	@for DIRECTORY in $(DIRS) ; do \
		test -d obj/$$DIRECTORY || mkdir obj/$$DIRECTORY; \
	done

clean:
	rm -f $(EXEC) $(OBJS)

# Compile & Run
run: $(EXEC)
	./$(EXEC)
