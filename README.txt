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

This is my attempt to create dynamic polymorphism in C. I don't know how practical this system is. I
have tried to make the macros convenient, but C's macro system is pretty limited.

The basis of the system is the pig_ty type. It is an opaque object whose type information can be
queried with the macro pig_info. The macro takes the name of a trait. A trait is basically a struct
with some other hidden information. When passed a trait identifier, a pig gives back a pointer
which hides type information such as method implementations. The data given can then be used to
perform various actions through method calls, probably including the specific pig which provided it.

pig.h includes several macros for defining, implementing, and using traits with one or multiple
methods. Specific documentation can be found there.
