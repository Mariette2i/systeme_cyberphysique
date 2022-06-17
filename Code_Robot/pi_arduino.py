from marvelmind import MarvelmindHedge
from time import sleep
from ctypes import *
import sys
from threading import Thread
import serial
from time import sleep
import math
import time

try:
   ser = serial.Serial('/dev/ttyS0', 115200, timeout=1)
except:
   print("ERROR - Could not open USB serial port.  Please check your port name and permissions.")
   print("Exiting program.")
   exit()



def main():
    global real_x, real_y, theta, pos_x, pos_y, G1, L, L1, p, target_x, target_y;
    real_x = 0
    real_y = 0
    theta = 0
    pos_x = 0
    pos_y = 0

    G1 = 0.1
    L = 185.0
    L1 = 0.1
    p = 90.0
    target_x = 0
    target_y = 0
    real_z = 0

    # COnfig du MarvelMind
    hedge = MarvelmindHedge(tty = "/dev/ttyACM0", adr=None, debug=False) # create MarvelmindHedge thread
    
    if (len(sys.argv)<2):
        print("python pi_arduino.py {position X} {position Y}")
        return
    else:
        target_x = float(sys.argv[1])
        target_y = float(sys.argv[2])
    
    # Récupération de l'angle (transmis par l'arduino)
    angle_thread = Thread(target=getAngle)
    angle_thread.start()
    
    # Création du thread pour s'exécuter toutes les 5 ms
    vgvd_thread = Thread(target=thread5ms)
    vgvd_thread.start()
    hedge.start() # start thread
    while True:
        try:
            hedge.dataEvent.wait(1)
            hedge.dataEvent.clear()
            real_x, real_y, real_z = getPosition(hedge)
           
            
            
        except KeyboardInterrupt:
            hedge.stop()  # stop and close serial port
            sys.exit()

# Récupération de la position du MarvelMidnd
def getPosition(hedge):
    return hedge.position()[1], hedge.position()[2], hedge.position()[3]

# Recupération de l'angle du robot : valeur transmise par l'arduino
def getAngle():
    global theta;
    while True:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        if line != '':
            theta_1 = float(line)
            theta = math.radians(int(theta_1))
            print(theta)

# Thread pour lancer un programme toutes les 5ms            
def thread5ms():
    while True:
        call5ms()
        sleep(0.005)
        
# Fonction appelée toute les 5 ms
def call5ms():
    global real_x, real_y, theta, pos_x, pos_y, G1, L, L1, p, target_x, target_y;
   
    # Bloc matlab "Controleur 1"
    rtb_Sum_i4 = G1 * target_x - L1 * real_x
    
    # Bloc matlab "Controleur 2"
    rtb_Sum_l = G1 * target_y - L1 * real_y

    # Bloc matlab "M(theta)^-1"
    rtb_Cos = math.cos(theta)
    rtb_Sin = math.sin(theta)
    rtb_Sum_h = rtb_Sum_i4 * rtb_Cos + rtb_Sin * rtb_Sum_l
    rtb_Gain_o = L
    rtb_Gain_o = (1.0 / rtb_Gain_o * rtb_Cos * rtb_Sum_l - rtb_Sum_i4 * rtb_Sin / rtb_Gain_o) * p
    
    # Bloc matlab "commande de vitesse pour les roues"
    vg = rtb_Sum_h - rtb_Gain_o
    vd = rtb_Sum_h + rtb_Gain_o

    # Affichage pour debug
    print("real : " + " x : " + str(real_x) + ", y : " + str(real_y) + ", angle : "+ str(theta))
    print("vg : " + str(round(vg*1000, 3)) + ", vd : " + str(round(vd*1000, 3)))
    print("target_x : " + str(target_x) + ", target_y : " + str(target_y))
    print("________________________________________")

    # Transmission à l'arduino : Ecriture des valeurs de vitesse (vg et vd) dans le port serial de l'arduino
    ser.write(bytes(str(round(vd*1000, 3))+ "D", encoding='utf-8') )
    ser.write(bytes(str(round(vg*1000, 3))+ "G", encoding='utf-8') )
   
main()
