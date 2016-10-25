import pickle
import math

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.image import Image
from kivy.graphics import Color,Line,Rectangle
from kivy.graphics.context_instructions import PushMatrix,PopMatrix,Rotate,Translate
from kivy.core.window import Window
from kivy.uix.label import Label

from kivy.config import Config
Config.set('graphics', 'resizable', '0')
Config.write()

IMG_W = 884
IMG_H = 588
DX = 25.0
DY = 25.0

INI_X = 2760
INI_Y = 1000

R_W = 270
R_H = 300

ARM_DX = 25 * IMG_W / 3000.0
ARM_DY = 45 * IMG_H / 2000.0

STEP = 20
STEP_ANGLE = 5
FORWARD, BACKWARD = 0,1
ROT, LIN = 0,1

armAngles = [(-180,0), (-135,-45), (-85, -95)]

def normalizeAngle(angle):
    while (angle <= -180):
	 angle += 360
    while (angle > 180):
	angle -= 360;
    return angle

class Map(Widget):
    
    def __init__(self, **kwargs):
        super(Map, self).__init__(**kwargs)
        
        self._keyboard = Window.request_keyboard(self._keyboard_closed, self)
        self._keyboard.bind(on_key_down=self._on_keyboard_down)
        
        self.size_hint = None, None
        Window.size = self.size
        
        self.waypoints = []
        self.side = 'g'
        self.armMode = 0
        self.progress = 0
        self.fishMode = 0
        
        self.rX, self.rY = 0,0
        self.rAngle = 0
        self.rMode = ROT
        self.rArmMode = 0
        self.waypointIndex = 0
        
        self.drawCanvas()
        
    def getTotalLength(self, index):
        
        if len(self.waypoints) == 0:
            return 0
        
        prevX, prevY = self.waypoints[0][:2]
        length = 0
        
        for i in range(1, min(index,len(self.waypoints))):
            x,y = self.waypoints[i][:2]
            length += math.sqrt( (x-prevX)*(x-prevX) + (y-prevY)*(y-prevY) )
            prevX, prevY = x,y
            
        return length
    
    
    def moveRobot(self, direction):
        
        if len(self.waypoints) < 2:
            return
        
        if self.rMode == ROT:
            
            if len(self.waypoints) < 2 or self.waypointIndex == len(self.waypoints) - 1:
                return
            
            wX, wY = self.waypoints[self.waypointIndex + 1][:2]
            waypointsAngle = math.atan2(wY - self.rY, wX - self.rX) * 180 / math.pi
            d_angle_norm = normalizeAngle(waypointsAngle - self.rAngle)
            d_angle_opp = normalizeAngle(waypointsAngle - self.rAngle + 180)
            
            if( abs(d_angle_norm) < abs(d_angle_opp)):
                d_angle = d_angle_norm
                orientation = 0
            else:
                d_angle = d_angle_opp
                orientation = 180
                
            sign = math.copysign(1, d_angle)
            self.rAngle += sign * STEP_ANGLE
            
            if abs(d_angle) - STEP_ANGLE < 0:
                self.rAngle = waypointsAngle + orientation
                self.rMode = LIN
                self.waypointIndex += 1
            
        else:
            
            self.rArmMode = self.waypoints[self.waypointIndex][2]
            
            if direction == FORWARD:
                if self.progress + STEP > self.getTotalLength(len(self.waypoints)):
                    return
                else:
                    self.progress += STEP
            
            progressToNextWaypoint = self.getTotalLength(self.waypointIndex+1)
            nextX,nextY = self.waypoints[self.waypointIndex][:2]
            if self.progress >= progressToNextWaypoint:
                self.progress = progressToNextWaypoint
                self.rX,self.rY = nextX,nextY
                
                self.rMode = ROT
                
            else:
                distanceToNextWaypoint =  progressToNextWaypoint - self.progress
                L = math.sqrt((self.rX-nextX)*(self.rX-nextX) + (self.rY-nextY)*(self.rY-nextY))
                self.rX,self.rY = nextX + distanceToNextWaypoint * (self.rX-nextX) / L, nextY + distanceToNextWaypoint * (self.rY-nextY) / L
                
            
    def putRobotOnLastWaypoint(self):
        
        if len(self.waypoints) < 1:
            return
        
        self.rX,self.rY = self.waypoints[-1][:2]
        self.progress = self.getTotalLength(len(self.waypoints))
        
        if len(self.waypoints) >= 2:
            w1X,w1Y = self.waypoints[-2][:2]
            w2X,w2Y = self.waypoints[-1][:2]
            
            self.rAngle = math.atan2(w2Y - w1Y, w2X - w1X) * 180 / math.pi
            
        self.rMode = ROT
        self.waypointIndex = len(self.waypoints) - 1
        
    def putRobotBeginning(self):
        
        if len(self.waypoints) == 0:
            return
        
        self.progress = 0
        
        self.rX, self.rY = self.waypoints[0][:2]
        if self.side == 'g':
            self.rAngle = 0
        else:
            self.rAngle = 180
        self.rMode = ROT
        self.rArmMode = self.waypoints[0][2]
        self.waypointIndex = 0
            
                
        
    def _keyboard_closed(self):
        self._keyboard.unbind(on_key_down=self._on_keyboard_down)
        self._keyboard = None

    def _on_keyboard_down(self, keyboard, keycode, text, modifiers):
        if keycode[1] == 'c':
            self.waypoints = []
            self.progress = 0
        elif keycode[1] == 'r':
            self.putRobotBeginning()
        elif keycode[1] == 's':
            pack = [self.side, self.waypoints]
            pickle.dump(pack, open("waypoints" + self.side + ".txt", "w"))
            
        elif keycode[1] == 'l':
            pack = pickle.load(open("waypoints" + self.side + ".txt", "r"))

            self.side = pack[0]
            self.waypoints = pack[1]
        elif keycode[1] == 'd':
            if(len(self.waypoints) > 0):
                del self.waypoints[-1]
                if len(self.waypoints) == 1 or self.progress > self.getTotalLength(len(self.waypoints)):
                    self.putRobotOnLastWaypoint()
        elif keycode[1] == 't':
            self.armMode = (self.armMode + 1) % 3
            if(len(self.waypoints) > 0):
                self.waypoints[-1] = (self.waypoints[-1][0], self.waypoints[-1][1], self.armMode, self.fishMode)
        elif keycode[1] == 'up':
            self.moveRobot(FORWARD)
        elif keycode[1] == 'p':
            self.fishMode = 1 - self.fishMode
            
        self.drawCanvas()
        return True
        
    def drawCanvas(self):
        self.canvas.clear()
        
        
        with self.canvas:
            
            PushMatrix()
            
            # La map
            Rectangle(source='map.png', pos=self.pos, size=self.size)
            
            # Les waypoints
            first = True
            for (x,y,m,f) in self.waypoints:
                x *= IMG_W / 3000.0
                y *= IMG_H / 2000.0
                
                
                if(first):
                    first = False
                    
                    # Couleur du cercle
                    Color(1, 1, 0, 0.7) # Jaune : premier point
                else:
                    #Ligne
                    Color(0, 1, 0)
                    Line(points=[x, y]+lastPt)
                    
                    # Couleur du cercle
                    if(m == 0):
                        Color(1, 0, 0, 0.7) # Rouge = ferme
                    elif(m == 1):
                        Color(0, 1, 0, 0.7) # Vert = triangle
                    else:
                        Color(0, 0, 1, 0.7) # Bleu = ouvert
                        
                Line(circle=(x, y, 7), width=2)
                lastPt = [x,y]
                
                # Indicateur poisson
                if f == 1:
                    Color(0, 0, 0)
                    Line(circle=(x, y, 12), width=2)
            
            
            # Dessin de la silhouette du robot

            if len(self.waypoints) > 0:
                x,y,angle = self.rX,self.rY,self.rAngle
                x *= IMG_W / 3000.0
                y *= IMG_H / 2000.0
                
                Translate(x,y)
                
                rot = Rotate()
                rot.origin = (0,0)
                rot.angle = angle
                
                # Robot
                w,h = R_W *  IMG_W / 3000.0, R_H *  IMG_H / 2000.0
                Color(0, 0, 0, 0.2)
                Rectangle(pos=(-w/2,-h/2), size=(w, h))
                
                Color(1, 0, 0, 0.8)
                
                # Bras 1
                PushMatrix()
                Translate(w/2 - ARM_DX, h/2 - ARM_DY)
                rot2 = Rotate()
                rot2.origin = (0,0)
                rot2.angle = armAngles[self.rArmMode][0]
                Rectangle(pos=(-1,0), size = (2, 170 * IMG_H / 2000.0))
                PopMatrix()
                
                # Bras 2
                PushMatrix()
                Translate(w/2 - ARM_DX, -h/2 + ARM_DY)
                rot2 = Rotate()
                rot2.origin = (0,0)
                rot2.angle = armAngles[self.rArmMode][1]
                Rectangle(pos=(-1,0), size = (2, 170 * IMG_H / 2000.0))
                PopMatrix()
                
            PopMatrix()
                
                    
            
    def on_touch_down(self, touch):
        
        x = touch.x * 3000.0 / IMG_W
        y = touch.y * 2000.0 / IMG_H
        
        # Snap a la grille
        x = x+DX/2 - (x+DX/2)%DX
        y = y+DY/2 - (y+DY/2)%DY
        
        self.waypoints.append((int(x), int(y), self.armMode, self.fishMode))
        #print self.waypoints
        
        
        if len(self.waypoints) == 1:
            self.rX,self.rY = self.waypoints[0][:2]
            if self.side == 'g':
                self.rAngle = 0
            else:
                self.rAngle = 180
                
            self.rMode = ROT
            self.rArmMode = self.armMode
            self.waypointIndex = 0
        
        self.drawCanvas()

class TestApp(App):

    def build(self):
        self.title = 'SUMO Planner'
	return Map(pos=(0,0), size=(IMG_W,IMG_H))


if __name__ == '__main__':
    TestApp().run()
