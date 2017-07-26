# Arduino Tweeter

A command may be sent through a Twitter account to remotely control LED lighting, using "/led (command)". 
Python is used to interface between a Twitter API, Tweepy, and serial communication. 
Only works for a user enabling the application.

### Commands:<br />
/led (command)<br />
     blue<br />
     light blue<br />
     green<br />
     red<br />
     cycle<br />
     stay<br />
     break

### Dependencies:<br />
pyserial 2.7<br />
Tweepy 3.5.0

