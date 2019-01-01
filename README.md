# Interactive Umbrella with Arduino Uno
Queen Mary University group project:
Using an Arduino Uno with additional components(e.g. water sensors) we created an interactive umbrella which responds to environmental factors(rain, temperature, light level). There are 4 LED strips and water sensors attached to an umbrella. When water hits a water sensor, a corresponding LED strip lights up. We are reading in a light level of an environment with a photoresistor and depending on that value control the brightness of LED strips. The darker your surroundings are, the brighter are the LEDs. The lighter your environment is, the dimmer are the LEDs. When you use an umbrella in the evening/night time, LED strips will produce a lot of light. But when an umbrella is used during daytime there is no point to light up the LEDs to their full capacity since you would not see the outcome because of the sunlight. Additionally, it would be a waste of power/energy. We are using a temperature sensor to get a value of the temperature of the user’s environment. If the value is below a certain level(in our case 10°C), the LED stips would primarily use blue colour. When the temperature is above that limit, a primary colour of the strips will be red.

## Umbrella:
![umbrella](https://user-images.githubusercontent.com/17802955/50573891-83625c00-0dd4-11e9-933a-939abcb1ec30.jpeg)

## Arduino board layout:
![final circuit](https://user-images.githubusercontent.com/17802955/50523777-3def1780-0ad2-11e9-92b5-57377ad6032e.png)

## Video of the result:
https://www.youtube.com/watch?v=BgsNdKU57lk
