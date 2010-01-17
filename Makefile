EXEC = dminion
CC = g++
CFLAGS = -g
OPT = -O3
INCLUDES = -ISDL
LIBS = -lSDL -lSDL_ttf
OBJDIR = obj
SRCDIR = .

OBJS= \
  $(OBJDIR)/main.o \
  $(OBJDIR)/settings.o \
  $(OBJDIR)/const.o \
  $(OBJDIR)/display.o \
  $(OBJDIR)/platform.o \
  $(OBJDIR)/dminion.o \
  $(OBJDIR)/font.o \
  $(OBJDIR)/util.o \
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
	$(CC) $(CFLAGS) -c -o $@ $?

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) $(OPT) -c -o $@ $?
