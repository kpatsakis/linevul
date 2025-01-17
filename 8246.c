pvscsi_on_cmd_setup_msg_ring(PVSCSIState *s)
{
    PVSCSICmdDescSetupMsgRing *rc =
        (PVSCSICmdDescSetupMsgRing *) s->curr_cmd_data;

    trace_pvscsi_on_cmd_arrived("PVSCSI_CMD_SETUP_MSG_RING");

    if (!s->use_msg) {
        return PVSCSI_COMMAND_PROCESSING_FAILED;
    }

    if (s->rings_info_valid) {
        if (pvscsi_ring_init_msg(&s->rings, rc) < 0) {
            return PVSCSI_COMMAND_PROCESSING_FAILED;
        }
        s->msg_ring_info_valid = TRUE;
    }
    return sizeof(PVSCSICmdDescSetupMsgRing) / sizeof(uint32_t);
}
