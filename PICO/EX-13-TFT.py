from ST7735 import TFT
from sysfont import sysfont
from machine import SPI,Pin
import time
import math

TFT_CS=4
TFT_RESET=5
TFT_A0=9
TFT_SDA=11
TFT_SCK=10

spi = SPI(1, baudrate=20000000, polarity=0, phase=0,miso=None)
tft=TFT(spi,TFT_A0,TFT_RESET,TFT_CS)
tft.initr()

tft.fill(TFT.BLACK)


tft.text((0, 0), "thingZkit_TFT", TFT.WHITE, sysfont, 3)
time.sleep_ms(1000)


