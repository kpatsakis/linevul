e1000e_parse_rxbufsize(E1000ECore *core)
{
    uint32_t rctl = core->mac[RCTL];

    memset(core->rxbuf_sizes, 0, sizeof(core->rxbuf_sizes));

    if (rctl & E1000_RCTL_DTYP_MASK) {
        uint32_t bsize;

        bsize = core->mac[PSRCTL] & E1000_PSRCTL_BSIZE0_MASK;
        core->rxbuf_sizes[0] = (bsize >> E1000_PSRCTL_BSIZE0_SHIFT) * 128;

        bsize = core->mac[PSRCTL] & E1000_PSRCTL_BSIZE1_MASK;
        core->rxbuf_sizes[1] = (bsize >> E1000_PSRCTL_BSIZE1_SHIFT) * 1024;

        bsize = core->mac[PSRCTL] & E1000_PSRCTL_BSIZE2_MASK;
        core->rxbuf_sizes[2] = (bsize >> E1000_PSRCTL_BSIZE2_SHIFT) * 1024;

        bsize = core->mac[PSRCTL] & E1000_PSRCTL_BSIZE3_MASK;
        core->rxbuf_sizes[3] = (bsize >> E1000_PSRCTL_BSIZE3_SHIFT) * 1024;
    } else if (rctl & E1000_RCTL_FLXBUF_MASK) {
        int flxbuf = rctl & E1000_RCTL_FLXBUF_MASK;
        core->rxbuf_sizes[0] = (flxbuf >> E1000_RCTL_FLXBUF_SHIFT) * 1024;
    } else {
        core->rxbuf_sizes[0] = e1000x_rxbufsize(rctl);
    }

    trace_e1000e_rx_desc_buff_sizes(core->rxbuf_sizes[0], core->rxbuf_sizes[1],
                                    core->rxbuf_sizes[2], core->rxbuf_sizes[3]);

    e1000e_calc_per_desc_buf_size(core);
}
