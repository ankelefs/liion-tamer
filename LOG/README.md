## LiIon Tamer LOG

<br>

**R&R** = Research and results

<br>

#### Monday, February 6th, 2023:
Setup a flowcharts for the different modes I want the liion-tamer (LT) system to do. Also started on the schematics for the charging circuit.  

<br>

#### Tuesday, February 7th:
Got feedback on my circuit from a friend in my class: try using a bootstrapped N-type MOSFET as a high side switch for less "live wires" and active power consumption. 

**R&R:** A bootstrapped, high side NMOS, although may draw less power in active mode, does not yield a good result for this type of implementation. The main reason is that the bootstrapped high side NMOS seems to be best suited for high frequency switching operations, because when the NMOS is turned ON over a "long time", the capacitor will be slowly drained, finally turning it OFF. Since I want to charge a cell, over a long time, I will stick to a high side PMOS alternative.

<br>

#### Tuesday, March 9th:
I got some li-ion cells from a classmate. These had voltages around 0.5 to 0.7 V. I got the tip, from the same classmate, to try and revive them with a little "push". I researched the idea and tested it on one of the cells (a video which documents the event has been made). 

**TEST:** The test conducted was to attach the cell to my bench power supply, set it to 4.0 V and max. of 1 A current draw. I then applied this to the cell for about 30 seconds. 
**RESULT:** The voltage increased to about 2.8 V measuring with a multimeter afterwards, although the multimeter showed a high voltage drop rate of about 0.05 V/s. I initially thought the cell is dead and cannot be used, but research gave the impression that the multimeter draws a tiny bit of current while measuring, and the low capacity left in the cell made the voltage drop fast. 
**FURTHER TESTING:** A further test should to the same test as described above, but also immediately start cell-charging. Then the voltage "self-drop" rate should be measured again. 

I also made (but not tested) the charging circuit from this schematic:

Here is a picture of the circuit: