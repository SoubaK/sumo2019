# -*- coding: utf-8 -*-
"""
Created on Tue Feb 01 00:46:08 2017
@author: paulwitz
"""

from carte import Map


size = (200, 300)

moonVillageSubway= Map(size)




moonVillageSubway.enclose(0)

# base circulaire

moonVillageSubway.popCircle((200,150),20,0)


# bases rectangulaires ie racks

# ceux de la base centrale
moonVillageSubway.popRectangle((180,193),(120,207),-2)
moonVillageSubway.popRectangle((184,162),(146,206),-2)
moonVillageSubway.popRectangle((184,138),(180,94),-2)

# ceux sur les cotes
moonVillageSubway.popRectangle((68,0),(117,11),-2)
moonVillageSubway.popRectangle((68,300),(117,289),-2)


# Fuuuuuuuuuuuuuusées !

moonVillageSubway.popCircle((135,4),4,-1)
moonVillageSubway.popCircle((135,296),4,-1)
moonVillageSubway.popCircle((4,115),4,-1)
moonVillageSubway.popCircle((4,185),4,-1)

# Zones de départ
moonVillageSubway.popRectangle((36,0),(38,71),0)
moonVillageSubway.popRectangle((36,300),(38,229),-2)

# Modules 
moonVillageSubway.popCircle((60,20),3,-3)
moonVillageSubway.popCircle((185,80),3,-3)

moonVillageSubway.popCircle((110,50),3,-3)
moonVillageSubway.popCircle((140,90),3,-3)
moonVillageSubway.popCircle((60,100),3,-3)

moonVillageSubway.popCircle((20,205),3,-4)
moonVillageSubway.popCircle((60,280),3,-4)
moonVillageSubway.popCircle((185,220),3,-4)

moonVillageSubway.popCircle((110,250),3,-3)
moonVillageSubway.popCircle((140,210),3,-3)
moonVillageSubway.popCircle((60,200),3,-3)


# Volcans
moonVillageSubway.popCircle((200,0),51,-5)
moonVillageSubway.popCircle((200,300),51,-5)
moonVillageSubway.popCircle((54,65),17,-5)
moonVillageSubway.popCircle((54,235),17,-5)
moonVillageSubway.popCircle((187,193),17,-5)
moonVillageSubway.popCircle((187,107),17,-5)

# Bascules

moonVillageSubway.popRectangle((0,36),(36,71),-6)
moonVillageSubway.popRectangle((0,229),(36,264),-6)


moonVillageSubway.enlargeYourPenis(20, -1)


#moonVillageSubway.displayForest()
