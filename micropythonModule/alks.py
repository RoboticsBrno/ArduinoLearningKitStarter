import machine
import network
import time

def delay(ms):
	time.delay_ms(ms)

r = None
g = None
b = None
y = None

def setupLeds():
	global r, g, b, y
	r = machine.Pin(22, machine.Pin.OUT)
	g = machine.Pin(17, machine.Pin.OUT)
	b = machine.Pin(5, machine.Pin.OUT)
	y = machine.Pin(23, machine.Pin.OUT)

RGBr = None
RGBg = None
RGBb = None

def setupRgbLeds():
	global RGBr, RGBg, RGBb
	RGBr = machine.Pin(4, machine.Pin.OUT)
	RGBg = machine.Pin(21, machine.Pin.OUT)
	RGBb = machine.Pin(16, machine.Pin.OUT)

def cekej(ms):
	delay(ms)

def testLEDs():
	global r, g, b, y
	global RGBr, RGBg, RGBb
	setupLeds()
	setupRgbLeds()
	r.value(1)
	delay(100)
	g.value(1)
	delay(100)
	b.value(1)
	delay(100)
	y.value(1)
	delay(100)
	RGBr.value(1)
	delay(100)
	RGBg.value(1)
	delay(100)
	RGBb.value(1)
	delay(100)
	r.value(0)
	delay(100)
	g.value(0)
	delay(100)
	b.value(0)
	delay(100)
	y.value(0)
	delay(100)
	RGBr.value(0)
	delay(100)
	RGBg.value(0)
	delay(100)
	RGBb.value(0)
	delay(100)
