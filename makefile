MACHINE = $(shell uname -s)
INCLUDES = -Isrc/
DIRS = 
OBJS = $(patsubst src/%.c,obj/%.o, $(wildcard src/*.c) $(foreach d, $(DIRS), $(wildcard src/$(d)/*.c)))

CXX = g++
PLATFORM_LIBS = 
WARNINGS = -Wall -Wextra
FEATURES = 
CFLAGS = -std=c11 -O -g -march=native $(WARNINGS) $(FEATURES)

ifeq ($(MACHINE), Darwin)
	CXX = clang
	PLATFORM_LIBS = 
endif

LIBS = $(PLATFORM_LIBS)
EXEC = FistDance_$(MACHINE).out

main: dirs $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

obj/%.o: src/%.c
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCLUDES)

dirs:
	@test -d obj || mkdir obj
	@for DIRECTORY in $(DIRS) ; do \
		test -d obj/$$DIRECTORY || mkdir obj/$$DIRECTORY; \
	done

clean:
	rm -f $(EXEC) $(OBJS)

run: main
	$(EXEC)
