/* PIG: Polymorphic Information Getter */

/* Define a trait. This macro is followed by the information table (the body of a struct
 * definition.)
 * 
 *  trait: The name of the trait
 * */
#define PIG_TRAIT(trait) \
	const int const trait##_id = __COUNTER__; \
	struct _##trait; \
	typedef struct _##trait trait##_info_ty; \
	struct _##trait

/* Define a public method.
 *
 *  trait: The associated trait
 *  field_name: The name of the field this corresponds to
 *  method_name: The name to give the method
 *  ret: The return type of the method
 *  args: The list of arguments to pass to the inner method, enclosed by parentheses
 *  params: The comma-separated parameter list
 * */
#define PIG_METHOD_FULL(trait, field_name, method_name, ret, args, params...) \
	static inline ret method_name(const trait##_info_ty *_info_internal, params) \
	{ \
		return (*_info_internal->field_name) args; \
	}

/* Define a public method corresponding to the field <name> with the identifier <trait>_<name>.
 * */
#define PIG_METHOD(trait, name, ret, args, params...) \
	PIG_METHOD_FULL(trait, name, trait##_##name, ret, args, params)

/* Implement a trait.
 *
 *  trait: The trait to implement
 *  impl: The name of the implementation, initialized as a pointer to <trait>_info_ty
 *  methods: The list of field initializers not surrounded by braces
 * */
#define PIG_IMPLEMENT(trait, impl, methods...) \
	const trait##_info_ty const _##impl##_raw_dont_use = { methods }; \
	const trait##_info_ty *const impl = &_##impl##_raw_dont_use;

/* Define a trait with a single method.
 *
 *  trait: The name of the trait
 *  method_name: The name of the method
 *  ret: The method's return value
 *  args: The list of arguments to pass to the inner method, enclosed by parentheses
 *  params: The comma-separated parameter list
 * */
#define PIG_TRAIT_SINGLE_FULL(trait, method_name, ret, args, params...) \
	const int const trait##_id = __COUNTER__; \
	typedef int trait##_info_ty; \
	typedef ret (*trait##_method_ty)(params);\
	static inline ret method_name(const trait##_info_ty *_info_internal, params) \
	{ \
		return (*(ret (*)(params))_info_internal) args; \
	}

/* Define a trait with a single method whose identifier is <trait>_<method_name>.
 * */
#define PIG_TRAIT_SINGLE(trait, method_name, ret, args, params...) \
	PIG_TRAIT_SINGLE_FULL(trait, trait##_##method_name, ret, args, params)

/* Implement a trait with a single method.
 *
 *  trait: The trait to implement
 *  impl: The name of the implementation, initialized as a pointer to <trait>_info_ty
 *  method: The method implementation
 * */
#define PIG_IMPLEMENT_SINGLE(trait, impl, method) \
	const trait##_method_ty const _##impl##_raw_dont_use = method; \
	const trait##_info_ty *const impl = (trait##_info_ty *)method; 

/* An opaque Polymorphism Information Getter. A pig should be embedded in all structures using this
 * system, and a pointer to a pig should be passed as the `self` argument to methods.
 * */
typedef struct {
	void *(*get_info)(int trait_id);
} pig_ty;

/* Initialize a pig.
 * 
 *  self: The pig to initialize
 *  get_info: The method that the pig should use to get its information
 * */
static inline void pig_init(pig_ty *self, void *(*get_info)(int trait_id))
{
	self->get_info = get_info;
}

/* Query a pig's type information.
 *
 *  pig: The pig to ask
 *  trait: The trait to request information on
 *
 *  return value: A pointer to an implementation of the requested trait, where NULL indicates that
 *  an implementation of the trait requested could not be found
 * */
#define pig_info(pig, trait) ( (trait##_info_ty *)(*(pig)->get_info)(trait##_id) )

/* This is due to some strange casting which must be done. */
struct _pig_void_ptr_must_be_equal_in_size_to_function_ptr {
	int void_ptr_must_be_equal_in_size_to_function_ptr
		[(sizeof(void *) == sizeof(void (*)())) - 1];
};
