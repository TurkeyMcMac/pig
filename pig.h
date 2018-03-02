#define PIG_TRAIT(trait) \
	const int const trait##_id = __COUNTER__; \
	struct _##trait; \
	typedef struct _##trait trait##_info_ty; \
	struct _##trait

#define PIG_METHOD(trait, name, ret, arg_names, args_declare...) \
	static inline ret trait##_##name(trait##_info_ty *_info_internal, args_declare) \
	{ \
		return (*_info_internal->name) arg_names; \
	}

#define PIG_IMPLEMENT(trait, impl, methods...) \
	const trait##_info_ty const _##impl##_raw_dont_use = { methods }; \
	const trait##_info_ty *const impl = &_##impl##_raw_dont_use;

#define PIG_TRAIT_SINGLE(trait, method_name, ret, arg_names, args_declare...) \
	const int const trait##_id = __COUNTER__; \
	typedef int trait##_info_ty; \
	typedef ret (*trait##_method_ty)(args_declare);\
	static inline ret trait##_##method_name(trait##_info_ty *_info_internal, args_declare) \
	{ \
		return (*(ret (*)(args_declare))_info_internal) arg_names; \
	}

#define PIG_IMPLEMENT_SINGLE(trait, impl, method) \
	const trait##_method_ty const _##impl##_raw_dont_use = method; \
	const trait##_info_ty *const impl = (trait##_info_ty *)method; \

typedef struct {
	void *(*get_info)(int trait_id);
} pig_object_ty;

static inline void pig_object_init(pig_object_ty *self, void *(*get_info)(int trait_id))
{
	self->get_info = get_info;
}

#define pig_info(obj, trait) ( (trait##_info_ty *)(*(obj)->get_info)(trait##_id) )

/* This is due to some strange casting which must be done. */
struct _pig_void_ptr_must_be_equal_in_size_to_function_ptr {
	int void_ptr_must_be_equal_in_size_to_function_ptr
		[(sizeof(void *) == sizeof(void (*)())) - 1];
};
