CXX = clang++
FLAGS = -std=c++11 -stdlib=libstdc++ -Wall -pedantic -Werror
LDLIBS=-lstdc++
# LFLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
OBJS = main.o game_state_manager.o
PROG = game

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
%.o: src/%.cpp
	$(CXX) $(FLAGS) -c $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(PROG) $(LDLIBS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm $(PROG) *.o
