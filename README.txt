[P][I][G]
 o  n  e
 l  f  t
 y  o  t
 m  r  e
 o  m  r
 r  a
 p  t
 h  i  
 i  o
 c  n

This is my attempt to create dynamic polymorphism in C. I don't know how
practical this system is. I have tried to make the macros convenient, but C's
macro system is pretty limited.

The basis of the system is the pig_ty type. It is an opaque object whose type
information can be queried with the macro pig_info. The macro takes the name of
some registered information. The return value can be anything that is the size
of a pointer. Its type is the one registered with the information name given.

pig.h includes specific documentation.
