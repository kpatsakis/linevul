void red_channel_client_begin_send_message(RedChannelClient *rcc)
{
    SpiceMarshaller *m = rcc->send_data.marshaller;

    if (rcc->send_data.header.get_msg_type(&rcc->send_data.header) == 0) {
        spice_printerr("BUG: header->type == 0");
        return;
    }

    /* canceling the latency test timer till the nework is idle */
    red_channel_client_cancel_ping_timer(rcc);

    spice_marshaller_flush(m);
    rcc->send_data.size = spice_marshaller_get_total_size(m);
    rcc->send_data.header.set_msg_size(&rcc->send_data.header,
                                       rcc->send_data.size - rcc->send_data.header.header_size);
    rcc->ack_data.messages_window++;
    rcc->send_data.last_sent_serial = rcc->send_data.serial;
    rcc->send_data.header.data = NULL; /* avoid writing to this until we have a new message */
    red_channel_client_send(rcc);
}
