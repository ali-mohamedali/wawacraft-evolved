MKDIR=mkdir -p

<<<<<<< HEAD
CXX = x86_64-w64-mingw32-g++
=======
CXX = g++
>>>>>>> new_base
CC = gcc

LS=ls
FIND=find
GREP=grep
ECHO=echo
RM=rm

<<<<<<< HEAD
CXXFLAGS = -w -g -fcommon -fpermissive -no-pie -static-libstdc++ -static-libgcc
LFLAGS = -lopengl32 -lgdi32

global_include_paths :=
=======
CXXFLAGS = -w -g -fcommon -fpermissive -no-pie
LFLAGS = -lglfw -lGL

global_include_paths := /usr/include/GL /usr/include/GLFW /usr/lib /usr/lib64
>>>>>>> new_base

global_include_dir := include

LPATHS := $(addprefix -I,$(global_include_paths))

<<<<<<< HEAD
CXXCOMPILE := $(CXX) $(CXXFLAGS) $(LFLAGS) $(LPATHS)
=======
CXXCOMPILE := $(CXX) $(CXXFLAGS)
>>>>>>> new_base

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
<<<<<<< HEAD
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@
=======
	$(CXXCOMPILE) -c $< -o $(bindir_here)/$@ $(LPATH_HERE) $(LPATHS) $(LFLAGS)
>>>>>>> new_base
