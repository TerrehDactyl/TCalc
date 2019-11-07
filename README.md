TCalc
-
What is Tcalc?
-
Tcalc is a multifunction calculator written in C using the GTK 3.0 library, modeled after the KDE product Kcalc.

Getting started!
-
Compile using 
gcc -Wall -g -lm tcalc.c -o tcalc `pkg-config --cflags --libs gtk+-3.0`
run with ./tcalc

Known bugs
-
1) Redo gives unexpected results.
2) When using any of the preset constants, only 6 decimal spaces are shown
but 11 decimal places are used in calculations.
