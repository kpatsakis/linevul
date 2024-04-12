static BOOLEAN btm_sec_queue_mx_request (BD_ADDR bd_addr,  UINT16 psm,  BOOLEAN is_orig,
                                         UINT32 mx_proto_id, UINT32 mx_chan_id,
                                         tBTM_SEC_CALLBACK *p_callback, void *p_ref_data)
{
    tBTM_SEC_QUEUE_ENTRY    *p_e;

    p_e = (tBTM_SEC_QUEUE_ENTRY *)GKI_getbuf (sizeof(tBTM_SEC_QUEUE_ENTRY));

 if (p_e)
 {
        p_e->psm            = psm;
        p_e->is_orig        = is_orig;
        p_e->p_callback     = p_callback;
        p_e->p_ref_data     = p_ref_data;
        p_e->mx_proto_id    = mx_proto_id;
        p_e->mx_chan_id     = mx_chan_id;

        memcpy (p_e->bd_addr, bd_addr, BD_ADDR_LEN);

        BTM_TRACE_EVENT ("btm_sec_queue_mx_request() PSM: 0x%04x  Is_Orig: %u  mx_proto_id: %u  mx_chan_id: %u",
                          psm, is_orig, mx_proto_id, mx_chan_id);

        GKI_enqueue (&btm_cb.sec_pending_q, p_e);

 return(TRUE);
 }

 return(FALSE);
}
