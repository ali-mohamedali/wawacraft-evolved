include ../common.mk

bindir_here := ../$(bindir)
include_here := ../$(global_include_dir) ../$(global_include_dir)/$(libdir)

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

%.o: %.cpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

%.o: %.cpp %.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

.PHONY: all program

all: main.o program

main.o: main.cpp program

program:
	$(MKDIR) $(bindir_here)/program
	$(MAKE) -C program
