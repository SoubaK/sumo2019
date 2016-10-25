import pickle

pack = pickle.load(open("waypointsg.txt", "r"))

waypoints = pack[1]

a = waypoints[:1]
b = waypoints[1:]

waypoints = a + [(1000, 950, 1, 0)] + b

#waypoints[3] = (600, 1600, 1, 0)

pack[1] = waypoints
pickle.dump(pack, open("waypointsg.txt", "w"))