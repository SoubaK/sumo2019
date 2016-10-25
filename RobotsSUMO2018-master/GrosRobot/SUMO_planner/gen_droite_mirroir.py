import pickle

pack = pickle.load(open("waypoints" + 'g' + ".txt", "r"))
num = raw_input('>')
pickle.dump(pack, open("waypoints" + num + 'g' + ".txt", "w"))

waypoints = pack[1]


for i in range(0,len(waypoints)):
    
    (x,y,m,f) = waypoints[i]
    x = 3000 - x
    waypoints[i] = (x,y,m,f)
     
pack[1] = waypoints
pack[0] = 'd'
pickle.dump(pack, open("waypoints" + num + 'd' + ".txt", "w"))
