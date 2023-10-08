CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g
EXECUTABLE = Mines
            
$(EXECUTABLE): Sweep.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) Sweep.c
      
clean:
	rm -f $(EXECUTABLE)	