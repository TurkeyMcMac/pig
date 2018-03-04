/* PIG: Polymorphic Information Getter */

#ifndef _PIG_H /* Header guard */

#define _PIG_H

#include <stddef.h>

/* Register some info under a name.
 *
 *  name: The name to register
 *  type: The type which will be returned when this info is requested through pig_info
 * */
#define PIG_REGISTER(name, type) \
	static const char _pig_##name##_info_id[__COUNTER__ + 1]; \
	typedef type _pig_##name##_ty

/* Cast a function pointer to a suitable return value for a pig's info getter function.
 *
 *  info: The name of the info in question
 * */
#define pig_func(info) ((const void *)(ptrdiff_t)info)

/* Get the unique identifier of some registered info.
 *
 *  info: The name of the info in question
 * 
 *  return value: The associated identifier
 * */
#define pig_id(info) (sizeof(_pig_##info##_info_id) - 1)

/* An opaque Polymorphism Information Getter. A pig should be embedded in all structures using this
 * system, and a pointer to a pig can be passed as the `self` argument to methods.
 * */
typedef struct {
	const void *(*get_info)(int info_id);
} pig_ty;

/* Initialize a pig.
 * 
 *  self: The pig to initialize
 *  get_info: The method that the pig should use to get its information
 * */
void pig_init(pig_ty *self, const void *(*get_info)(int trait_id));

/* Query a pig's type information.
 *
 *  pig: The pig to ask
 *  info: The name of the info to request
 *
 *  return value: A pointer to an instance of the requested info, where NULL indicates that no
 *  instance could be found
 * */
#define pig_info(pig, info) ( (_pig_##info##_ty)(ptrdiff_t)(*(pig)->get_info)(pig_id(info)) )

/* This is due to some strange casting which must be done. */
struct _pig_void_ptr_must_be_equal_in_size_to_function_ptr {
	int void_ptr_must_be_equal_in_size_to_function_ptr
		[(sizeof(void *) == sizeof(void (*)())) * 2 - 1];
};

#endif /* End header guard */
