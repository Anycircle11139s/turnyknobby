# turnyknobby
I made a turny knobby thingy cause I wanted my desk to look cooooolll. So i can be reall tuff and flex my sigma-ness to all my friends, I also throught it would be really fun to design and build, and so far, I'm right. I wanted to be able to control my volume without spamming my volume increase buttons, and I wanted the thing to be bluetooth, cause I don't like wires clutering up my desk.

I started with the custom PCB, I kind of based the PCB off a blinky board, except it has a microcontroller and no random other stuff, just microcontroller connected to leds with a rotary encoder for the turning. I chose the xiao esp32-s3 ecause of its bluetooth capabilities and after finishing my schematic, I started on the PCB. I made circle as the edges of the PCB and put the LEDs in a circle around the edges so they can display how high my volume is. I made sure the rotary encoder was in the exact middle, so when I turn it (there will be a case on top) the case wont look weird. After tracing it up, I finished the PCB.

<img width="769" height="357" alt="Screenshot 2026-04-21 at 12 10 45 pm" src="https://github.com/user-attachments/assets/896c1f0d-60ce-487a-9193-e53ac312b3c8" />
<img width="775" height="735" alt="Screenshot 2026-04-21 at 12 10 57 pm" src="https://github.com/user-attachments/assets/99b9b21c-55cd-4253-8f47-df979d0a3e4f" />
<img width="655" height="543" alt="Screenshot 2026-04-21 at 12 11 06 pm" src="https://github.com/user-attachments/assets/16fb5486-0f7f-464c-84bf-d3eeac22f43e" />


Once I finsihed the PCB, I moved on to the CAD. Before I could fully begin with CADing the case, I had to get all my 3d models imported, and to do that, I would have to decide which lipo battery I would use. I spent a while trying to decide and I made sure the one I chose had a 3d model of it, so I could cad it into the case. Once I had all my 3d models imported, I moved on to actually creating the case. I started by creating the bottom and frame, like I always do, created the turn thingy and made a hole for the rotary encoder, so that when I turn the case, it turns the rotary encoder. Then, I created some slots for the lid in the bottom part of the case, so it fits properly. After that, I added supports for the PCB and lipo battery, and with that, I finsihed the CAD.

<img width="794" height="717" alt="Screenshot 2026-04-21 at 12 08 46 pm" src="https://github.com/user-attachments/assets/bc06f0bc-efde-493d-b852-0c4f08d7aad9" />
<img width="734" height="578" alt="Screenshot 2026-04-21 at 10 14 02 am" src="https://github.com/user-attachments/assets/c79bd638-faa9-4049-9f91-b9c33711e05a" />
<img width="763" height="624" alt="Screenshot 2026-04-21 at 10 13 53 am" src="https://github.com/user-attachments/assets/2b731c10-f819-4591-8e1e-1bf333f7495a" />
<img width="787" height="685" alt="Screenshot 2026-04-21 at 12 09 03 pm" src="https://github.com/user-attachments/assets/01a83ed9-8f6f-4ec8-b5a9-25872e9dfea3" />
<img width="727" height="564" alt="Screenshot 2026-04-21 at 12 09 08 pm" src="https://github.com/user-attachments/assets/0474b25f-9f78-4773-824b-db6540fa0372" />


After that, I made some simple code and I had finally finished my design, I hope this gets approved soon, so I can order my parts and build this thing.
