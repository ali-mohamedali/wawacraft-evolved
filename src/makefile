include ../common.mk

bindir_here := ../$(bindir)
include_here := ../$(global_include_dir) ../$(global_include_dir)/$(libdir)

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

.PHONY: all program

all: main.o options.o blurbs.o program

main.o: main.cpp options.o blurbs.o
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

options.o: options.cpp options.hpp blurbs.o
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

blurbs.o: blurbs.cpp blurbs.hpp common.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

program:
	$(MKDIR) $(bindir_here)/program
	$(MAKE) -C program
