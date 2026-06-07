include ../../common.mk

bindir_here := ../../$(bindir)/program
include_here := ../../$(global_include_dir) ../../$(global_include_dir)/program

VPATH = $(include_here):$(bindir_here)

LPATH_HERE := $(addprefix -I,$(include_here))

.PHONY: all

all: parser.o flag.o sieve.o logging.o

flag.o: flag.cpp flags.hpp settings.hpp
parser.o: parser.cpp flags.hpp logging.hpp settings.hpp
sieve.o: sieve.cpp flags.hpp logging.hpp
logging.o: logging.cpp logging.hpp common.hpp
