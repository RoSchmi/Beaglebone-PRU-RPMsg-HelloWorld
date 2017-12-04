# Beaglebone-PRU-RPMsg-HelloWorld
Exchange messages between PRU (Programmable Real-Time Unit) and Linux System using RemoteProc and RPMsg

This project runs on: Linux beaglebone 4.4.91-ti-r133 #1 SMP Tue Oct 10 05:18:08 UTC 2017 armv7l GNU/Linux

How to use:
Copy the content of this repository in the folder debian@beaglebone:~/PruProgs/Pru_RPMsg_Hello/

(if you use another folder, change the content of the variable CODE_ROOT in the file Makefile accordingly)

Navigate to the folder ../Pru_RPMsg_Hello/

Type:
sudo make clean        // (to delete the old executable files)
sudo make install -B   // (to compile and install the programs for PRU0 and PRU1)
sudo make -B           // (to compile the Linux user space program)
sudo ./hello           // (to start the Linux user space program)

The user space program hello sends a message to each PRU from where the message is returned and printed to the console.

This project is based on the TI PRU examples and the Project
Beaglebone: remoteproc "Hello,World" by Andrew B. Wright
http://theduchy.ualr.edu/?p=996

There were problems to run the program on the latest debian 2017-10-10 Stretch IoT build and the latest TI pru-software-support-package.
Alex Bagehot managed to get it running with the latest distributions
https://groups.google.com/forum/#!category-topic/beagleboard/support/4P9NdglojBo

His recommendations proved to work.
