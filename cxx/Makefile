SHELL     = /bin/bash
CXX_FLAGS = -std=c++17 -Wall -Wextra -O3 -I $(shell pwd)
CXX_DIRS  = utils
CXX_FILES = $(notdir $(wildcard $(patsubst %,%/*.cxx,$(CXX_DIRS))))
OBJ_FILES = $(patsubst %.cxx,bin/%.o,$(CXX_FILES))


all: $(OBJ_FILES)

bin/%.o: */%.cxx
	@g++ $(CXX_FLAGS) -c -o $@ $<

test: dummy
	@for FILE in test/*.cxx; do \
		EXE=bin/test.exe; \
		rm -f $EXE; \
		g++ $(CXX_FLAGS) -o $$EXE $$FILE $(OBJ_FILES); \
		$$EXE; \
		rm $$EXE; \
	done

clean: dummy
	@rm -f bin/*

refresh: clean all

dummy:
