MKDIR=mkdir -p

CXX = x86_64-w64-mingw32-g++
CC = gcc

LS=ls
FIND=find
GREP=grep
ECHO=echo
RM=rm

CXXFLAGS = -w -g -fcommon -fpermissive -no-pie -static-libstdc++ -static-libgcc
LFLAGS = -lopengl32 -lgdi32

global_include_paths :=

global_include_dir := include

LPATHS := $(addprefix -I,$(global_include_paths))

CXXCOMPILE := $(CXX) $(CXXFLAGS) $(LFLAGS) $(LPATHS)

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
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@
