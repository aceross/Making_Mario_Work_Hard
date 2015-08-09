# Making Mario Work Hard Makefile
# ===============================

# To stop executing under other make(1) commands
# that won't understand these lines
ifneq (,)
This makefile requires GNU Make.
endif

NO_COLOUR    =\033[0m
OK_COLOUR    =\033[32;01m
ERROR_COLOUR =\033[31;01m
WARN_COLOUR  =\033[33;01m
TASK_COLOUR  =\033[34;01m

OK_STRING     =$(OK_COLOUR)[OK]$(NO_COLOUR)
ERROR_STRING  =$(ERROR_COLOUR)[ERRORS]$(NO_COLOUR)
WARN_STRING   =$(WARN_COLOUR)[WARNINGS]$(NO_COLOUR)

AWK_CMD       = awk '{ printf "%-30s %-10s\n",$$1, $$2; }'
PRINT_ERROR   = printf "$@ $(ERROR_STRING)\n" | $(AWK_CMD) && \
                printf "$(CMD)\n$$LOG\n" && false
PRINT_WARNING = printf "$@ $(WARN_STRING)\n" | $(AWK_CMD) && \
                printf "$(CMD)\n$$LOG\n"
PRINT_OK      = printf "$@ $(OK_STRING)\n" | $(AWK_CMD)
BUILD_CMD     = LOG=$$($(CMD) 2>&1) ; if [ $$? -eq 1 ]; \
                then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; \
								then $(PRINT_WARNING); else $(PRINT_OK); fi;

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
CFLAGS   := -std=c++11 -stdlib=libstdc++ -pedantic
LIB      := -lstdc++ -lz -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
INC      := -I include

# links the *.o objects together along with the necessary libraries
$(TARGET): $(OBJECTS)
	@echo " ${TASK_COLOUR}Linking...${NO_COLOUR}"
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# makes the build directory with the *.o objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR) $(BUILDDIR)/pugixml
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
###	@$(BUILD_CMD)

clean:
	@echo "${TASK_COLOUR} Cleaning...${NO_COLOUR}"
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
