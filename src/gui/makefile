include ../../common.mk

bindir_here := ../../$(bindir)/gui
include_here := ../../$(global_include_dir) ../../$(global_include_dir)/gui

VPATH = $(include_here):$(bindir_here)

LPATH_HERE = $(addprefix -I,$(include_here))

.PHONY: all

all: window.o reserve.o node.o manager.o manager_register.o events.o

window.o: window.cpp windows.hpp reserve.o
reserve.o: reserve.cpp windows.hpp
node.o: node.cpp management.hpp window.o events.o
manager_register.o: manager_register.cpp management.hpp node.o events.o
manager.o: manager.cpp management.hpp node.o manager_register.o
events.o: events.cpp events.hpp
