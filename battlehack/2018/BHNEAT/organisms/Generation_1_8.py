edge = [(74,94,0.280770287179174)]
orgname='BHNEAT_1_8'
cnodes = 119

import battlecode
import time
import random
import queue

#Start a game
game = battlecode.Game(orgname)

start = time.clock()

# convert to edge list
edgel = [[]] * cnodes
indeg = [0] * cnodes
for a in range(len(edge)):
	edgel[edge[a][0]].append((edge[a][1], edge[a][2]))
	indeg[edge[a][1]] += 1

# establish update order
q = []
qtop = 0
curindeg = indeg.copy ()
for a in range(cnodes):
	if curindeg[a] == 0:
		q.append(a)
while qtop != len(q):
	node = q[qtop]
	qtop += 1
	for a in range(len(edgel[node])):
		curindeg[edgel[node][a][0]] -= 1
		if curindeg[edgel[node][a][0]] == 0:
			q.append(edgel[node][a][0])

# node values
val = [0.0] * cnodes

dirlist = battlecode.Direction.directions()

def EntityAtLoc(state, loc):
	entlist = state.get_entities()
	for entity in entlist:
		if entity.location.distance_to(loc) <= 0.05:
			return entity
	return None

for state in game.turns():
	# Your Code will run within this loop
	for entity in state.get_entities(team=state.my_team): 
		# This line gets all the bots on your team

		# input 1 bias node and 84 feature nodes
		val[0] = 1.0
		val[1] = float(entity.hp)
		if entity.holding == None:
			val[2] = 0.0
		elif entity.holding.team == state.my_team:
			val[2] = 1.0
		elif entity.holding.team == state.other_team:
			val[2] = -1.0
		else:
			val[2] = 0.0
		for a in range(len(dirlist)): # 3-34
			thisloc = entity.location.adjacent_location_in_direction(dirlist[a])
			pre = 3 + a * 4

			if not state.map.location_on_map(thisloc):
				val[pre + 0] = 0.0
			elif state.map.tile_at(thisloc) == 'G':
				val[pre + 0] = 1.0
			elif state.map.tile_at(thisloc) == 'D':
				val[pre + 0] = -1.0
			else:
				val[pre + 0] = 0.0

			if not state.map.location_on_map(thisloc):
				val[pre + 1] = 0.0
			locent = EntityAtLoc(state, thisloc)
			if locent == None:
				val[pre + 1] = 0.0
			elif locent.team == state.my_team and locent.is_thrower:
				val[pre + 1] = 1.0
			elif locent.team == state.other_team and locent.is_thrower:
				val[pre + 1] = -1.0
			else:
				val[pre + 1] = 0.0

			if not state.map.location_on_map(thisloc):
				val[pre + 2] = 0.0
			locent = EntityAtLoc(state, thisloc)
			if locent == None:
				val[pre + 2] = 0.0
			elif locent.team == state.my_team and locent.is_statue:
				val[pre + 2] = 1.0
			elif locent.team == state.other_team and locent.is_statue:
				val[pre + 2] = -1.0
			else:
				val[pre + 2] = 0.0

			if not state.map.location_on_map(thisloc):
				val[pre + 3] = 1.0
			else:
				val[pre + 3] = 0.0
		for a in range(len(dirlist)): # 35-66
			pre = 35 + a * 4
			thisloc = entity.location
			val[pre+3] = 0.0
			for b in range(7):
				thisloc = thisloc.adjacent_location_in_direction(dirlist[a])
				if not state.map.location_on_map(thisloc):
					val[pre + 0] = 0.0
					val[pre + 1] = 0.0
					val[pre + 2] = 0.0
					val[pre + 3] = 1.0
					break
				entloc = EntityAtLoc(state, thisloc)
				if entloc != None:
					break
			if not state.map.location_on_map(thisloc):
				pass
			else:
				entloc = EntityAtLoc(state, thisloc)
				if entloc == None:
					val[pre + 1] = 0.0
					val[pre + 2] = 0.0
					if state.map.tile_at(thisloc) == 'G':
						val[pre + 0] = 1.0
					elif state.map.tile_at(thisloc) == 'D':
						val[pre + 0] = -1.0
					else:
						val[pre + 0] = 0.0
				else:
					val[pre + 0] = 0.0
					if entloc.team == state.my_team and entloc.is_thrower:
						val[pre + 1] = 1.0
					elif entloc.team == state.other_team and entloc.is_thrower:
						val[pre + 1] = -1.0
					else:
						val[pre + 1] = 0.0
					if entloc.team == state.my_team and entloc.is_statue:
						val[pre + 2] = 1.0
					elif entloc.team == state.other_team and entloc.is_statue:
						val[pre + 2] = -1.0
					else:
						val[pre + 2] = 0.0
		for a in range(len(dirlist)): # 67-82
			pre = 66 + a * 2
			thisloc = entity.location.adjacent_location_in_direction(dirlist[a])
			if not state.map.location_on_map(thisloc):
				val[pre + 0] = 0.0
				val[pre + 1] = 1.0
			else:
				val[pre + 1] = 0.0
				sector = state.map.sector_at(thisloc)
				if sector.team == state.my_team:
					val[pre + 0] = 1.0
				elif sector.team == state.other_team:
					val[pre + 0] = -1.0
				else:
					val[pre + 0] = 0.0
		val[83] = 0.0
		val[84] = 0.0
		
		# bfs propagate on all nodes

		for a in range(len(q)):
			for b in range(len(edgel[q[a]])):
				val[edgel[q[a]][b][0]] += val[q[a]] * edgel[q[a]][b][1]
					
		# get corresponding max of 34 output nodes
		maxout = val[85]
		maxoutid = 85
		for a in range(85, 119):
			if val[a] > maxout:
				maxout = val[a]
				maxoutid = a

		outval = []
		for a in range(85, 119):
			outval.append((val[a],a))
		stout = sorted(outval, key=lambda curval: curval[0], reverse=True)

		for a in range(len(stout)):
			maxoutid = stout[a][1]
			maxoutid -= 85
			if maxoutid == 0:
				break # do nothing
			elif maxoutid == 1:
				entity.queue_disintegrate()
				break
			elif maxoutid >= 2 and maxoutid <= 9 and entity.can_move(dirlist[maxoutid - 2]):
				entity.queue_move(dirlist[maxoutid - 2])
				break
			elif maxoutid >= 10 and maxoutid <= 17:
				entloc = EntityAtLoc(state, entity.location.adjacent_location_in_direction(dirlist[maxoutid - 10]))
				if entloc != None and entity.can_pickup(entloc):
					entity.queue_pickup(entloc)
					break
			elif maxoutid >= 18 and maxoutid <= 25 and entity.can_throw(dirlist[maxoutid - 18]):
				entity.queue_throw(dirlist[maxoutid - 18])
				break
			elif maxoutid >= 26 and maxoutid <= 33 and entity.can_build(dirlist[maxoutid - 26]):
				entity.queue_build(dirlist[maxoutid - 26])
				break
			else:
				pass

end = time.clock()
# print('clock time: ' + str(end - start))
# print('per round: ' + str((end - start) / 1000))
count = 0
for entity in state.get_entities(team=state.my_team):
	count += 1

file = open('result\\' + orgname + '.txt', 'w')
file.write(str(count - 1))
file.close()