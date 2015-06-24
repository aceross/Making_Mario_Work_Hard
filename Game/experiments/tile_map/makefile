# Making Mario Work Hard Makefile
# ===============================

# To stop executing under other make(1) commands
# that won't understand these lines
ifneq (,)
This makefile requires GNU Make.
endif

# This makefile uses LLVM/Clang but can be changed easily to g++ :
# * to change to g++, change CC to g++
# * remove -lstdc++ as this is clang specific
CC       := clang++
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/game

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS   := -std=c++11 -stdlib=libstdc++ -Wall -pedantic -Werror
LIB      := -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
INC      := -I include

# links the *.o objects together along with the necessary libraries
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# makes the build directory with the *.o objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
