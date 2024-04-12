static bool arg_type_is_refcounted(enum bpf_arg_type type)
{
	return type == ARG_PTR_TO_SOCKET;
}
