AM_CXXFLAGS= -w -g -fcommon -fpermissive -no-pie

bin_PROGRAMS=wawacraft-evolved

wawacraft_evolved_CFLAGS=$(GLFW_CFLAGS)
wawacraft_evolved_LDADD=$(GLFW_LIBS) -lGL

wawacraft_evolved_SOURCES=glad.c stb_image.cpp main.cpp \
blurbs.cpp events.cpp windows-reserve.cpp \
file.cpp flag.cpp gl_handle.cpp logging.cpp manager.cpp \
manager_register.cpp node.cpp options.cpp parser.cpp \
reserve.cpp sieve.cpp window.cpp blurbs.hpp common.hpp events.hpp \
file.hpp flags.hpp graphics.hpp libs.hpp logging.hpp \
management.hpp options.hpp settings.hpp stb_image.hpp \
windows.hpp glad.h
