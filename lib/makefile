include ../common.mk

bindir_here := ../$(bindir)/lib
include_here := ../$(global_include_dir) ../$(global_include_dir)/lib

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

%.o: %.c
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

%.o: %.cpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

%.o: %.cpp %.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

.PHONY: all

all: glad.o stb_image.o

glad.o: glad.c
stb_image.o: stb_image.cpp stb_image.hpp
