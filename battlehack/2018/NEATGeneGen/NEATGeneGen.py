import random
file = open('genes.txt', 'w')

file.write('genomestart 1\n')
file.write('trait 1 0.1 0 0 0 0 0 0 0\n')
file.write('node 1 0 1 3\n')

for a in range(84):
	file.write('node ' + str(a+2) + ' 0 1 1\n')
for a in range(34):
	file.write('node ' + str(a+86) + ' 0 0 2\n')
for a in range(85):
	for b in range(34):
		if random.randint (0, 100) % 100 < 25:
			file.write('gene 1 ' + str(a+1) + ' ' + str(b+86) + ' 0.0 0 ' + str(a*34+b) + ' 0 1\n')

file.write('genomeend 1\n')

file.close()