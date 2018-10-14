# Class: Sketching mit Hardware

## Traffic Control

An Arduino implementation of a traffic control system for a crossroad with one main street and a side street crossing into it: 
```
_______________________
__M_A_I_N__   _________
           |S|
           |I|
           |D|
           |E|
```

### Setup  
For configuration, setup the digital Arduino pins the traffic light LEDs and sensor I/O is connected to in `src/pins.h`  
You might also need to adjust the HEX codes associated with buttons on the IR Remote in `src/keys.h`

### Automatic control
By default, the main street always has green while the traffic light of the side street is set to red.  
Once a car driving up the side street approaches the traffic light (which is detected by an ultrasonic sensor), the traffic lights of main street turn red and traffic on side street is allowed to pass for a limited amount of time before its traffic light turns red again.  
Note that traffic on main street always is allowed to pass for a specified amound of time (currently `5s`) before side street can be set to green. If this amount is not reached yet, the green phase of side street will be delayed.

### Traffic can also be controlled manually using the remote as follows:  
> ON/OFF: Turns traffic lights on or off  
> EQ: Disables traffic lights – their yellow lights start blinking (to signal that they are inactive)  
> PLAY: Let traffic on side street pass for a limited amount of time (simulates an approaching car)  
> SKIP/PREV: Switch between allowing traffic on main street to pass or allowing traffic on side street to pass  
