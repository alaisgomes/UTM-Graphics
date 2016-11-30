
##CSCI 325 - Computer Graphics
##Aline Lais Gomes Tavares
#Assignment 3: User Interaction (Painting with Pixels)


* Intructions to compile: make

*Instructions to execute: ./paint

##Intructions: 
It starts with drawing random-colorized squares qith left button of mouse + motion

Right mouse click: Opens Menu. Menu Options:
* Larger: 		Increase square dimensions by 5px
* Smaller: 		Decrease square dimensions by 5px
* Toggle Mode: 	Alternate to draw squares with just mouse click, no motion
* Erase: 		You can activate/deactivate it and it will erase areas where you click in.
			   			Alternatively, you can press the keyboard button 'e' to turn erase mode on/off.
* Draw Lines: 	You can activate/deactivate it with this button, it will let you draw connected lines
						If you happen to close a polygon with the lines, the line mode is automatically be 
						turned off and brush/square mode will be on again
##Keyboard functions:
* Key 'c': 		Clear the screen
* Key 'b':		Clear the screen and change background color (it alternate between black and white background)
* Key 'e': 		Erase Mode (keybard option)



ps: I fixed the issue I showed during the class demo where my screen cleared whenever I right-clicked with
    mouse, apparently I was indeed using glClear() instead of using glFlush() to keep drawing the squares.
