## Author: Rafiqul Islam


Architecture
========================

In this project, I implement 3 layers of RaspNet protocol. RaspNet is a networking protocol contains 7 layers as like as OSI model, but limited to basic functions. In this project, I developed Physical Layer, Data Link Layer and Network Layer of RaspNet protocol.
	## Physical Layer
This layer is responsible for sending and receiving raw bit streams over the physical medium. According to, RaspNet protocol, in Physical Layer two wires are used from one node to the next. The first one is data-pin, the second one is the clock-signal. Whenever the clock-signal changes (from 1 to 0 or from 0 to 1) there is a new bit there for reading on the data-pin.
	## Data Link Layer
This layer is responsible for the reliable transmission of data frames between two connected nodes. According to RaspNet, Layer 2 bundles all bits together to send network frames. A network frame begins with a preamble of "01111110". In this layer, CRC-32 (cyclic redundancy check) is used for error detection.
	## Network Layer
This layer structure and manage a multi-node network, addressing, routing as well as traffic control. According to RaspNet protocol, Layer 3 handles addressing, routing as well as the priority of each packet. 

Technology
========================
## Programming language
C programming language is used to implement this RaspNet protocol.

## Hardware device
+ Raspberry Pi: Raspberry pi is a single-board computer.
+ Gertboard: The Gertboard is an input/output (I/O) extension board for the Raspberry Pi computer. It fits onto theGPIO (general-purpose Input/Output) pins of the Raspberry Pi. 
+ Microcontroller: AVR Atmega328p microcontroller is used here. Gertboard contains this microcontroller inside the board. So it is not needed to add a separate microcontroller. Atmega328p is a single-chip microcontroller. It has an 8 bit RISC processor.

## Toolchain
+ Operating system: Linux based operating system is used here. NOOB, Raspbian, RISC OS, Ubuntu Mate, Ubuntu Core, etc are usually used for Raspberry Pi computer.
+ Serial communication program: For serial communication purposes, minicom is used. Minicom is a text-based serial communication program. Minicom command from the terminal has been given below.

> **Command:** 
> minicom -b 19200 -o -D /dev/ttyAMA0

+ Compiler: avr-gcc is used to compile C code.

+ avrdude: AVRDUDE is a command line program to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming techniquee.

+ Compiler:gcc-avr : Cross-compiler for C programming complitation for AVR microcontroller.

+ AVR library: avr-libc library is used which provides built-in functionalities to use with C programming.


## Installation
+ Minicom installation in Linux (Debian, Ubuntu, Kali, Mint)
> **Command:** 
> sudo apt install minicom -y

+ Minicom installation in Linux (Fedora, CentOS, RHEL)
> **Command:**
> sudo yum install minicom -y

+ avrdude installation in Linux
> **Command:**
> sudo apt-get install avrdude

+ AVR tool chain installation:
> **Command:**
> sudo apt-get install gcc-avr binutils-avr avr-libc


## Reference Links:
+ [ RaspNet protocol ]: [ https://osg.informatik.tu-chemnitz.de/lehre/emblab/protocol_final_4stud.pdf ]
+ [Gertboard Manual]: [ https://osg.informatik.tu-chemnitz.de/lehre/emblab/gertboard_manual_2.0.pdf ]
+ [AVR]: [ https://osg.informatik.tu-chemnitz.de/lehre/emblab/atmel.pdf ]
+ [avrdude]: [https://www.nongnu.org/avrdude/ ]
+ [avr-gcc]: [https://gcc.gnu.org/wiki/avr-gcc ]
+ [Minicom]: [https://salsa.debian.org/minicom-team/minicom5 ] 
+ [Raspberry Pi]: [https://www.raspberrypi.org/ ]

