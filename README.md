# USB Support for the Second Generation Pano Logic Thin Client

https://github.com/skiphansen/panog2_usb

This project is an attempt to port Ultra embedded's usb host controller [core](https://github.com/ultraembedded/core_usb_host)
to the second generation Pano Logic thin client. 

## Status
This is very much a work in progress.  

Currently the project builds and runs, but fails while trying to 
enumerates the root USB hub.

I am making this repository public in the hope of finding a collaborator 
with more experience to help move this project forward.

Please see the [debug notes](debug_notes.md) for more details on the 
current state.

## HW Requirements

* A Pano Logic G2, rev C
* A suitable 5 volt power supply
* A JTAG programmer to load the bitstream into the FPGA.

**NB:** According to core_usb_host's [README.md](https://github.com/ultraembedded/core_usb_host#readme):

```
The core requires a 48MHz/60MHz clock input, which the AXI4-Lite and UTMI 
interfaces are expected to be synchronous to.
```

The RISC-V core doesn't run reliably @ 48 Mhz on a Rev B Pano 
(-2 speed grade), but it does on a Rev C with the -3 speed grade.  
Hence A **Rev C IS REQUIRED**.  Once (if) we get this running on a rev C
I have some ideas on how to get it to work on a Rev B.

## Serial port 

A serial port is required for debugging and currently that's all this
project is good for!

The prebuilt .bit file uses the mini HDMI port for serial.  The RTL can be
be changed to use DVI port if you like.

Please see the [fpga_test_soc](https://github.com/skiphansen/fpga_test_soc/tree/master/fpga/panologic_g2#serial-port) for connection information.

You will need to set the "TARGET_PORT" environment variable to point
to your serial device.

## Running

Run "make run" to load the bitstream into the Pano and then reload
the test code with an console attached.

```
skip@Dell-7040:~/pano/working/panog2_usb$ make run
make -C fw/usb_test load
make[1]: Entering directory '/home/skip/pano/working/panog2_usb/fw/usb_test'
make[2]: Entering directory '/home/skip/pano/working/panog2_usb/fpga'
xc3sprog -c jtaghs2 -v /home/skip/pano/working/panog2_usb/prebuilt/pano-g2.bit
XC3SPROG (c) 2004-2011 xc3sprog project $Rev: 774 $ OS: Linux
Free software: If you contribute nothing, expect nothing!
Feedback on success/failure/enhancement requests:
        http://sourceforge.net/mail/?group_id=170565
Check Sourceforge for updates:
        http://sourceforge.net/projects/xc3sprog/develop

Using built-in device list
Using built-in cable list
Cable jtaghs2 type ftdi VID 0x0403 PID 0x6014 Desc "Digilent USB Device" dbus data e8 enable eb cbus data 00 data 60
Using Libftdi, Using JTAG frequency   6.000 MHz from undivided clock
JTAG chainpos: 0 Device IDCODE = 0x04011093     Desc: XC6SLX100
Can't open datafile /home/skip/pano/working/panog2_usb/prebuilt/pano-g2.bit: No such file or directory
Reading Bitfile /home/skip/pano/working/panog2_usb/prebuilt/pano-g2.bit failed
USB transactions: Write 6 read 3 retries 0
make[2]: Leaving directory '/home/skip/pano/working/panog2_usb/fpga'
make[1]: Leaving directory '/home/skip/pano/working/panog2_usb/fw/usb_test'
make -C fw/usb_test run_prebuilt
make[1]: Entering directory '/home/skip/pano/working/panog2_usb/fw/usb_test'
/home/skip/pano/working/panog2_usb/pano/tools/dbg_bridge/run.py -d /dev/ttyUSB.Pano -b 1000000 -f  ../../prebuilt/usb_test
/home/skip/pano/working/panog2_usb/pano/tools/dbg_bridge/poke.py -t uart -d /dev/ttyUSB.Pano -b 1000000 -a 0xF0000000 -v 0x1
/home/skip/pano/working/panog2_usb/pano/tools/dbg_bridge/poke.py -t uart -d /dev/ttyUSB.Pano -b 1000000 -a 0xF0000000 -v 0x0
/home/skip/pano/working/panog2_usb/pano/tools/dbg_bridge/load.py -t uart -d /dev/ttyUSB.Pano -b 1000000 -f ../../prebuilt/usb_test -p ''
ELF: Loading 0x0 - size 14KB
 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| 100.0%
/home/skip/pano/working/panog2_usb/pano/tools/dbg_bridge/console-uart.py -t uart -d /dev/ttyUSB.Pano -b 1000000
main: usb_test compiled Jun  9 2022 09:26:44
main: USB reset
main: Calling usbhw_reset()
main: calling usb_configure_device()
USB: Unknown OUT response (00)
USB: Unknown OUT response (00)
```

## Software Requirements

* Xilinx ISE 14.7
* GNU make
* RISC-V GCC built for RV32IM
* xc3sprog or Xilinx tools with a Platform or XVC compatible cable.

The free Webpack version of Xilinx [ISE 14.7](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive-ise.html) is used for development.
Download the latest Windows 10 version which supports the Spartan 6 family of 
chips used in the second generation Panologic device.
If you prefer, you can easily build a [docker image](https://github.com/vmunoz82/ise14) 
with ISE 14.7.


### Building everything from sources

**NB:** While it may be possible to use Windows for development I haven't 
tried it and don't recommend it.

1. Clone the https://github.com/skiphansen/panog2_usb repository
2. cd into panog2_usb
3. Make sure that RISC-V GCC (built for RV32IM) is in the PATH.
4. Make sure that ISE 14.7 for the Spartan 6 family is in the PATH.
5. Set the PLATFORM enviornment variable to pano-g2-c
6. Run "make build_all".



## Acknowledgement and Thanks
This project uses code from several other projects including:
 - https://github.com/ultraembedded/fpga_test_soc
 - https://github.com/ultraembedded/core_usb_host

## Pano Links

Links to other Pano logic information can be found on the 
[Pano Logic Hackers wiki](https://github.com/tomverbeure/panologic-g2/wiki)

## LEGAL 

My original work (the Pano glue code) is released under the GNU 
General Public License, version 2.

