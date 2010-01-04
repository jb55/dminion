EXEC = dminion
CC = g++ -O
LDFLAGS = -g
INCLUDES = -ISDL
LIBS = -lSDL

dminion: main.cc
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) $(INCLUDES)
