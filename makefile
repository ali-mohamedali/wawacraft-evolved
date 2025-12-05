include common.mk

.PHONY: all src lib clean

TARGET = wawacraft-evolved

all: lib src
	$(MKDIR) $(outdir)
	$(CXXCOMPILE) $(OBJS) -o $(outdir)/$(TARGET) $(LFLAGS)

src: lib
	$(MAKE) -C src

lib:
	$(MKDIR) $(bindir)/lib $(global_include_dir)/lib
	$(MAKE) all -C $(libdir)

run_target:
	$(outdir)/$(TARGET)

clean:
	$(RM) -rf $$($(FIND) $(bindir) -name '*.o')
