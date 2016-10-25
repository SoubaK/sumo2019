# -*- coding: utf-8 -*-
"""
Created on Mon Nov 03 23:08:08 2014
@author: christianhamelain
"""

##import random
##
import math
##
##import os

from pathManager import PathManager
from util import *
from beachbotMapV2 import *


class Trajectoire :


    def __init__(self, coordinates, angle, orientation) :

        self.position = [coordinates, angle, orientation]
        
        self.currentWay = []

        self.facteurDistance = 50

        self.facteurDegre = 10

    def wololo(self, path) :
        # pas de changement d'orientation sur cette portion de trajectoire

        coor0 = self.position[0]
        angle0 = self.position[1]
        orientation = self.position[2]
        way = []
        
        for coor in path[1:] :
            (x0, y0) = coor0
            (x, y) = coor
            distance = dist(coor0, coor)
            ang = - angle0 + angle((0, 1), (x - x0, y - y0))
            ang = (ang + math.pi) % (2*math.pi)  - math.pi     # ang dans [-180, 180]
            way.append((distance*self.facteurDistance, ang*180/math.pi*self.facteurDegre, orientation)) 
            angle0 = ang
            coor0 = coor

        self.currentWay = way
        
        return way

    

    def vaVoirLaBasSiJySuis(self, point) :

        pouet = PathManager(beachbotsForest.getForest())
        pouet.setThreshold(4)
        (x, y) = point
        pouet.findPath(self.position[0],(x, y, 0))

        print "path"
        print pouet.path

        wolo = self.wololo(pouet.path)

        for coor in pouet.path :
            (x, y) = coor
            beachbotsForest.forest[x][y] = -8

        #beachbotsForest.displayForest()
        
        return wolo
		
    def estCeUnRobot(self, distance, capteur) :
		
        coordRepere = getCoord(self.position[0], self.position[1],13.5)
        if(capteur == 0) :
            coordRepere = getCoord(coordRepere, self.position[1]-(math.pi / 2),13.5)
        else :
            coordRepere = getCoord(coordRepere, self.position[1]+(math.pi / 2),13.5)
        coordRepere = getCoord(coordRepere, self.position[1],distance)
		
        return (beachbotsForest.forest[int(coordRepere[0])][int(coordRepere[1])] > 0)

    def poseUnRobot(self, coord, radius) :
	    

        beachbotsForest.popCircle(coordRepere, radius, -2)
	
    def detection(self, distances, capteurs) :
	    
		
		coordRepere = getCoord(self.position[0], self.position[1],13.5)
        if(capteurs[0] and capteurs[1]) :
            
        else if(capteurs[0]):
		    coordRepere = getCoord(coordRepere, self.position[1]-(math.pi / 2),13.5)
		else if(capteurs[1]):
		    coordRepere = getCoord(coordRepere, self.position[1]+(math.pi / 2),13.5)
        coordRepere = getCoord(coordRepere, self.position[1],distance + 19)
        coordRepere = [int(coordRepere[0]),int(coordRepere[1])]
		
		self.poseUnRobot(coorRepere, 19)
		

#beachbotsForest.displayForest()

traj = Trajectoire((70, 30), 0, True)
print traj.estCeUnRobot(80, 0)
traj.poseUnRobot([20,0], 0)
beachbotsForest.displayForest()
pouet = traj.vaVoirLaBasSiJySuis((70, 270))

print pouet
