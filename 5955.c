void handle_rc_metamsg_cmd (tBTA_AV_META_MSG *pmeta_msg)
{
 /* Parse the metamsg command and pass it on to BTL-IFS */
    UINT8             scratch_buf[512] = {0};
    tAVRC_COMMAND    avrc_command = {0};
    tAVRC_STS status;

    BTIF_TRACE_EVENT("+ %s", __FUNCTION__);

 if (pmeta_msg->p_msg->hdr.opcode != AVRC_OP_VENDOR)
 {
        BTIF_TRACE_WARNING("Invalid opcode: %x", pmeta_msg->p_msg->hdr.opcode);
 return;
 }
 if (pmeta_msg->len < 3)
 {
        BTIF_TRACE_WARNING("Invalid length.Opcode: 0x%x, len: 0x%x", pmeta_msg->p_msg->hdr.opcode,
            pmeta_msg->len);
 return;
 }

 if (pmeta_msg->code >= AVRC_RSP_NOT_IMPL)
 {
#if (AVRC_ADV_CTRL_INCLUDED == TRUE)
{
 rc_transaction_t *transaction=NULL;
     transaction=get_transaction_by_lbl(pmeta_msg->label);
 if(NULL!=transaction)
 {
        handle_rc_metamsg_rsp(pmeta_msg);
 }
 else
 {
         BTIF_TRACE_DEBUG("%s:Discard vendor dependent rsp. code: %d label:%d.",
             __FUNCTION__, pmeta_msg->code, pmeta_msg->label);
 }
 return;
}
#else
{
        BTIF_TRACE_DEBUG("%s:Received vendor dependent rsp. code: %d len: %d. Not processing it.",
            __FUNCTION__, pmeta_msg->code, pmeta_msg->len);
 return;
}
#endif
 }

    status=AVRC_ParsCommand(pmeta_msg->p_msg, &avrc_command, scratch_buf, sizeof(scratch_buf));
    BTIF_TRACE_DEBUG("Received vendor command.code,PDU and label: %d, %d,%d",pmeta_msg->code,
                       avrc_command.cmd.pdu, pmeta_msg->label);

 if (status != AVRC_STS_NO_ERROR)
 {
 /* return error */
        BTIF_TRACE_WARNING("%s: Error in parsing received metamsg command. status: 0x%02x",
            __FUNCTION__, status);
        send_reject_response(pmeta_msg->rc_handle, pmeta_msg->label, avrc_command.pdu, status);
 }
 else
 {
 /* if RegisterNotification, add it to our registered queue */

 if (avrc_command.cmd.pdu == AVRC_PDU_REGISTER_NOTIFICATION)
 {
            UINT8 event_id = avrc_command.reg_notif.event_id;
            BTIF_TRACE_EVENT("%s:New register notification received.event_id:%s,label:0x%x,code:%x",
            __FUNCTION__,dump_rc_notification_event_id(event_id), pmeta_msg->label,pmeta_msg->code);
            btif_rc_cb.rc_notif[event_id-1].bNotify = TRUE;
            btif_rc_cb.rc_notif[event_id-1].label = pmeta_msg->label;

 if(event_id == AVRC_EVT_UIDS_CHANGE)
 {
                handle_uid_changed_notification(pmeta_msg, &avrc_command);
 return;
 }

 }

        BTIF_TRACE_EVENT("%s: Passing received metamsg command to app. pdu: %s",
            __FUNCTION__, dump_rc_pdu(avrc_command.cmd.pdu));

 /* Since handle_rc_metamsg_cmd() itself is called from
            *btif context, no context switching is required. Invoke
            * btif_rc_upstreams_evt directly from here. */
        btif_rc_upstreams_evt((uint16_t)avrc_command.cmd.pdu, &avrc_command, pmeta_msg->code,
                               pmeta_msg->label);
 }
}
