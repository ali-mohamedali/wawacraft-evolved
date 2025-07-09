include ../../common.mk

bindir_here := ../../$(bindir)/graphics
include_here := ../../$(global_include_dir) ../../$(global_include_dir)/graphics

VPATH = $(include_here):$(bindir_here)

LPATH_HERE = $(addprefix -I,$(include_here))

.PHONY: all

all: reserve.o gl_handle.o

reserve.o: reserve.cpp graphics.hpp
gl_handle.o: gl_handle.cpp graphics.hpp reserve.o
