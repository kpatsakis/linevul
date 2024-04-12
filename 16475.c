val_wrap_iov_args(
    OM_uint32 *minor_status,
    gss_ctx_id_t context_handle,
    int conf_req_flag,
    gss_qop_t qop_req,
    int *conf_state,
    gss_iov_buffer_desc *iov,
    int iov_count)
{

    /* Initialize outputs. */

    if (minor_status != NULL)
	*minor_status = 0;

    /* Validate arguments. */

    if (minor_status == NULL)
	return (GSS_S_CALL_INACCESSIBLE_WRITE);

    if (context_handle == GSS_C_NO_CONTEXT)
	return (GSS_S_CALL_INACCESSIBLE_READ | GSS_S_NO_CONTEXT);

    if (iov == GSS_C_NO_IOV_BUFFER)
	return (GSS_S_CALL_INACCESSIBLE_READ);

    return (GSS_S_COMPLETE);
}
