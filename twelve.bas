100 rem Copyright 2022 by Jim Lawless
110 rem MIT/X11 license
120 let d% = 1
130 print "On the ";
140 if d% = 1
150   print "first ";
160 if d% = 2
170   print "second ";
180 if d% = 3
190   print "third ";
200 if d% = 4
210   print "fourth ";
220 if d% = 5
230   print "fifth ";
240 if d% = 6
250   print "sixth ";
260 if d% = 7
270   print "seventh ";
280 if d% = 8
290   print "eighth ";
300 if d% = 9
310   print "ninth ";
320 if d% = 10
330   print "tenth ";
340 if d% = 11
350   print "eleventh ";
360 if d% = 12
370   print "twelfth ";
380 print "day of Christmas, my true love gave to me:"
390 if d% > 11
400   print "Twelve drummers drumming,"
410 if d% > 10
420   print "Eleven pipers piping,"
430 if d% > 9
440   print "Ten lords a leaping,"
450 if d% > 8
460   print "Nine ladies dancing,"
470 if d% > 7
480   print "Eight maids a milking,"
490 if d% > 6
500   print "Seven swans a swimming,"
510 if d% > 5
520   print "Six geese a laying,"
530 if d% > 4
540   print "Fiiiiiive golden riiiinngs..."
550 if d% > 3
560   print "Four calling birds,"
570 if d% > 2
580   print "Three French hens,"
590 if d% > 1
600   print      "Two turtle doves,"
610 if d% > 1
620   print "And, a ";
630 if d% = 1
640   print "A ";
650 print "partridge in a pear tree."
660 print
670 add d% 1
680 if d% <> 13
690   goto 130