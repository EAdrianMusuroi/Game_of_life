import random
import sys

# first argument is the number of lines/columns
if len(sys.argv) < 2:
	print("Too few arguments")
	exit()

size = sys.argv[1]
file = open("input_size_" + str(size), "w+")

for i in range(int(size) * int(size)):
	file.write(str(random.randint(0,1)))

file.close()