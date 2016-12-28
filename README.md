# ev3playground

## SETUP
Setup bluetooth connection to the EV3 as descriped here: http://www.ev3dev.org/docs/tutorials/connecting-to-the-internet-via-bluetooth/

Setup ev3dev with Docker as descriped here: http://www.ev3dev.org/docs/tutorials/using-docker-to-cross-compile/

Source the setup.sh script, so the build and copy scripts in bin can be used

## SSH
### Login in to ev3:
ssh robot@ev3dev.local
password: maker
 
### Copy program to ev3:
scp hello robot@ev3dev.local:~/workspace/
password: maker

## SCRIPTS
### ev3build
-Startups a temporary docker container and runs the makefile for the current folder

### ev3cp source_file
-Copies the source_file from host to the EV3. The filename must be given as argument.

## WORKFLOW:
1. Navigate to the folder with the project which should be compiled and run
2. Run ev3build
3. Turn on the EV3
4. Run ev3cp where the argument is the compiled file
5. On EV3 navigate to the workspacefolder
6. Select the copied file on the EV3 to run it


