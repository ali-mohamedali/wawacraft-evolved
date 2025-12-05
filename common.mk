MKDIR=mkdir -p

CXX = g++
CC = gcc

LS=ls
FIND=find
GREP=grep
ECHO=echo
RM=rm

CXXFLAGS = -w -g -fcommon -fpermissive -no-pie
LFLAGS = -lglfw -lGL

global_include_paths := /usr/include/GL /usr/include/GLFW /usr/lib /usr/lib64

global_include_dir := include

LPATHS := $(addprefix -I,$(global_include_paths))

CXXCOMPILE := $(CXX) $(CXXFLAGS)

OBJS := $$($(FIND) $(bindir) -name '*.o')

srcdir := src
libdir := lib
bindir := bin/objects

outdir := bin/output

shddir := shd
texdir := tex

bindir_here = bindir

LPATH_HERE = LPATHS

%.o: %.cpp
	$(CXXCOMPILE) -c $< -o $(bindir_here)/$@ $(LPATH_HERE) $(LPATHS) $(LFLAGS)
