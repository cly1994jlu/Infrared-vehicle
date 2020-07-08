# Infrared-vehicle
Infraded-controller vehicle, detect and avoid obstacles using ultrasound, sense temperature and humidity and feedback

Update on 2020-07-08, The University of British Columbia, Vancouver, BC, Canada. Copyright reserved.

This is a poject that my classmates and I cooperated to accomplish a long time ago, when we were still undergraduate students at Jilin University in the spring of 2015. This project finally wons the first-class award in 2015 Jilin University Electronic Design Competition.

In this project, we designed a controller and a vehicle using C51 SCM. We can use a controller to send controlling signals to the vehicle using infrared signal, to remotely control the motions (upward, backward, turing left or right, speeding up or down, and sending and receiving data). The vehicle is equipped with an ultrasound module so that it can detect the distance with other obstacles to avoid being crashed. Besides, the vehicle can sense the temperature and humidity of the environment, send back the results to the controller, and display them in the screen of the controller.

This is a happy memory of cooperation and creation a long time ago. I can still remember the happy lab and many talented guys that we worked together. However, I turned to research on communication theories and algorithms, so I did not continue working on SCM and implementations later on. Many details are forgotten and I cannot even make sure the codes still work well with the development of the community. One thing to mention that the comments and reports are all written in Chinese, so it is easier to understand an implement with Chinese background.

Prerequisits:

Hardware: AT89C51 SCM, LCD1602 screen, ISD1820 soundplayer, L298N motor mudule, HC-SR04 ultrasound module, HS0038 infrared mudule, DHT11 humudity and temperature sensor, etc.

Software: Keil IDE for coding and generating executable files

Language: c
