AUTOMAKE_OPTIONS=subdir-objects

AM_CPPFLAGS= -w -g -fcommon -fpermissive -no-pie
AM_LFLAGS=-lglfw -lGL

bin_PROGRAMS=wawacraft-evolved

wawacraft_evolved_CFLAGS=$(GLFW_CFLAGS)
wawacraft_evolved_LDADD=$(GLFW_LIBS) -lGL

wawacraft_evolved_SOURCES=src/glad.c src/stb_image.cpp src/main.cpp \
src/blurbs.cpp src/events.cpp src/windows-reserve.cpp src/blurbs-help-table.cpp \
src/file.cpp src/flag.cpp src/gl-handle.cpp src/logging.cpp src/manager.cpp \
src/manager-register.cpp src/node.cpp src/options.cpp src/parser.cpp \
src/reserve.cpp src/sieve.cpp src/window.cpp src/blurbs.hpp src/common.hpp \
src/events.hpp src/file.hpp src/flags.hpp src/graphics.hpp src/libs.hpp \
src/logging.hpp src/management.hpp src/options.hpp src/settings.hpp \
src/stb_image.hpp src/windows.hpp src/glad.h
