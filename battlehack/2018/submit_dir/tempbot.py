import battlecode
import time
import random

#Start a game
game = battlecode.Game('tempbot')

start = time.clock()

# node values
val = [0.0] * 85

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

		if entity.held_by != None:
			entity.queue_disintegrate()
		if entity.can_act:
			for a in range(67,83,2):
				if val[a + 1] == 0 and (val[a] == 0 or val[a] == -1):
					loc = entity.location.adjacent_location_in_direction(dirlist[(a - 67)//2])
					if entity.can_build(dirlist[(a - 67)//2]) and state.map.sector_at(loc).team != state.my_team:
						entity.queue_build(dirlist[(a - 67)//2])
		if entity.can_act:
			for a in range(8):
				loc = entity.location.adjacent_location_in_direction(dirlist[a])
				entloc = EntityAtLoc(state, loc)
				if entloc != None and entity.can_pickup(entloc):
					entity.queue_pickup(entloc)

		closestdist = 1000
		closest = None
		for stuff in state.get_entities(team=state.other_team):
			if entity.location.adjacent_distance_to(stuff.location) < closestdist:
				closestdist = entity.location.adjacent_distance_to(stuff.location)
				closest = stuff
		if entity.can_act and entity.is_holding:
			if closest != None and entity.location != closest.location and entity.can_throw(entity.location.direction_to(closest.location)):
				entity.queue_throw(entity.location.direction_to(closest.location))

		if entity.can_act:
			if closest != None and entity.location != closest.location and entity.can_move(entity.location.direction_to(closest.location)):
				entity.queue_move(entity.location.direction_to(closest.location))

end = time.clock()
print('clock time: ' + str(end - start))
print('per round: ' + str((end - start) / 1000))