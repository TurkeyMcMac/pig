#include "pig.h"

#include <stdio.h>

PIG_TRAIT_SINGLE_FULL(print, print, int, (               self,       file),
                                          pig_object_ty *self, FILE *file);

int print_foo(pig_object_ty *self, FILE *file)
{
	return fprintf(file, "foo\n");
}

PIG_IMPLEMENT_SINGLE(print, foo, print_foo);

int main(void)
{
	return print(foo, NULL, stdout);
}
