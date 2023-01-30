# HolographicDisplayFan

![tempsnip](https://user-images.githubusercontent.com/123864033/215341999-49846908-dc0c-411a-8f91-e20d7e7024cf.png)

This project has been created at Politehnica Timisoara as part of my study plan.

The teacher (Sorin Nanu) proposed this project: "Holographic Display Fan using Arduino ATmega328 and 10 LEDs". After the final evaluation my project got the best score. The physical project is now showcased in my teacher's Laboratory.

How the Project Works:

-Using an internal interruption to measure the time it takes the fan to complete a revolution, and use this time to display in the next revolution.
-How every letter is displayed is saved in: "letters.h" file together with the display function: "afisareLitera(litera, i)".
-The display function modifies the output of PORTC and PORTD on the ATmega328 chip.
-One revolution of the blade is divided in 120 circle arcs. In each arc it will be displayed a piece of a letter or nothing for space.
