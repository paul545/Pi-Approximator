Paul Bosonetto

This program is a 'pi' approximator. Using fork() to create multiple processes, the program
simulates throwing darts at a square. We simulate the idea that there is a maximally sized circle
inside this square, and count how many darts 'hit' this circle. This should approximate to 3.14 
with enough repetitions.


USAGE: ./my-pi numWorkers numDartsThrown 

where numWorkers is the amount of child processes
and numDartsThrown is the number of darts you want to simulate throwing. 
