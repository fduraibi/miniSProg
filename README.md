miniSProg
=========

GUI programmer for miniSpartan6+ development board

The application uses xc3sprog to function, so you need to have a working
copy of that application first, check xc3sprog website to learn how 
http://xc3sprog.sourceforge.net/

---------
# How to run/compile this project?

This project is developed using Qt Creator, and should work with Qt4 and
above (tested with both Qt4 and Qt5 on Linux and Windows). Simply open the 
project from Qt Creator and make sure you have Qt installed then click on Build 
then Run (or Run directly and will build it for you if it need to).


---------
# How to use it?

When you start up the application it will look into its current folder to find 
the xc3sprog execuatable, if it is not there then you have to tell it where to 
find that file (it has to be with that exact name). Next you need to select the 
bit file (must have ".bit" extension) then click on 'Program'. The details 
console will show the result, check it to see if it was successful or it 
there was any error.


---------
# Explaining some possible errors

- "Permission denied" + "Failed to start"
(Linux only) Make sure the 'xc3sprog' has the execute permission set for your 
user.

- When compiling xc3sprog you might get "fatal error: ftdi.h: No such file or directory"
Make sure you have (libftdi 0.x) installed, some new Linux distributions have 
moved to (libftdi 1.x) if that is the case with your distribution then fix the 
source code of xc3sprog to use the new library instead.