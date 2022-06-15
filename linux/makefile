# Android will not build here

CC=g++-9
ACC=arm-linux-gnueabi-g++-9

SRCDIR=src
TSTDIR=test
DBGDIR=debug
RELDIR=release
ANDDIR=android
MACDIR=macos
LIBDIR=$(SRCDIR)/lib
INCDIR=$(SRCDIR)/include

BIN=colorstatic

SRCNAM=main
SRCEXT=cpp
SRC=$(SRCNAM).$(SRCEXT)
SRCPTH=$(SRCDIR)/$(SRC)

TSTPTH=$(TSTDIR)/$(BIN)
DBGPTH=$(DBGDIR)/$(BIN)
DBGPTHSTATIC=$(DBGDIR)/$(BIN).static
RELPTH=$(RELDIR)/$(BIN)
RELPTHSTATIC=$(RELDIR)/$(BIN).static
ANDPTH=$(ANDDIR)/$(BIN).arm

CF_STATIC=-static -static-libgcc -static-libstdc++

CF_DBG=-g -Wall -Wextra -fsanitize=leak -fsanitize=address -std=c++17 -pthread 
CF_DBG_STATIC=-g -Wall -Wextra $(CF_STATIC) -std=c++17
CF_REL=-O3 -std=c++17 -pthread 
CF_REL_STATIC=-O2 $(CF_STATIC) -std=c++17 -pthread 
CF_AND=$(CF_REL_STATIC) -march=armv8-a -pthread 

TSTARG=--help

$(SRCNAM): $(SRCPTH)
	mkdir -p $(RELDIR)
	$(CC) $(CF_REL) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(RELPTH)

debug:
	mkdir -p $(DBGDIR)
	$(CC) $(CF_DBG) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(DBGPTH)

android: $(SRCPTH)
	mkdir -p $(ANDDIR)
	$(ACC) $(CF_AND) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(ANDPTH)

test:
	mkdir -p $(TSTDIR)
	$(CC) $(CF_DBG) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(TSTPTH)
	./$(TSTPTH) $(TSTARG)

install: $(SRCNAM)
	cp -f "$(RELPTH)" "/usr/bin/$(BIN)"

clean:
	rm -rf $(RELDIR)
	rm -rf $(TSTDIR)
	rm -rf $(DBGDIR)
	rm -rf $(ANDDIR)
