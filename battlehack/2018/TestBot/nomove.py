import battlecode
import time
import random

#Start a game
game = battlecode.Game('nomove')

start = time.clock()

for state in game.turns():
	# Your Code will run within this loop
	for entity in state.get_entities(team=state.my_team): 
		# This line gets all the bots on your team
		pass

end = time.clock()
print('clock time: ' + str(end - start))
print('per round: ' + str((end - start) / 1000))
