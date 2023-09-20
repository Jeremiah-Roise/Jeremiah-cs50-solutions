#!/usr/bin/python3
from cs50 import get_int
# sanatize user input.
while True:
    height = get_int("Height: ")
    if height != None:
        if height > 0 and height < 9:
            break

# print the pyramid
for i in range(1, height + 1):
    # print padding for the pyramid.
    print(' '*(height - i), end='')
    print('#'*i + "  " + '#'*i)
