svc_rdma_parse_connect_private(struct svcxprt_rdma *newxprt,
			       struct rdma_conn_param *param)
{
	const struct rpcrdma_connect_private *pmsg = param->private_data;

	if (pmsg &&
	    pmsg->cp_magic == rpcrdma_cmp_magic &&
	    pmsg->cp_version == RPCRDMA_CMP_VERSION) {
		newxprt->sc_snd_w_inv = pmsg->cp_flags &
					RPCRDMA_CMP_F_SND_W_INV_OK;

		dprintk("svcrdma: client send_size %u, recv_size %u "
			"remote inv %ssupported\n",
			rpcrdma_decode_buffer_size(pmsg->cp_send_size),
			rpcrdma_decode_buffer_size(pmsg->cp_recv_size),
			newxprt->sc_snd_w_inv ? "" : "un");
	}
}
