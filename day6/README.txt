IMPORTANT: The program for part 2 IS INCOMPLETE!!
To me, there are 2 cases where the guard is 'looped'
1: The guard is stuck in a loop in which they retrace their steps completely
    (i.e no. of places visited == no. of places revisited)
2: The guard hasn't completely retraced their steps, but are stuck in a loop in a seperate area of the map
    -> guard has moved more times CONSECUTIVELY then the places they have revisited
    (i.e no. of consecutive moves(without making progress) > no. of places revisited)

I've implemented both of these checks within the program, in the method 'is_looped'
For my problem, it keeps returning 1840, and this is apparently too low and im stumped on what to do,
so im progressing for now. I'll come back to this should God will. 



ALSO in day6_P2.py

I've imported the rich library into my code for my own sanity
If you don't want to install it, just remove the import statement at the top,
and in main, replace

for x, row in track(enumerate(contents), description="Progress="):

with

for x, row in enumerate(contents):