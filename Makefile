# Declaratiile de variabile
CC = gcc
CFLAGS =   -g -lm -lcurses -Wall #-Werror -Wextra -Wswitch-default -Wswitch-enum -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn 
RUNFLAGS = arg1.in arg2.in arg3.in
NUME=battleship
build:

	$(CC) -o $(NUME) $(NUME).c $(CFLAGS)

run:

	./$(NUME) $(RUNFLAGS)

clean:

	rm -f $(NUME)


