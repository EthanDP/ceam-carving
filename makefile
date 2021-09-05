CC = gcc

SRCDIR = ./src
OBJDIR = obj
INCLUDE = ./src/include

SRCS = $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*.c)

_DEPS = $(wildcard $(INCLUDE)/*.h)
DEPS = $(patsubst %,$(IDIR)/%.h,$(_DEPS))

OBJS = $(patsubst $(SRCDIR)/*/%.c $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

CFLAGS = -I$(INCLUDE)

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLUDE)/*~ 