#include "pig.h"

#include <stdio.h>

struct animal_info {
	int (*get_leg_num)(pig_ty *self);
	int (*get_arm_num)(pig_ty *self);
};
PIG_REGISTER(animal, const struct animal_info *);

typedef size_t (*iterator_next_ty)(pig_ty *self, void *dest);
PIG_REGISTER(iterator, iterator_next_ty);

int get_leg_num_impl(pig_ty *self)
{
	return 2;
}

int get_arm_num_impl(pig_ty *self)
{
	return 2;
}

const struct animal_info info_animal = {
	.get_leg_num = get_leg_num_impl,
	.get_arm_num = get_arm_num_impl,
};

size_t next_impl(pig_ty *self, void *dest)
{
	return 0;
}

const void *impl_list(int info_id)
{
	switch (info_id) {
	case pig_id(iterator):
		return pig_cast(next_impl);
	case pig_id(animal):
		return &info_animal;
	default:
		return NULL;
	}
}

int main(void)
{
	pig_ty p;
	pig_init(&p, impl_list);
	const struct animal_info *animal = pig_info(&p, animal);
	iterator_next_ty next = pig_info(&p, iterator);
	animal->get_leg_num(&p);
	next(&p, NULL);
}
