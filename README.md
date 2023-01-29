# HolographicDisplayFan

This project have been created at Politehnica Timisoara as part of my study plan. 
The teacher: Sorin Nanu proposed this porject: "Holographic Display Fan using Arduino ATmega328 and 10 LEDs". 
After the final evaluation my project got the best score. The physical project is now showcased in Sorin Nanu Laboratory.

How the Project Works:

-using an internal interupstion to mesure the time it take the fan to complate a revolution, and use this time to display in the next revolution.
-how every letter is displayed is saved in: "letters.h" file togheder with the display function: "afisareLitera(litera, i)".
	-the display function modify the output of PORTC and PORTD on the ATmega328 chip.
-one revolution of the blade is divided in 120 circle arcs. In each arc will be displayed a pice of letter or nothing for space.
