EXEC = dminion
CC = g++ -O
LDFLAGS = -g
INCLUDES = -ISDL
LIBS = -lSDL

CFILES = \
  const.cc \
  main.cc \
  context.cc \
  display.cc \
  settings.cc \

HEADERS = \
  player.h \
  context.h \
  display.h \
  settings.h \
  types.h \
  const.h \

all: dminionbin

dminionbin: $(CFILES) $(HEADERS)
	$(CC) $(LDFLAGS) -o dminion $^ $(LIBS) $(INCLUDES)
