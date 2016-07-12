#///////////////////////////////////////////////////////////////////////////////
# <file type="public">
#
#   <description>
#     <abstract>
#       Makefile for compiling the example codes.
#     </abstract>
#   </description>
#   <license>
#     See the src/README.txt file in this distribution for copyright and license
#     information.
#   </license>
#
# </file>
#///////////////////////////////////////////////////////////////////////////////

#===============================================================================
# Edit the following lines to give the path to the source codes, to choose
# the compiler (gcc or g++), and to choose whether you will check
# executable with Valgrind:
#===============================================================================

SRCDIR = ./
GC=g++
VALGRIND=yes

#===============================================================================
# End of editing
#===============================================================================

VPATH = $(SRCDIR)

CINCLUDE= -I$(SRCDIR) 

#===============================================================================
# BINDIR is the temporary directory for code executables.
#===============================================================================

ifndef BINDIR
BINDIR = .
endif

BIN_DIR := $(shell mkdir -p $(BINDIR))

#===============================================================================
# Compiler flags.
#===============================================================================

CFLAGS1= -ansi -pedantic -Werror -Wall -W \
         -Wconversion -Wshadow \
         -Wpointer-arith -Wcast-qual -Wcast-align \
         -Wwrite-strings \
         -fshort-enums -fno-common -Dinline= -g

ifeq ($(GC), gcc)
  CFLAGS2= $(CFLAGS1) -Wmissing-prototypes -Wstrict-prototypes -Wnested-externs
else
  CFLAGS2= $(CFLAGS1)
endif

ifeq ($(VALGRIND), yes)
  CFLAGS= $(CFLAGS2) -O0
else
  CFLAGS= $(CFLAGS2) -O2
endif

#CC=$(GC) $(CFLAGS) $(CINCLUDE)
CC=$(GC) $(CINCLUDE)

#===============================================================================
# OBJDIR is the temporary directory for codes compilation, this is where
# object files are created.
#===============================================================================

OBJDIR = ../obj/

OBJ_DIR := $(shell mkdir -p $(OBJDIR))

#===============================================================================
# Objects.
#===============================================================================

OBJS =  $(OBJDIR)car.o \
	$(OBJDIR)network.o

$(OBJS): $(OBJDIR)%.o: %.cpp
	$(CC) -c -o $@ $<

#===============================================================================
# Excutables
#===============================================================================

EXEC = \
  run_network \

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/$@ $@.cpp

.PHONY all : $(EXEC)

#===============================================================================
# Clean up.
#===============================================================================

.PHONY: clean cleanall

clean: 
	rm -fr $(OBJDIR)

cleanall: clean
	rm -f $(EXEC) *.exe
