include ../common.mk

bindir_here := ../$(bindir)
include_here := ../$(global_include_dir) ../$(global_include_dir)/$(libdir)

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

SUBDIRS = program gui graphics

.PHONY: all $(SUBDIRS)

all: main.o options.o blurbs.o $(SUBDIRS)

main.o: main.cpp options.o blurbs.o
options.o: options.cpp options.hpp blurbs.o
blurbs.o: blurbs.cpp blurbs.hpp common.hpp

program:
	$(MKDIR) $(bindir_here)/program
	$(MAKE) -C program

gui: program
	$(MKDIR) $(bindir_here)/gui
	$(MAKE) -C gui

graphics: gui program
	$(MKDIR) $(bindir_here)/graphics
	$(MAKE) -C graphics
