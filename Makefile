PROJECT := ga

BINDIR := bin
OBJDIR := obj
SRCDIR := src

BINARY := $(BINDIR)/$(PROJECT)

CXXSTD := -std=c++14
WARNINGS := -Wall -Werror -Wextra
DEBUG := -g -DDEBUG
CXX += $(CXXSTD) $(WARNINGS) $(DEBUG)

SOURCES := $(shell find src -name '**.cc')
OBJECTS := $(shell echo $(SOURCES:.cc=.o) | sed 's/src/obj/g')

all: $(BINARY)

$(BINARY): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $^ -o $@

$(OBJECTS): $(OBJDIR)%.o: $(SRCDIR)/%.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $< -c -o $@

run:
	./bin/ga
	
clean:
	rm -rfv $(BINDIR) $(OBJDRI)
