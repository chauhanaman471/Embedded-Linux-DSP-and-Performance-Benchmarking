This file is for documentation of milestone 01 : Linux and Embedded Fundamentals
The objective of this milestone is to develop a c application which generate 100 numerical samples and save them in a text file using linux environment

Let say we have a temperature sensor that generates 100 samples, since we are not using any hardware for our learning phase initially, we will develop a c program first which will generate these numerical samples, we will save it in a text file using linux operations

lets say the sample formula we will use x[n] = 25.0 + 0.5n 
at time instant n = 0, value of sample x[0] = 25.0 + 0.5(0) = 25.0
at time instant n = 1, value of sample x[0] = 25.0 + 0.5(0) = 25.5

i.e. it increment by 0.5 with each time instant

what we need to install:
1) WSL - Windows Subsystems for Linux : It help to run linux kernel inside Windows
2) Ubuntu : Free operating system that is built on top of Linux


Linux commands with example:
cd ~ : Go to Linux home directory

pwd : show current directory
aman@Aman:~$ pwd
/home/aman

whoami : display linux username
aman@Aman:~$ whoami
aman

uname -r : display linux kernel version
aman@Aman:~$ uname -r
6.18.58.1-microsoft-standard-WSL2

ls -la : Shows all files, including hidden .git

