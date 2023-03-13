# Li-Ion Tamer journal


This is the complete development journal for the Li-Ion Tamer project.


<br>


## Abbreviations
**R&R** = Research and results <br>
**T** = Test <br>
**R** = Result <br>
**FT** = Further testing


<br>


### Monday, February 6th, 2023:
Setup flowcharts for the different modi I want the liion-tamer (LT) system to do. Also started on the schematics for the charging circuit.  


<br>


### Tuesday, February 7th:
Got feedback on my circuit from a friend in my class: try using a bootstrapped N-type MOSFET as a high side switch for less "live wires" and active power consumption. 

**R&R:** A bootstrapped, high side NMOS, although may draw less power in active mode, does not yield a good result for this type of implementation. The main reason is that the bootstrapped high side NMOS seems to be best suited for high frequency switching operations, because when the NMOS is turned ON for a "long time", the capacitor will be slowly drained, finally turning it OFF. Since I want to charge a cell, over a long time, I will stick to a high side PMOS alternative.


<br>


### Tuesday, March 9th:
I got some li-ion cells from a classmate. These had voltages around 0.5 to 0.7 V. I got the tip, from the same classmate, to try and revive them with a little "push". I researched the idea and tested it on one of the cells (a video which documents the event has been made). 

**T:** The test conducted was to attach the cell to my bench power supply, set it to 4.0 V and max. of 1 A current draw. I then applied this to the cell for about 30 seconds. 

**R:** The voltage increased to about 2.8 V measuring with a multimeter afterwards, although the multimeter showed a high voltage drop rate of about 0.05 V/s. I initially thought the cell is dead and cannot be used, but research gave the impression that the multimeter draws a tiny bit of current while measuring, and the low capacity left in the cell made the voltage drop fast. 

**FT:** A further test should to the same test as described above, but also immediately start cell-charging. Then the voltage "self-drop" rate should be measured again. 

I also made (but not tested) the charging circuit from this schematic:
![schematic](https://user-images.githubusercontent.com/18615800/224134239-04de22d5-ca76-45ea-b223-604aa53ab282.jpeg)

Here is a picture of the circuit:
![circuit](https://user-images.githubusercontent.com/18615800/224134266-80909a26-9520-4cc2-a958-81eabdf17536.JPG)


<br>


### Saturday, March 11th:
**T:** Tested the revive method (4 V, 1A for 25 seconds) and immediately put it to charging (with another TC4056 circuit power directly via a USB charger). 

**R:** Worked perfectly. The cell did not even get hot. It is now revived and fully charged, but I have not conducted a health status check.

I worked some more on the Charge Only (CO) mode circuit and code, see picture below. 
![circuit-number-2](https://user-images.githubusercontent.com/18615800/224506289-9aa0dd79-43e8-4239-9168-c21d3db705b9.JPG)
I changed from trying to use MOSFETs to just using a relay operating from a 5 V signal that the Arduino can provide. The reason is that with testing different topologies for the MOSFETs, each had their drawbacks, and wanting to make this first circuit easy and of course, safe, I adapted to a relay. The high side PMOS worked, but at startup or pressing the Arduino's "Reset" button, a voltage spike to 4 V at the battery output happened. This is something I seriously want to avoid, as to not damage the cell. A low side NMOS worked better, but for some reason, when I wanted to turn off the charger, it was still on even though the gate was put to 0 V. I could probably troubleshoot some more and find an answer as to why that happens, but since I have some relays laying around and they are safe and secure for these types of operations, and I don't need to worry about voltage potentials along the circuit, it seems like a good alternative.

The reason I did not choose a relay at the beginning was that I wanted to try MOSFETs, and that I thought the Arduino could not handle many relays at the same time. But it turns out it can! Since I power the Arduino from an external source (not USB), that source is powering the relay (@~450 mA draw ON-state) and the signal from the Arduino only draws about 2 mA. The Arduino can supply 0.8 A, so we have plenty of wiggle room. 

I also added a LCD display and a push button to provide a better user interface. I am not sure if I opt for the 16x2 LCD display or if I want to use an OLED display instead. It seems that the Arduino Nano Every will be streched to its limit regarding available PINs either way, so I can only make the Li-Ion Tamer for a single battery cell and must thus make more of these (whole) systems to expand capacity for multiple cells, so I think I will just choose the most cheap option of the LCD and OLED screen. 

Here is the **Rev**ision 2 Charge Only circuit. It still misses a temperature measurement. Also: the code is not finished.
![schematics-revision-2](https://user-images.githubusercontent.com/18615800/224507117-a109136d-9b57-4c46-a87c-3d0138cd19f8.jpeg)


<br>


### Sunday, March 12th:
**R&R:** Researched the TC4056A charger circuit IC and found that the STDBY-pin on the IC can be used as a charge status indicator. When it is in standby the voltage is ~3.7 V and ~1.3 V when charging. In the code, when charging is initiated, I enable the charger and delay the code 3.5 seconds to give the charger time to register that the battery cell is there and start charging, bringing the STDBY voltage down, before then monitoring that same voltage.

I have also written some more on the code, and the Charge Only mode is starting to get close to finished. I first need a bigger breadboard to work with before continuing. At this point, where the code for this mode is soon finished, I also have to make a state machine diagram to ensure I have implemented the right things at the right places.
