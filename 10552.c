gssint_unwrap_aead_iov_shim(gss_mechanism mech,
			    OM_uint32 *minor_status,
			    gss_ctx_id_t context_handle,
			    gss_buffer_t input_message_buffer,
			    gss_buffer_t input_assoc_buffer,
			    gss_buffer_t output_payload_buffer,
			    int *conf_state,
			    gss_qop_t *qop_state)
{
    OM_uint32		    status;
    gss_iov_buffer_desc	    iov[3];
    int			    i = 0;

    iov[i].type = GSS_IOV_BUFFER_TYPE_STREAM;
    iov[i].buffer = *input_message_buffer;
    i++;

    if (input_assoc_buffer != NULL) {
	iov[i].type = GSS_IOV_BUFFER_TYPE_SIGN_ONLY;
	iov[i].buffer = *input_assoc_buffer;
	i++;
    }

    iov[i].type = GSS_IOV_BUFFER_TYPE_DATA | GSS_IOV_BUFFER_FLAG_ALLOCATE;
    iov[i].buffer.value = NULL;
    iov[i].buffer.length = 0;
    i++;

    assert(mech->gss_unwrap_iov);

    status = mech->gss_unwrap_iov(minor_status, context_handle, conf_state,
				  qop_state, iov, i);
    if (status == GSS_S_COMPLETE) {
	*output_payload_buffer = iov[i - 1].buffer;
    } else {
	OM_uint32 minor;

	map_error(minor_status, mech);

	if (iov[i - 1].type & GSS_IOV_BUFFER_FLAG_ALLOCATED) {
	    gss_release_buffer(&minor, &iov[i - 1].buffer);
	    iov[i - 1].type &= ~(GSS_IOV_BUFFER_FLAG_ALLOCATED);
	}
    }

    return status;
}
