## Space Invaders Game and Gaming Pad

#### Motivation 

I built this project to reinforce my learning on computer graphics and interfaces with external hardware like gaming pads. I happened to have a 'damaged' gaming pad in my junk box. Been building simple openFrameworks projects so interfacing with a hacked gaming pad seemed like a nice project for a start.

![start-screen](.\img\start-screen.png)

![game-screen](.\img\game-screen.png)

#### How it works

##### Gaming pad 

This gaming pad utilizes two analog sticks of the pad as the other buttons were pretty damaged. So I reverse engineered the sticks, extracted the connections to X and Y axes and push buttons and glued everything together on a perf-board. 

###### Broken gaming pad

![game-screen](.\img\broken.jpg)



###### Re-constructed gaming pad

The re-contructed gaming pad looks as below: 

![game-screen](.\img\gaming-pad.jpg)



#### Gaming pad schematic

Most gaming pads feature two analog sticks and some pressure push buttons. The analog sticks are made of two potentiometers that output  voltage values based on their resistance (position). The pressure push buttons are reactive to user-press. The stronger the user pressed the button, the less the resistance, therefore more current passes through that circuitry and it is interpreted appropriately. You can read more about gaming pads electronics here: https://scholar.valpo.edu/cgi/viewcontent.cgi?article=1004&context=stja

The below schematic shows how I interfaced the two analog sticks of the broken pad with an ESP-DEVKIT and utilized its ADC to extract the potentiometer values: 

[image-schematic] 



##### Software interface 

I needed to write some sort of a 'driver' to this gaming pad to allow interfacing with the firmware. The needed functions were:

1. Read the state of the push buttons for left and right sticks
2. Read the X and Y axes values for the left and right sticks

This equated to creating an instance for each stick - left and right. The 'class' definition look as as below:

[image-class-struct]

### How to build and run the game 

1. Make sure you have openFrameworks set up on your machine. You can check out how to do that on https://openframeworks.cc/
2. Download this repo as a zip file.
3. Extract the zip archive into a new folder. In the new folder, you will 



### References

1. Game splash screen : https://www.google.com/url?sa=i&url=https%3A%2F%2Fgithub.com%2Fflightcrank%2Fspace-invaders&psig=AOvVaw2sGXSs8_Zt1q-g28Koeaky&ust=1714921605528000&source=images&cd=vfe&opi=89978449&ved=0CBQQjhxqFwoTCNDly_qi9IUDFQAAAAAdAAAAABAE

2. OpenFrameworks: https://openframeworks.cc/

3. OF hardware: https://openframeworks.cc/ofBook/chapters/hardware.html

4. OF Serial: https://openframeworks.cc/documentation/communication/ofSerial/#:~:text=Reads%20and%20returns%20a%20single,is%20%25d%22%2C%20myByte)%3B

5. Gaming Pad Electronics(PDF): https://scholar.valpo.edu/cgi/viewcontent.cgi?article=1004&context=stja

   