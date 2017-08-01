'''
Kenneth Jung
Mechatronics Engineering
https://github.com/k22jung
'''

import tweepy
import serial
from time import sleep

# Get tokens by creating an app at: https://apps.twitter.com/


# Authenticate Twitter
auth = tweepy.OAuthHandler(ctoken, csecret)
auth.set_access_token(atoken, asecret)
api = tweepy.API(auth)

#Initialize Arduino connection
ser = serial.Serial(3, 9600) # COM4
ser.close()
ser.open()
sleep(2)


while True:
		try:
			# Get most recent Tweet
			msg = api.user_timeline(count=1)[0] 
	
			# Exit program or send byte to Arduino
			# if message is valid. Immediately deletes
			# command Tweet so duplicates do not exist.
			if msg.text[0:4].lower() == '/led':
				if msg.text[5:8].lower() == 'red':
					ser.write(b'R')
					print('RED')
					api.destroy_status(msg.id)
				elif msg.text[5:9].lower() == 'blue':
					ser.write(b'B')
					print('BLUE')
					api.destroy_status(msg.id)
				elif msg.text[5:10].lower() == 'green':
					ser.write(b'G')
					print('GREEN')
					api.destroy_status(msg.id)
				elif msg.text[5:15].lower() == 'light blue':
					ser.write(b'L')
					print('LIGHT BLUE')
					api.destroy_status(msg.id)
				elif msg.text[5:10].lower() == 'cycle':
					ser.write(b'C')
					print('RESUMING CYCLE')
					api.destroy_status(msg.id)
				elif msg.text[5:10].lower() == 'break':
					ser.write(b'C')
					print('PROGRAM BREAK')
					api.destroy_status(msg.id)
					break
				elif msg.text[5:9].lower() == 'stay':
					print('PROGRAM BREAK')
					api.destroy_status(msg.id)
					break
			
			# Delay to maintain request rate limit
			sleep(7);
		
		except serial.SerialException: 
			break
ser.close()
