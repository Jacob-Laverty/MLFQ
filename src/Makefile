CC = gcc
CFLAGS = -Wall -g

IDIR = ./include
INCLUDES = -I$(IDIR)

SRCS = simulation.c

OBJDIR=./obj
OBJECTS = $(OBJDIR)/$(SRCS:.c=.o)


MAIN = simulation

install: $(MAIN)
	@echo Simulation compiled

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) 

$(OBJDIR)/%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJDIR)/*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
