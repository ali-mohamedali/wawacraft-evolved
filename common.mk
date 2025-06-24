MKDIR=mkdir -p

CXX = g++
CC = gcc

LS=ls
FIND=find
GREP=grep
ECHO=echo
RM=rm

CXXFLAGS = -w -g -fcommon -fpermissive -no-pie
LFLAGS = -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl

global_include_paths := /usr/include/GL /usr/include/GLFW /usr/include/glad /usr/lib64

global_include_dir := include

LPATHS := $(addprefix -I,$(global_include_paths))

CXXCOMPILE := $(CXX) $(CXXFLAGS) $(LFLAGS) $(LPATHS)

OBJS := $$($(FIND) $(bindir) -name '*.o')

srcdir := src
libdir := lib
bindir := bin

outdir := $(bindir)/output

shddir := shd
texdir := tex
