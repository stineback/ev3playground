# Gyrofeedback

## DESCRITPION
When turning the robot, the motor is turning accordingly, so the arm will stay in the same position. It uses the feedback from a gyrometer on the arm and PD-controller has been implemented to achive this.

## ARGUMENTS
* -P#: sets the proportional coefficient to #.
* -D#: sets the derived coefficient to #.
* -S#: sets the set point of the arm to #.
* -C#: sets the duty cycle of the motor to #.
* -G#: shows graph where horizontal is error according to set point and vertical is time. The range of error is from -# to #.