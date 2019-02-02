import machine
import network
import time

# Pinout definition
TX = 1
RX = 3

D0 = 40
D1 = 41
D2 = 15
D3 = 2
D4 = 0
D5 = 4
D6 = 16
D7 = 17
D8 = 5
D9 = 18
D10 = 19
D11 = 21
D12 = 22
D13 = 23

A0 = 32
A1 = 33
A2 = 25
A3 = 26
A4 = 27
A5 = 14
A6 = 12
A7 = 15

L_R = 22
L_G = 17
L_Y = 23
L_B = 5
L_RGB_R = 4
L_RGB_G = 21
L_RGB_B = 16

SW1 = 15
SW2 = 2
SW3 = 0

POT1 = 32
POT2 = 33

PIEZO1 = 19
PIEZO2 = 18

PHOTO = 25

DHT_PIN = 26

S1 = 4
S2 = 16
S3 = 18
S4 = 19
S5 = 21

SDA = 27
SCL = 14

SS    = 19
MOSI  = 21
MISO  = 22
SCK   = 23

DAC1 = 25
DAC2 = 26

r = None
g = None
b = None
y = None

def setupLeds():
	global r, g, b, y
	r = machine.Pin(L_R, machine.Pin.OUT)
	g = machine.Pin(L_G, machine.Pin.OUT)
	b = machine.Pin(L_B, machine.Pin.OUT)
	y = machine.Pin(L_Y, machine.Pin.OUT)

RGBr = None
RGBg = None
RGBb = None

def setupRgbLeds():
	global RGBr, RGBg, RGBb
	RGBr = machine.Pin(L_RGB_R, machine.Pin.OUT)
	RGBg = machine.Pin(L_RGB_G, machine.Pin.OUT)
	RGBb = machine.Pin(L_RGB_B, machine.Pin.OUT)

sw1 = None
sw2 = None
sw3 = None

def setupButtons():
	global sw1, sw2, sw3
	sw1 = machine.Pin(SW1, machine.Pin.IN, machine.Pin.PULL_UP)
	sw2 = machine.Pin(SW2, machine.Pin.IN, machine.Pin.PULL_UP)
	sw3 = machine.Pin(SW3, machine.Pin.IN, machine.Pin.PULL_UP)

piezo = None

def setupPiezo():
	global piezo
	piezo = machine.PWM(machine.Pin(PIEZO1))
	piezoGND = machine.Pin(PIEZO2, machine.Pin.OUT)
	piezoGND.off()

def setupAll()
	setupLeds()
	setupRgbLeds()
	setupButtons()
	setupPiezo()
	
def setupRgbPwm():
	global RGBr, RGBg, RGBb
	RGBr = machine.PWM(machine.Pin(L_RGB_R))
	RGBg = machine.PWM(machine.Pin(L_RGB_G))
	RGBb = machine.PWM(machine.Pin(L_RGB_B))

pot1 = None
pot2 = None

def setupPotenciometers():
	global pot1, pot2
	pot1 = machine.ADC(machine.Pin(POT1))
	pot2 = machine.ADC(machine.Pin(POT2))

def delay(ms):
	time.delay_ms(ms)

def cekej(ms):
	delay(ms)

def testLEDs(t = 100):
	global r, g, b, y
	global RGBr, RGBg, RGBb
	setupLeds()
	setupRgbLeds()
	r.on()
	delay(t)
	g.on()
	delay(t)
	b.on()
	delay(t)
	y.on()
	delay(t)
	RGBr.on()
	delay(t)
	RGBg.on()
	delay(t)
	RGBb.on()
	delay(t)
	r.off()
	delay(t)
	g.off()
	delay(t)
	b.off()
	delay(t)
	y.off()
	delay(t)
	RGBr.off()
	delay(t)
	RGBg.off()
	delay(t)
	RGBb.off()
	delay(t)
