include ../../common.mk

bindir_here := ../../$(bindir)/program
include_here := ../../$(global_include_dir) ../../$(global_include_dir)/program

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

.PHONY: all

all: parser.o flag.o sieve.o logging.o

flag.o: flag.cpp flags.hpp settings.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

parser.o: parser.cpp flags.hpp logging.hpp settings.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

sieve.o: sieve.cpp flags.hpp logging.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@

logging.o: logging.cpp logging.hpp common.hpp
	$(CXXCOMPILE) $(LPATH_HERE) -c $< -o $(bindir_here)/$@
