CC = gcc
CFLAGS = -Wall -g

LEXC=lex
LEX = lex.yy.c

IDIR = ./include
INCLUDES = -I$(IDIR)

LANGUAGE = $(IDIR)/lang.l

SRCS = simulation.c mts.c burst.c pcb.c timer.c srtf_queue.c rr_queue.c scheduler.c cpu.c dd.c device.c print_event.c stats.c

OBJDIR=./obj
OBJECTS = $(SRCS:.c=.o)


MAIN = simulation
RULES = rules.o

install: $(MAIN)
	@mv *.o $(OBJDIR)
	@echo Simulation compiled

$(MAIN): $(RULES) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(RULES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(RULES): $(LEX) lex.yy.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(LEX): 
	$(LEXC) $(LANGUAGE)

clean:
	$(RM) $(LEX) ./*.o $(OBJDIR)/*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
