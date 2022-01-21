CC=gcc
CFLAGS=--std=c17 -Wall -Wextra -Werror -pedantic -g
LD=gcc
LDFLAGS=-lm

EXEC=nuke

SRCDIR=src
INCDIR=inc
BUILDDIR=build

all: build $(EXEC)


build:
	mkdir $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $^ -o $@

$(EXEC): $(BUILDDIR)/$(EXEC).o $(BUILDDIR)/utils.o $(BUILDDIR)/cluster.o $(BUILDDIR)/points.o $(BUILDDIR)/vector.o
	$(LD) $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(BUILDDIR)
	rm -f $(EXEC)