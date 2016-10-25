# -*- coding: utf-8 -*-
"""
Created on Mon Apr 11 23:11:08 2016
@author: christianhamelain
"""
from carte import Map


size = (200, 300)

beachbotsForest = Map(size)




beachbotsForest.enclose(0)

# coins circulaires

beachbotsForest.popCircle((200,0),25,0)

beachbotsForest.popCircle((200,300),25,0)

# batons au sol

beachbotsForest.popRectangle((0,80),(20,83),0)

beachbotsForest.popRectangle((0,217),(20,220),0)

# plage

beachbotsForest.popRectangle((75,90),(78,210),0)

beachbotsForest.popRectangle((78,148),(135,153),0)



beachbotsForest.enlargeYourPenis(20, -1)


#beachbotsForest.displayForest()


