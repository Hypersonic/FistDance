# Platform identifier
MACHINE = $(shell uname -s)
# Our source, so we can include relative to src/
INCLUDES = -Isrc/
# Directories inside src that we should look in for compilation
DIRS = 
# Object files, by keeping the directory structure from src/ in obj/
OBJS = $(patsubst src/core/%.cpp,obj/core/%.o, $(wildcard src/core/*.cpp) $(foreach d, $(DIRS), $(wildcard src/core/$(d)/*.cpp)))
# Dependency files, used to automatically recompile a source if a header it depends on changes
DEPS = $(OBJS:.o=.d)

# Our compiler
CXX = clang++
# initialize $PLATFORM_LIBS to blank so the platform-specfic section can fill it in later
PLATFORM_LIBS = 
# Warnings
WARNINGS = -Wall -Wextra
# compiler features
FEATURES =
CFLAGS = -w -lSDL2 -lSDL2_ttf -O -stdlib=libc++ -std=gnu++11 -g -march=native $(WARNINGS) $(FEATURES)

# Handle platform-specific setup
ifeq ($(MACHINE), Darwin)
	CXX = clang++
	PLATFORM_FLAGS = -mmacosx-version-min=10.7
	PLATFORM_LIBS =
endif

# The libs we build with should be our platform libs plus whatver platform-independent libs we want
LIBS = $(PLATFORM_LIBS)
# Same with the flags
FLAGS = $(PLATFORM_FLAGS) $(CFLAGS)

# The name of our executable
EXEC = FistDance_$(MACHINE).out
CORE_LIB = FistDance_core.dylib

# Link into an executable
# UNIX FORM:
unix: dirs $(OBJS) core
	$(CXX) $(FLAGS) -o $(EXEC) $(LIBS) src/unix.cpp

core: dirs $(OBJS)
	$(CXX) -dynamiclib $(FLAGS) -o $(CORE_LIB) $(OBJS) $(LIBS)

# Compile for each thing
obj/%.o: src/%.cpp
	$(CXX) $(FLAGS) -c -MMD -MP $< -o $@ $(INCLUDES)

# Create empty dirs if they don't exist
dirs:
	@test -d obj || mkdir obj
	@test -d obj/core || mkdir obj/core
	@for DIRECTORY in $(DIRS) ; do \
		test -d obj/core/$$DIRECTORY || mkdir obj/core/$$DIRECTORY; \
	done

clean:
	rm -f $(EXEC) $(OBJS) $(DEPS) $(CORE_LIB)

# Run
# TODO: Make the dependency for this be the platform the user is on
run: unix
	./$(EXEC)

-include $(DEPS)
