import board
import time
import digitalio
import analogio
from ulab import numpy as np

# some_led = digitalio.DigitalInOut(board.GP16) # put an LED circuit on pin GP16
# some_led.direction = digitalio.Direction.OUTPUT
# some_button = digitalio.DigitalInOut(board.GP15) # put a button circuit on GP15
# some_button.direction = digitalio.Direction.INPUT
built_in_led = digitalio.DigitalInOut(board.LED)
built_in_led.direction = digitalio.Direction.OUTPUT
adc_pin_a0 = analogio.AnalogIn(board.A0)
built_in_led.value = 1


# sampling rate
sr = 1024
#time step
ts = 1.0/sr
t = np.arange(0,1,ts)

sine1 = 5*np.sin(2*np.pi*10*t)
sine2 = np.sin(2*np.pi*3*t)
sine3 = np.sin(2*np.pi*7*t)

f_array = sine1 + sine2 + sine3

[real, imag] = np.fft.fft(f_array)
i = 0
print(len(real))
for i in range(0,len(real)):
    print("("+str(abs(real[i]))+",)") # print with plotting format
