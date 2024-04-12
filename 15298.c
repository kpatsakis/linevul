TEE_Result syscall_cryp_obj_close(unsigned long obj)
{
	TEE_Result res;
	struct tee_ta_session *sess;
	struct tee_obj *o;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_obj_get(to_user_ta_ctx(sess->ctx),
			  tee_svc_uref_to_vaddr(obj), &o);
	if (res != TEE_SUCCESS)
		return res;

	/*
	 * If it's busy it's used by an operation, a client should never have
	 * this handle.
	 */
	if (o->busy)
		return TEE_ERROR_ITEM_NOT_FOUND;

	tee_obj_close(to_user_ta_ctx(sess->ctx), o);
	return TEE_SUCCESS;
}
