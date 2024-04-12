NTSTATUS smb1cli_req_chain_submit(struct tevent_req **reqs, int num_reqs)
{
	struct smbXcli_req_state *first_state =
		tevent_req_data(reqs[0],
		struct smbXcli_req_state);
	struct smbXcli_req_state *state;
	size_t wct_offset;
	size_t chain_padding = 0;
	int i, iovlen;
	struct iovec *iov = NULL;
	struct iovec *this_iov;
	NTSTATUS status;
	ssize_t nbt_len;

	if (num_reqs == 1) {
		return smb1cli_req_writev_submit(reqs[0], first_state,
						 first_state->smb1.iov,
						 first_state->smb1.iov_count);
	}

	iovlen = 0;
	for (i=0; i<num_reqs; i++) {
		if (!tevent_req_is_in_progress(reqs[i])) {
			return NT_STATUS_INTERNAL_ERROR;
		}

		state = tevent_req_data(reqs[i], struct smbXcli_req_state);

		if (state->smb1.iov_count < 4) {
			return NT_STATUS_INVALID_PARAMETER_MIX;
		}

		if (i == 0) {
			/*
			 * The NBT and SMB header
			 */
			iovlen += 2;
		} else {
			/*
			 * Chain padding
			 */
			iovlen += 1;
		}

		/*
		 * words and bytes
		 */
		iovlen += state->smb1.iov_count - 2;
	}

	iov = talloc_zero_array(first_state, struct iovec, iovlen);
	if (iov == NULL) {
		return NT_STATUS_NO_MEMORY;
	}

	first_state->smb1.chained_requests = (struct tevent_req **)talloc_memdup(
		first_state, reqs, sizeof(*reqs) * num_reqs);
	if (first_state->smb1.chained_requests == NULL) {
		TALLOC_FREE(iov);
		return NT_STATUS_NO_MEMORY;
	}

	wct_offset = HDR_WCT;
	this_iov = iov;

	for (i=0; i<num_reqs; i++) {
		size_t next_padding = 0;
		uint16_t *vwv;

		state = tevent_req_data(reqs[i], struct smbXcli_req_state);

		if (i < num_reqs-1) {
			if (!smb1cli_is_andx_req(CVAL(state->smb1.hdr, HDR_COM))
			    || CVAL(state->smb1.hdr, HDR_WCT) < 2) {
				TALLOC_FREE(iov);
				TALLOC_FREE(first_state->smb1.chained_requests);
				return NT_STATUS_INVALID_PARAMETER_MIX;
			}
		}

		wct_offset += smbXcli_iov_len(state->smb1.iov+2,
					      state->smb1.iov_count-2) + 1;
		if ((wct_offset % 4) != 0) {
			next_padding = 4 - (wct_offset % 4);
		}
		wct_offset += next_padding;
		vwv = state->smb1.vwv;

		if (i < num_reqs-1) {
			struct smbXcli_req_state *next_state =
				tevent_req_data(reqs[i+1],
				struct smbXcli_req_state);
			SCVAL(vwv+0, 0, CVAL(next_state->smb1.hdr, HDR_COM));
			SCVAL(vwv+0, 1, 0);
			SSVAL(vwv+1, 0, wct_offset);
		} else if (smb1cli_is_andx_req(CVAL(state->smb1.hdr, HDR_COM))) {
			/* properly end the chain */
			SCVAL(vwv+0, 0, 0xff);
			SCVAL(vwv+0, 1, 0xff);
			SSVAL(vwv+1, 0, 0);
		}

		if (i == 0) {
			/*
			 * The NBT and SMB header
			 */
			this_iov[0] = state->smb1.iov[0];
			this_iov[1] = state->smb1.iov[1];
			this_iov += 2;
		} else {
			/*
			 * This one is a bit subtle. We have to add
			 * chain_padding bytes between the requests, and we
			 * have to also include the wct field of the
			 * subsequent requests. We use the subsequent header
			 * for the padding, it contains the wct field in its
			 * last byte.
			 */
			this_iov[0].iov_len = chain_padding+1;
			this_iov[0].iov_base = (void *)&state->smb1.hdr[
				sizeof(state->smb1.hdr) - this_iov[0].iov_len];
			memset(this_iov[0].iov_base, 0, this_iov[0].iov_len-1);
			this_iov += 1;
		}

		/*
		 * copy the words and bytes
		 */
		memcpy(this_iov, state->smb1.iov+2,
		       sizeof(struct iovec) * (state->smb1.iov_count-2));
		this_iov += state->smb1.iov_count - 2;
		chain_padding = next_padding;
	}

	nbt_len = iov_buflen(&iov[1], iovlen-1);
	if ((nbt_len == -1) || (nbt_len > first_state->conn->smb1.max_xmit)) {
		TALLOC_FREE(iov);
		TALLOC_FREE(first_state->smb1.chained_requests);
		return NT_STATUS_INVALID_PARAMETER_MIX;
	}

	status = smb1cli_req_writev_submit(reqs[0], first_state, iov, iovlen);
	if (!NT_STATUS_IS_OK(status)) {
		TALLOC_FREE(iov);
		TALLOC_FREE(first_state->smb1.chained_requests);
		return status;
	}

	return NT_STATUS_OK;
}
