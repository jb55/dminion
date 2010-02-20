EXEC = dminion
CC = g++
DEF = 
BOOST = $(HOME)/dev/boost_1_42_0
CFLAGS = -Wall -g $(DEF)
OPT = -O2
INCLUDES = -ISDL -I$(BOOST)
LIBS = -lSDL -lSDL_ttf -lSDL_image -lyaml-cpp
OBJDIR = obj
SRCDIR = src

OBJS= \
  $(OBJDIR)/main.o \
  $(OBJDIR)/settings.o \
  $(OBJDIR)/const.o \
  $(OBJDIR)/display.o \
  $(OBJDIR)/platform.o \
  $(OBJDIR)/dminion.o \
  $(OBJDIR)/font.o \
  $(OBJDIR)/util.o \
  $(OBJDIR)/log.o \
  $(OBJDIR)/card.o \
  $(OBJDIR)/gamecard.o \
  $(OBJDIR)/context.o \
  $(OBJDIR)/resource.o

DBGOBJS= \
  $(OBJDIR)/main.dbg.o \
  $(OBJDIR)/settings.dbg.o \
  $(OBJDIR)/const.dbg.o \
  $(OBJDIR)/display.dbg.o \
  $(OBJDIR)/platform.dbg.o \
  $(OBJDIR)/dminion.dbg.o \
  $(OBJDIR)/font.dbg.o \
  $(OBJDIR)/util.dbg.o \
  $(OBJDIR)/log.dbg.o \
  $(OBJDIR)/card.dbg.o \
  $(OBJDIR)/gamecard.dbg.o \
  $(OBJDIR)/context.dbg.o \
  $(OBJDIR)/resource.dbg.o

all: debug

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXEC) $(DBGEXEC)

release: $(OBJS)
	$(CC) $(OPT) -o $(EXEC) $^ $(LIBS) $(INCLUDES)
	
debug: $(DBGOBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $^ $(LIBS) $(INCLUDES)

$(OBJDIR)/%.dbg.o: $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c -o $@ $? $(INCLUDES)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) $(OPT) -c -o $@ $? $(INCLUDES)
