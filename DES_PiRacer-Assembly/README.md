## **Assemble Pi Racer**

- [Pi-Racer Wiki](https://www.waveshare.com/piracer-ai-kit.htm) (Our Pi Racer)

- [Pi-Racer Assemble Wiki](https://www.waveshare.com/wiki/JetRacer_Assembly_Manual) (Which to take care)
    - Procedure 11 has an error : M3*10 -> M3*8
    - Steering Chassis has to be properly physically neutral(fine tune at Pi Racer Configuration)
    - Connect right direction of Li-ON battery

- Assembled Pi Racer

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/d88348b3-f579-455a-b3d6-7b17624b894c" style="width:600px;">

## **Raspberry Pi Configuration**




- OS
    - Rasbian Desktop “Bulleye” 64-bit
    
    - Linux raspberrypi 5.15.84-v8+ #1610 SMP PREEMPT aarch64 GNU/Linux
- Raspberry Pi Configuration
    
```bash
sudo raspi-config
```

1. enable Interfacing Options - I2C
2. enable Interfacing Options - SPI

1. enable Interfacing Options - SSH
2. enable Interfacing Options - Camera

```bash
sudo reboot
```

- dependencies
    
```bash
sudo apt update
sudo apt-get upgrade
sudo apt install \
    gcc \
    v4l-utils \
    i2c-tools \
    raspi-config \
    python3-setuptools \
    python3-venv \
    libopencv-dev

sudo apt-get install build-essential python3 python3-dev python3-pip python3-virtualenv python3-numpy python3-picamera python3-pandas python3-rpi.gpio i2c-tools avahi-utils joystick libopenjp2-7-dev libtiff5-dev gfortran libatlas-base-dev libopenblas-dev libhdf5-serial-dev libgeos-dev git ntp
sudo apt-get install libilmbase-dev libopenexr-dev libgstreamer1.0-dev libjasper-dev libwebp-dev libatlas-base-dev libavcodec-dev libavformat-dev libswscale-dev libqtgui4 libqt4-test
```
    

## Pi Racer Configuration

- Pi Racer structure

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/6a7f458d-a3da-4fd5-98a4-2e7999696404" style="width:600px;">

```bash
sudo apt-get install -y i2c-tools
sudo i2cdetect -y 1
```

then this i2c information appears!

```bash
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- --
10: -- -- -- -- 14 -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- 3c -- -- --
40: 40 41 -- -- -- -- -- -- -- -- -- 4b -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: 60 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: 70 -- -- -- -- -- -- --
```

- Install Pi Racer package
    
```bash
cd ~
mkdir piracer_test/
cd piracer_test/
python3 -m venv venv
source venv/bin/ativate

pip install piracer-py
```
    

- Calibrate Pi Racer
    - to see which path Pi-Racer library's from
    
```bash
which python3
```
  
  - set path Pi-Racer library
  
```bash
source env/bin/activate (activate)

or

deactivate env/bin/activate (deactivate)
```
    
    - calibrate (/home/team7/env/lib/python3.9/site-packages/piracer/vehicle.py)
    
```python
class PiRacerBase:
  ...
  def _get_50hz_duty_cycle_from_percent(cls, value: float) -> float:
    return 0.0015 + (value * 0.0005) #ex) to 0.0016
```
    

## ****Run Pi Racer Programming and testing****

- Run control example

```python
import time
from piracer.vehicles import PiRacerStandard

if __name__ == '__main__':

    # piracer = PiRacerPro()
    piracer = PiRacerStandard()

    # Forward
    piracer.set_throttle_percent(0.2)
    time.sleep(2.0)

    # Brake
    piracer.set_throttle_percent(-1.0)
    time.sleep(0.5)
    piracer.set_throttle_percent(0.0)
    time.sleep(0.1)

    # Backward
    piracer.set_throttle_percent(-0.3)
    time.sleep(2.0)

    # Stop
    piracer.set_throttle_percent(0.0)

    # Steering left
    piracer.set_steering_percent(0)
    time.sleep(1.0)

    # Steering right
    piracer.set_steering_percent(0.0)
    time.sleep(1.0)

    # Steering neutral
```

- Remote control example

```python
from piracer.vehicles import PiRacerStandard
from piracer.gamepads import ShanWanGamepad

if __name__ == '__main__':

    shanwan_gamepad = ShanWanGamepad()
    #piracer = PiRacerPro()
    piracer = PiRacerStandard()

    while True:
        gamepad_input = shanwan_gamepad.read_data()
        throttle = gamepad_input.analog_stick_right.y * 0.5
        steering = -gamepad_input.analog_stick_left.x

        print(f'throttle={throttle}, steering={steering}')

        piracer.set_throttle_percent(throttle)
        piracer.set_steering_percent(steering)
```

- Grab images example using OpenCv

```python
import cv2

def main():
    camera = cv2.VideoCapture(0)  

    if not camera.isOpened():
        print("camear is not open.")
        return

    while True:
        ret, frame = camera.read()
        if not ret:
            print("camera is not open.")
            break
        cv2.imshow("frame", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    camera.release()
    cv2.destroyAllWindows()
 image = camera.read_image()
 cv2.imwrite('image.png', image)
    
if __name__ == "__main__":
    main()
```

- OLED display example

```python
import os
import pathlib
import time
import signal
import math
from piracer.vehicles import PiRacerBase, PiRacerStandard, PiRacerPro

FILE_DIR = pathlib.Path(os.path.abspath(os.path.dirname(__file__)))

def print_battery_report(vehicle: PiRacerBase):
    battery_voltage = vehicle.get_battery_voltage()
    battery_current = vehicle.get_battery_current()
    power_consumption = vehicle.get_power_consumption()
    print("v:", battery_voltage)
    print("i:", battery_current)
    print("w:", power_consumption)
    power = (battery_voltage-9)/3.2*100
    print(power,'%')
    display = vehicle.get_display()

    output_text = 'U={0:0>6.3f}V\nI={1:0>8.3f}mA\nP={2:0>6.3f}W'.format(battery_voltage, battery_current,
                                                                                power_consumption)

    display.fill(0)
    display.text(output_text, 0, 0, 'white', font_name=FILE_DIR / 'fonts/font5x8.bin')
    display.show()

def handle_exit(signal_num, frame):
    display = piracer.get_display()
    display.fill(0)
    display.show()
    sys.exit(0)

if __name__ == '__main__':

    # piracer = PiRacerPro()
    piracer = PiRacerStandard()

    signal.signal(signal.SIGINT, handle_exit)

    try:
        while True:
            print_battery_report(piracer)
            time.sleep(0.5)
    except KeyboardInterrupt:
        pass
```
