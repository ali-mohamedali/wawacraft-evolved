include ../../common.mk

bindir_here := ../../$(bindir)/gui
include_here := ../../$(global_include_dir) ../../$(global_include_dir)/gui

VPATH = $(include_here):$(bindir_here)

LPATH_HERE = $(addprefix -I,$(include_here))

.PHONY: all

all: window.o reserve.o

window.o: window.cpp windows.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

reserve.o: reserve.cpp windows.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@
