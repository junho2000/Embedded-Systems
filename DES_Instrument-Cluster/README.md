# DES02_Instrument Cluster

## Team Member

💡 [Junho Kim](http://www.linkedin.com/in/junho-kim-3b007b1b9)


💡 [Oluwasegun Oyekeye](https://www.linkedin.com/in/oluwasegun-oyekeye-65a4209b/)


💡 [Krunal Patel](https://www.linkedin.com/in/krunal-patel007/)
  
## Table of Contents
- [Technical Overview](#technical-overview)
- [Installation and Setup](#installation-and-setup)
- [Hardware Components](#hardware-components)
- [System Architecture](#system-architecture)
- [Qt User Interface](#qt-user-interface)
- [Implementation Details](#implementation-details)
- [Testing and Debugging](#testing-and-debugging)
- [Qt](#qt)
- [Challenges Faced](#challenges-faced)
- [Results and Achievements](#results-and-achievements)
- [Future Work and Enhancements](#future-work-and-enhancements)
- [References](#references)
- [Appendices](#appendices)

# Technical Overview

## Introduction

 Software architecture, and implementation details. The document also includes information on testing and debugging, as well as future work and enhancements.

## Project Overview

This document outlines the process of creating a car speedometer using Arduino, CAN communication, a Raspberry Pi, and a Qt Dashboard application. The project involves capturing data from an infrared speedometer and ultrasonic distance sensor on an Arduino. This data is then transmitted to a Raspberry Pi via CAN communication. The Raspberry Pi preprocesses the data and utilizes D-Bus to communicate with a Qt Dashboard application, which visually displays the car's speedometer.

# Installation and Setup

## Raspberry Pi Setup

- 2-CH CAN Shield
    
    Step 1: Install `bcm2835` Library
    
    ```bash
    wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
    tar zxvf bcm2835-1.60.tar.gz
    cd bcm2835-1.60/
    sudo ./configure
    sudo make
    sudo make check
    sudo make install
    ```
    
    Step 2: Install `wiringpi` Library
    
    ```bash
    sudo -s
    apt --fix-broken install
    sudo apt-get install wiringpi
    wget https://project-downloads.drogon.net/wiringpi-latest.deb
    sudo dpkg -i wiringpi-latest.deb
    ```
    
    Step 3: Check `gpio` Version
    
    ```bash
    gpio -v
    ```
    
    Step 4: Install Required Python Packages
    
    ```bash
    sudo apt-get update
    sudo apt-get install python3-pip
    sudo apt-get install python3-pil
    sudo apt-get install python3-numpy
    sudo pip3 install RPi.GPIO
    sudo pip3 install spidev
    sudo pip3 install python-can
    ```
    
    Step 5: Set Up CAN Interfaces
    
    ```bash
    sudo ip link set can0 up type can bitrate 125000 dbitrate 8000000 restart-ms 1000 berr-reporting on fd on  # Set your own bitrate
    sudo ip link set can1 up type can bitrate 125000 dbitrate 8000000 restart-ms 1000 berr-reporting on fd on  # Set your own bitrate
    sudo ip link set can0 down  # To reset the bitrate and dbitrate of can0, if they are busy to change rate use this if you want to change the rate of the CAN protocol.
    sudo ifconfig can0 txqueuelen 65536
    sudo ifconfig can1 txqueuelen 65536
    ```
    
    Step 6: Verify Network Interfaces
    
    ```bash
    ifconfig
    ```
    
    Step 7: Install `can-utils` (Optional)
    
    ```bash
    sudo apt-get install can-utils
    ```
    
    Step 8: Test CAN Communication
    
    To accept all data from `can0`, use the following command:
    
    ```bash
    candump can0
    ```
    
    To send data from `can1`, use the following command:
    
    ```bash
    cansend can1 000#11.22.33.44
    ```

- 7.9 inch Touchable Display
    
    Step 1: Download and enter the Waveshare-DSI-LCD driver folder
    
    ```bash
    git clone https://github.com/waveshare/Waveshare-DSI-LCD
    cd Waveshare-DSI-LCD
    ```
    
    Step 2: Enter uname -a in the terminal to view the kernel version and cd to the corresponding file directory
    
    ```bash
    cd 5.15.84
    ```
    
    Step 3: Please check the bits of your system, enter the 32 directory for 32-bit systems, and enter the 64 directory for 64-bit systems
    
    ```bash
    cd 64
    ```
    
    Step 4: Enter your corresponding model command to install the driver, pay attention to the selection of the I2C DIP switch
    
    ```bash
    #7.9inch DSI LCD 400×1280 driver：
    sudo bash ./WS_xinchDSI_MAIN.sh 79 I2C0
    ```
    
    Step 5: Wait for a few seconds, when the driver installation is complete and no error is prompted, restart and load the DSI driver and it can be used normally
    
    ```bash
    sudo reboot
    ```
    

## Libraries

- Arduino Libraries
    - [MCP2515 CAN Bus Controller Module](https://github.com/autowp/arduino-mcp2515/)
    - [LCD1602 I2C Module](https://www.waveshare.com/wiki/File:LCD1602-RGB-Module-demo.zip)

# Hardware Components

## Pi Racer

- Pi Racer😎
    - [Pi-Racer Wiki](https://www.waveshare.com/piracer-ai-kit.htm) (Our final Pi Racer)

## Arduino Nano with Sensors & Can Module

- Arduino Nano

- MCP2515 CAN Bus Controller Module

- Ultrasonic Distance Sensor

- IR Speed Sensor

## Raspberry Pi

- Raspberry Pi 4B with 4GB RAM
    
- [2-CH CAN FD HAT](https://www.waveshare.com/wiki/2-CH_CAN_FD_HAT)
    
    

## 7.9 inch Touchable Screen

- Raspberry Pi with Touchable Screen
    - [7.9inch Capacitive Touch Display for Raspberry Pi, 400×1280](https://www.waveshare.com/7.9inch-dsi-lcd.htm)
    - [Touchable Screen Wiki](https://www.waveshare.com/wiki/7.9inch_DSI_LCD)

# System Architecture

## Hardware Architecture

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/7cbf4602-10f1-46c6-8537-53f1e57cba0f" style="width:600px;">

## Software Architecture

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/c3975396-b514-4951-915a-be0036cd7cc7" style="width:600px;">

# Qt User Interface

- Classic Dashboard Design

https://github.com/junho2000/Embedded-Systems/assets/73748884/1f3bacdf-fb4e-4804-9a06-6c5af12a88cc

(Fuel : Battery Level %, Speedometer : cm/s, Tachometer : RPM, Distance : cm)

- Modern Dashboard Design

https://github.com/junho2000/Embedded-Systems/assets/73748884/ad2e94d6-cddc-4c90-b281-3ff04011917e

[tesla_dashboard-2023-09-02_15.22.19 2.mp4](https://prod-files-secure.s3.us-west-2.amazonaws.com/1df925d9-eeb7-4003-aabb-5adc8a658a1f/647b444f-a5a1-4aa3-a5f3-ff2b693f359c/tesla_dashboard-2023-09-02_15.22.19_2.mp4)

[modern_dash.mp4](https://prod-files-secure.s3.us-west-2.amazonaws.com/1df925d9-eeb7-4003-aabb-5adc8a658a1f/5a06bf4c-6127-40bb-84b4-856588ef73ff/modern_dash.mp4)

# Implementation Details

## Data Gather

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/415cf1ee-d9e5-4f5f-846b-1de3d9b1e4d0" style="width:800px;">

- IR Speed Sensor
    
    ```arduino
    // ... (other includes and variable declarations)
    
    void setup() {
      // ... (CAN setup and Serial initialization)
    
    	//Speed Sensor D0 pin to D3 pin at Arduino
      attachInterrupt(digitalPinToInterrupt(3), Pulse_Event, RISING);
    
      delay(1000);
    }
    
    void loop() {
      // Speedometer calculations
      LastTimeCycleMeasure = LastTimeWeMeasured;
      CurrentMicros = micros();
      if (CurrentMicros < LastTimeCycleMeasure) {
        LastTimeCycleMeasure = CurrentMicros;
      }
      FrequencyRaw = 10000000000 / PeriodAverage;
      if (PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra) {
        FrequencyRaw = 0;  // Set frequency as 0.
        ZeroDebouncingExtra = 2000;
      } else {
        ZeroDebouncingExtra = 0;
      }
      FrequencyReal = FrequencyRaw / 10000;
    
      RPM = FrequencyRaw / PulsesPerRevolution * 60;
      RPM = RPM / 10000;
      total = total - readings[readIndex];
      readings[readIndex] = RPM;
      total = total + readings[readIndex];
      readIndex = readIndex + 1;
    
      if (readIndex >= numReadings) {
        readIndex = 0;
      }
      average = total / numReadings;
    
      //...
    }
    
    void Pulse_Event() {
    	// Speedometer pulse event handling
      PeriodBetweenPulses = micros() - LastTimeWeMeasured;
      LastTimeWeMeasured = micros();
      if (PulseCounter >= AmountOfReadings)  {
        PeriodAverage = PeriodSum / AmountOfReadings;
        PulseCounter = 1;
        PeriodSum = PeriodBetweenPulses;
    
        int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);
        RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);
        AmountOfReadings = RemapedAmountOfReadings;
      } else {
        PulseCounter++;
        PeriodSum = PeriodSum + PeriodBetweenPulses;
      }
    }
    ```
    

- Ultrasonic Distance Sensor
    
    ```arduino
    int ultrasonic() {
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
    
      long duration = pulseIn(ECHO_PIN, HIGH);
    
      int distance_cm = duration * 0.0343 / 2;
      Serial.print("Distance: ");
      Serial.println(distance_cm);
    
      return distance_cm;
    }
    ```
    

- CAN Communication
    
    ```arduino
    #include <SPI.h>
    #include <mcp2515.h>
    
    struct can_frame canMsg;
    MCP2515 mcp2515(10);
    
    void setup() {
      canMsg.can_id  = 0x036;           //CAN id as 0x036
      canMsg.can_dlc = 8;               //CAN data length as 8
      canMsg.data[0] = 0x00;               
      //...
    
      //CAN setup
    	SPI.begin();
    	mcp2515.reset();
      mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ); //Sets CAN at speed 125KBPS
      mcp2515.setNormalMode();
      Serial.println("Example: Write to CAN");
    
      delay(1000);
    }
    
    void loop() {
      // ... (Speedometer calculations and Ultrasonic readings)
    	
      int d = ultrasonic(); //distance
      int r = RPM; //rpm
      canMsg.data[0] = r; 
      canMsg.data[1] = d;
      mcp2515.sendMessage(&canMsg);     //Sends the CAN message
      delay(100);
    }
    ```
    

## Data PreProcessing & D-Bus Implement

- D-Bus Interface

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/eb465c04-1fb1-4d86-9005-c3c0fe8e637e" style="width:800px;">

1. **Client Process (Qt Dashboard Application):** This is the software application that wants to access or request certain services or data. Qt dashboard application serves as the client process. It can use D-Bus to communicate with other processes and request information.
2. **Service Process (Raspberry Pi with PyDBus):** This is the software application that provides the services or data that the client process wants to access. Raspberry Pi retrieves data from an Arduino via a CAN bus and publishes this data using PyDBus. This service process makes the data available to other applications through D-Bus.
3. **Message Request Method:** When the Qt dashboard application (client process) wants to retrieve a specific type of information, such as RPM or battery status, it sends a message request to the D-Bus system. This message contains the method name (e.g., **`get_rpm`**) and any required parameters.
4. **Message Response:** The service process (Raspberry Pi with PyDBus) receives the message request, processes it, and generates a response message. This response contains the requested information (e.g., RPM value or battery status) as a string. The response is then sent back to the client process through D-Bus.

```python
class dbusService(object):
    """
		<node>
			<interface name='com.example.dbusService'>
				<method name='get_rpm'>
					<arg type='s' name='rpm' direction='out'/>
				</method>
				<method name='get_distance'>
					<arg type='s' name='distance' direction='out'/>
				</method>
				<method name='energy_report'>
					<arg type='s' name='battery' direction='out'/>
				</method>
			</interface>
		</node>
	"""

    def can_recv_thread(self, can_bus):
        # ... (Receive CAN messages)

    def __init__(self):
        # ... (CAN interface setup)

    def get_rpm(self):
        # ... (Receive RPM value)
        return rpm

    def get_distance(self):
        # ... (Receive distance value)
        return distance

    def energy_report(self):
        # ... (Calculate Battery Level)
        return battery

if __name__ == "__main__":
    loop = GLib.MainLoop()
    bus = SessionBus()
    bus.publish("com.example.dbusService", dbusService())
    
    try:
        loop.run()
    except KeyboardInterrupt:
        os.system(f'sudo ifconfig {CAN_ID} down')
        loop.quit()
```

- CAN Communication
    
    ```python
    class dbusService(object):
        # ... (other methods)
        
        def can_recv_thread(self, can_bus):
            while True:
                self.msg = can_bus.recv()
                if self.msg is None:
                    print('Timeout occurred, no message.')
                else:
                    pass
        
        def __init__(self):
            os.system(f'sudo ifconfig {CAN_ID} down')
            os.system(f'sudo ip link set {CAN_ID} up type can bitrate 125000 dbitrate 8000000 restart-ms 1000 berr-reporting on fd on')
            self.can = can.interface.Bus(channel = CAN_ID, bustype = 'socketcan')
            self.piracer = PiRacerStandard()
            
            can_thread = Thread(target=self.can_recv_thread, args=(self.can,))
            can_thread.start()
    
    ```
    

- Multi-Thread
    - Why we use Multi-Thread?
 
    <img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/bbe9eb46-4c2a-42c3-a8c1-bc955ddf1023" style="width:600px;">
    
    Without multi-threading, the script may experience significant latency in displaying data on the dashboard. This can be attributed to the fact that the script is executing all its tasks sequentially within a single thread. When there's a delay in one task (e.g., reading CAN messages), it blocks the entire thread and prevents other tasks from executing. This can lead to delays in processing and updating the displayed data, resulting in a laggy dashboard display.

    <img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/f0e76a63-379f-4c9d-9f35-243888f2c03f" style="width:600px;">
    
    On the other hand, using multit-hreading allows the script to execute multiple tasks concurrently. In the code, the **`can_recv_thread`** function runs in a separate thread, continuously receiving CAN messages. This separation of tasks enables the main thread to focus on processing and displaying the data without waiting for new messages. This can significantly reduce latency and improve the responsiveness of the dashboard.
    
    ```python
    if __name__ == "__main__":
        loop = GLib.MainLoop()
        bus = SessionBus()
        bus.publish("com.example.dbusService", dbusService())
        
        try:
            loop.run()
        except KeyboardInterrupt:
            os.system(f'sudo ifconfig {CAN_ID} down')
            loop.quit()
    ```
    

- Weighted Moving Average Filter

    <img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/0e1b6bff-ba6b-4531-8954-a7697435e31b" style="width:600px;">

    ```python
    weights = [0.2, 0.3, 0.5]
    
    data_dis = deque(maxlen=len(weights))
    data_rpm = deque(maxlen=len(weights))
    
    def weighted_moving_average(data, weights):
        moving_average = sum(val * weight for val, weight in zip(data, weights))
        return moving_average
    ```
    
    A weighted moving average filter is a method of smoothing data by assigning weights to each data point and calculating a moving average of the weighted values. This filter is often used in signal processing to reduce noise or fluctuations in data. The weights assigned to each data point are typically determined by the user, and can be used to place more emphasis on recent data points or to give more weight to certain values. The result of the filter is a smoothed data set, where the impact of noise or sudden fluctuations is reduced.
    
    # Testing and Debugging
    
    The results presented below represents a graphical display of the instrument cluster in Revolution per Minutes average at a sampling time of 100s. 
    
    The following results provide a graphical representation of the instrument cluster in terms of average revolutions per minute (RPM) with 100ms & 50ms sampling time.
    
    The speed data displayed on the dashboard, when analyzed using both the moving average filter and the weighted moving average filter, exhibits similarities in terms of small latency and shape. However, it is important to note that the Exponential moving average filter introduces significant latency and is therefore not suitable for real-time application for dashboard.
    
    - Sampling time for 100ms
      sampling time 100ms 
    <img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/0d49498c-3cdf-450e-bea3-24a5407e3b89" style="width:600px;">
    
    - Sampling time for 50ms
    <img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/8b1f70f3-e5f3-4aff-b50b-49bb6a7ad6a1" style="width:600px;">


- Without filter

https://github.com/junho2000/Embedded-Systems/assets/73748884/39ef16d6-da31-4c3d-a24c-f2355d4d4d23


- With Weighted Average Moving filter

https://github.com/junho2000/Embedded-Systems/assets/73748884/7c828a67-f64b-45a4-a2f7-cc4a6c904c09



# Qt

## Qt Configure

- [Download Qt5.15.2 here](https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)
- if you need qtquick extras & qtpositioning qtlocation
    
    ```bash
    sudo apt-get update -y
    sudo apt-get install -y qml-module-qtquick-extras
    sudo apt install qml-module-qtlocation qml-module-qtpositioning
    sudo apt-get install -y qml-module-qtwebengine
    sudo apt-get install -y qml-module-qtquick-virtualkeyboard
    sudo apt-get install -y qml-module-qtmultimedia
    ```
    

## Cross-Compile

- Host OS : Ubuntu 20.04.6 LTS
- Target OS : Linux raspberrypi 5.15.84-v8+ “Bulleye” 64bit

Step 1: Update System(Host)

```bash
sudo apt update
sudo apt upgrade
```

Step 2: Install Cross Compiler(Host)

```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

Step 3 : Directory Setup(Host)

Create the required directory structure under `~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4`:

```bash
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/build
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/tools
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot/usr
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot/opt
sudo chown -R 1000:1000 ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
cd ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
```

Step 4: Download Qt Resources(Host)

Download the Qt resources and unpack them in the `raspberrypi4` directory:

```bash
sudo wget http://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz
sudo tar xfv qt-everywhere-src-5.15.2.tar.xz
```

Step 5: Modify mkspec file(Host)

To use the compiler, modify the mkspec file:

```bash
cp -R qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabi-g++ qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabihf-g++
sed -i -e 's/arm-linux-gnueabi-/arm-linux-gnueabihf-/g' qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabihf-g++/qmake.conf
```

Step 6: Rsync Raspberry Libraries(Host)

Copy the original Raspberry Pi libraries into the Ubuntu directories using rsync:

```bash
cd Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
rsync -avzS --rsync-path="rsync" --delete team07@192.168.86.41:/lib/ sysroot/lib
rsync -avzS --rsync-path="rsync" --delete team07@192.168.86.41:/usr/include/ sysroot/usr/include
rsync -avzS --rsync-path="rsync" --delete team07@192.168.86.41:/usr/lib/ sysroot/usr/lib
rsync -avzS --rsync-path="rsync" --delete team07@192.168.86.41:/opt/vc/ sysroot/opt/vc
```

Step 7: Clean up symbolic links(Host)

Clean up the symbolic links so that they point to the correct original files:

```bash
sudo apt install symlinks
cd Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
symlinks -rc sysroot
```

Step 8: Compile Qt(Host)

Configure and compile Qt for Raspberry Pi:

[copy linux-rasp-pi4-aarch64 to your devices folder](https://code.qt.io/cgit/qt/qtbase.git/tree/mkspecs/devices)

```bash
cd Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/qt5.15/mkspecs/devices
vim qmake.conf
vim qplatformdefs.h
```

```bash
cd build
../qt-everywhere-src-5.15.2/configure -release -opengl es2 -eglfs -device linux-rasp-pi4-aarch64 -device-option CROSS_COMPILE=aarch64-linux-gnu- -sysroot ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot -prefix /usr/local/qt5.15 -extprefix ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
make -j16
make install
```

Step 9: Send compiled files on the Raspberry Pi(Host)

If the compilation is successful, copy the compiled files to the Raspberry Pi using rsync:

```bash
cd build-cc_ex-team07-Debug/
rsync -avz --rsync-path="rsync" filename team07@192.168.86.51:/home/team07
```

Step 10: Execute on the Raspberry Pi(RPi)

```bash
cd /home/team07
./cc_ex
```

## Dashboard GUI

- Connect to D-Bus in Qt
    1. Make a C++ Class to manage D-Bus.
    - dbusmanager.h
        
        ```cpp
        //necessary headers for working with QtDBus
        #ifndef DBUSMANAGER_H
        #define DBUSMANAGER_H
        
        //...
        
        class DBusManager : public QObject
        {
            Q_OBJECT
        public:
            explicit DBusManager(QObject* parent = nullptr);
            // ...
        
        private:
        		//D-Bus connection using QDBusConnection::sessionBus(), which connects to the session bus, where user-specific communication takes place.
            QDBusConnection m_bus;
        
        		//D-Bus interface that your application will use to communicate with the remote service. It's used to call methods.
            QDBusInterface* m_interface;
            // ...
        };
        ```
        
    
    - dbusmanager.cpp
        
        ```cpp
        DBusManager::DBusManager(QObject* parent) : QObject(parent),
            m_bus(QDBusConnection::sessionBus()),
            m_rpm(0)
        {
            // ...
        		
        		//make a sepcific D-Bus to communicate
            m_interface = new QDBusInterface("com.example.dbusService", "/com/example/dbusService", "com.example.dbusService");
        		
        		//check if interface is valid, if not program off.
            if(!m_interface->isValid()){
                qDebug() << "Interface not valid: " << qPrintable(m_interface->lastError().message());
                exit(1);
            }
        }
        
        void DBusManager::fetchData() {
            // ...
        		
        		//message request to method
            QDBusMessage rpm = m_interface->call("get_rpm");
            QDBusMessage distance = m_interface->call("get_distance");
            QDBusMessage battery = m_interface->call("energy_report");
        
            // ...
        		
        		//when D-Bus call encountered an error, print the error message and exit the application.
        		if(rpm.type() == QDBusMessage::ErrorMessage || distance.type() == QDBusMessage::ErrorMessage || battery.type() == QDBusMessage::ErrorMessage ) {
        		    qDebug() << "Error: " << qPrintable(rpm.errorMessage());
        		    exit(1);
        		}
        }
        ```
        
    
    1. Register C++ Class to qml
        
        ```cpp
        #include "dbusmanager.h"
        
        int main(int argc, char *argv[])
        {
        	//... 
        	qmlRegisterType<DBusManager>("com.example", 1, 0, "DBusManager");
        
        	// Create an instance of the DBusManager class
        	DBusManager dbusManager;
        }
        ```
        
    

- GUI Design with qml
    - Import the required QML modules and their versions.
    
    ```cpp
    import QtQuick 2.2
    import QtQuick.Window 2.1
    import QtQuick.Controls 1.4
    import QtQuick.Controls.Styles 1.4
    import QtQuick.Extras 1.4
    ```
    
    - Window has a width of 1280 and a height of 400. It also sets the window's background color to a dark shade.
    
    ```cpp
    Window {
        id: root
        visible: true
    		//when executed it turns to FullScreen
        visibility: "FullScreen"
        width: 1280
        height: 400
        color: "#161616"
        title: "Qt Dashboard"
    ```
    
    - **`ValueSource`** is likely a custom QML component that provides data values for the gauges.
    
    ```cpp
        ValueSource {
            id: valueSource
        }
    ```
    
    - Within the **`gaugeRow`**, four sections are defined. Each section contains a **`CircularGauge`** or an **`Item`** placeholder. The **`CircularGauge`** elements display different aspects of the dashboard : fuel level, speedometer, tachometer, and temperature. They will be displaying values from the **`ValueSource`** component.
    
    ```cpp
                Item {
                    // CircularGauge for fuel
                }
    
                CircularGauge {
                    // CircularGauge for speedometer
                }
    
                CircularGauge {
                    // CircularGauge for tachometer
                }
    
                Item {
                    // CircularGauge for temperature
                }
    ```
    
- Backend Design with C++

<img src="https://github.com/junho2000/Embedded-Systems/assets/73748884/f94aa93e-6c2e-450e-8ed3-e12d11301ce4" style="width:800px;">

- C++ & qml connect
    - **main.cpp**
    
    In the `main.cpp` file, the `qmlRegisterType` function is used to register the `DBusManager` C++ class with QML. This allows QML to create instances of this class and access its properties and methods directly from QML.
    
    ```cpp
    int main(int argc, char *argv[])
    {
        // ...
    
        // Registering the DBusManager C++ class with QML
        qmlRegisterType<DBusManager>("com.example", 1, 0, "DBusManager");
    
        // ...
    }
    ```
    
    - **dbusmanager.h**
    
    In the `DBusManager` class definition (`dbusmanager.h`), the `Q_INVOKABLE` macro is used to mark certain methods as invokable from QML. These methods include `fetchData`, `getSpeed`, `getDistance`, `getBattery`, and `getRPM`. These methods will be accessible from QML and can be called directly from there.
    
    ```cpp
    class DBusManager : public QObject
    {
        Q_OBJECT
    public:
        // ...
    
        // Q_INVOKABLE methods that can be accessed from QML
        Q_INVOKABLE void fetchData(); // Fetches RPM data from D-Bus
        Q_INVOKABLE qreal getSpeed();
        Q_INVOKABLE qreal getDistance();
        Q_INVOKABLE qreal getBattery();
        Q_INVOKABLE qreal getRPM();
    
        // ...
    };
    
    ```
    
    - **ValueSource.qml**
    
    In the QML file (`ValueSource.qml`), the `import com.example 1.0` statement imports the C++ class registered with QML. This allows you to access the methods of the `DBusManager` class directly from QML.
    
    ```
    import com.example 1.0
    
    Item {
        // ...
    
        NumberAnimation {
            // ...
    
            onRunningChanged: {
                if (!running && kph !== dbusmanager.getSpeed()) {
                    from = kph
                    to = dbusmanager.getSpeed()
                    running = true
                }
            }
        }
    
        // ... (similar NumberAnimation blocks)
    
    }
    
    ```
    

## Challenges Faced

- Non Real-time Speedometer Display
    
    Initially, there was significant latency in the speedometer display when real-time data was not provided. However, this issue was resolved by implementing multi-threading in the application.
    
- Fluctuation of RPM data
    
    Weighted moving average filter can be used to reduce the fluctuation in raw RPM data. This filter gives more weight to recent data points and less weight to older data points. By adjusting the weights, we can control the level of smoothing.
    

# Results and Achievements

Based on the project objectives, we successfully achieved the following outcomes:

- Implemented, tested and validated a Qt-based graphical user interface (GUI) for the instrument cluster using PiRacer.
- Integrated an Arduino-based sensor system with the Raspberry Pi instrument cluster using the CAN bus protocol.
- Displayed real-time speed data on the instrument cluster GUI by interfacing the speed sensor system with PiRacer.
- Verified system functionality through testing across different speed use cases. The system displayed speed accurately without glitches.
- The Qt GUI provided a polished and responsive interface for displaying the real-time speedometer.
- CAN bus integration allowed reliable speed data transfer from the speed sensors.
- The end-to-end system achieved the goal of building a functional real-time speedometer display using PiRacer and Arduino. The testing results as presented validated the accuracy and reliability of the system.

# Future Work and Enhancements

Some possible improvements we propose based on the limitation of this projects are 

- The integration of warning to notify of speed limits, this will expect to provide a better user experience with the system.
- More Parallel Connection via CAN & D-Bus which can result in a robust extensibility of the system, and allow for efficient utilization of the communication module by allowing it report valuable performance features like engine temperature, wheel diagnostic message, alerts etc.
- More Various GUI Design like designing it for different parking modes such as parking, reversing, navigation etc.

# References

- Sritu Hobby. IR Infrared Speed Sensor with Arduino - How does it work? IR Speed Sensor. **https://srituhobby.com/ir-infrared-speed-sensor-with-arduino-how-does-work-ir-speed-sensor/**
- autowp. Arduino MCP2515 CAN interface library https://github.com/autowp/arduino-mcp2515/
- Vijay, Vamsavardhana & S., Divya & Song, Yalei & Oda, Takuma & Murali, Manika. (2016). Low Power System Architecture for PowerDUE Management System.
- P., Pratik. “PiRacer DES_Instrument-Cluster.” GitHub, GitHub, 25 Aug. 2023, https://github.com/SEA-ME/DES_Instrument-Cluster.

# Appendices
