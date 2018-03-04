#include "pig.h"

void pig_init(pig_ty *self, const void *(*get_info)(int trait_id))
{
	self->get_info = get_info;
}

