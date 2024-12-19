# Potentiometer Password Verifier

This is a circuit that uses a potentiometer as a form of input, in order to modify a 9 digit array of numbers.
The 9 digit array of numbers can be submitted to see if it is equal to the true password. The "password" is hardcoded in the source code so that it is easy to change (`int correctDigits[9] = ...`). 
This should not be used for an actual password verifier though since it has no hashing or encryption. It was made as a proof-of-concept for using a potentiometer as a form of input.

## Usage: 
1. Use the potentiometer dial to move thru the digits (left or right) during selection mode (solid yellow LED)
2. Use the potentiometer to edit the selected digit during editing mode (blinking yellow LED).
3. To change modes, press the upper push-button
   * Blinking Yellow LED - editing mode
   * Solid Yellow LED - selection mode
4. Once the digits have been modified as desired, press the lower push button to submit the password.
5. To reset to try again, press the reset button on the Arduino.

## Components:
* 1x Potentiometer
* 2x Push buttons
* 1x Yellow LED
* 2x 10K ohm resistor
* 1x 220 ohm resistor
* 1x Arduino Uno R3
* 1x 20x4 LCD (w/ I2C chip)
* Breadboard and wires.

## Gallery 
<img src="gallery/circuit_digits.jpg" alt="gallery/circuit_digits.jpg" width="50%" height="50%">
<img src="gallery/circuit_digits.jpg" alt="gallery/circuit_access_denied.jpg" width="50%" height="50%">
<img src="gallery/circuit_digits.jpg" alt="gallery/circuit_access_granted.jpg" width="50%" height="50%">
