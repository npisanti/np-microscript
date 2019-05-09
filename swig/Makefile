
# swig command
SWIG = swig

# default output language, see swig -h for more
LANG = lua

# which module to build
TARGET = us

# generated bindings filename
NAME = usBindings

# where to copy the generated bindings
DEST_DIR = ../src/microscript/bindings

# any extra SWIG flags per-language, etc
SWIG_FLAGS = -O -small

# path to OF headers
OF_HEADERS = ../../../../libs/openFrameworks

# path to addons
ADDON_DIR = ../../../../addons

# C & C++ flags
CFLAGS = -I$(OF_HEADERS) -I$(ADDON_DIR) -I$(DEST_DIR) -DSWIG_NOINCLUDE

# no attribute by default, build with make ATTRIBUTES=true
ifeq ($(ATTRIBUTES), true)
	CFLAGS += -DATTRIBUTES
endif

.PHONY: all bindings symbols clean us-prepare us lfo

all: us lfo

# generates bindings
bindings:
	@echo "### Generating $(TARGET)"
	@mkdir -p $(DEST_DIR)
	$(SWIG) -c++ -$(LANG) $(SWIG_FLAGS) $(CFLAGS) -o $(DEST_DIR)/$(NAME).cpp $(TARGET).i

# outputs debug symbols
symbols:
	$(SWIG) -c++ -$(LANG) -debug-lsymbols $(CFLAGS) $(TARGET).i > $(TARGET)_symbols.txt
	rm -f *.cxx

# clean up
clean:
	rm -f $(DEST_DIR)/*Bindings.cpp
	rm -f *_symbols.txt

# us bindings
us-prepare:
	$(eval TARGET := us)
	$(eval NAME := usBindings)

us: us-prepare bindings

# lfo bindings
lfo-prepare:
	$(eval TARGET := lfo)
	$(eval NAME := lfoBindings)

lfo: lfo-prepare bindings
