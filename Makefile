EXEC = dminion
CC = g++ -O
LDFLAGS = -g
INCLUDES = -ISDL
LIBS = -lSDL

CFILES = \
  const.cc \
  main.cc \
  dminion.cc \
  display.cc \
  settings.cc \
  platform.cc \

HEADERS = \
  player.h \
  dminion.h \
  display.h \
  settings.h \
  types.h \
  const.h \
  platform.h \

all: dminionbin

dminionbin: $(CFILES) $(HEADERS)
	$(CC) $(LDFLAGS) -o $(EXEC) $^ $(LIBS) $(INCLUDES)
