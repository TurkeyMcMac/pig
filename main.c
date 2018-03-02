#include "pig.h"

#include <stdio.h>

PIG_TRAIT_SINGLE(print, to, int, (      file,                self),
                                  FILE *file, pig_object_ty *self);

int print_foo(FILE *file)
{
	return fprintf(file, "foo\n");
}

PIG_IMPLEMENT_SINGLE(print, foo, print_foo);
