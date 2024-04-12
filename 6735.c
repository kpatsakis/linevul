static int ahci_state_post_load(void *opaque, int version_id)
{
    int i;
    struct AHCIDevice *ad;
    AHCIState *s = opaque;

    for (i = 0; i < s->ports; i++) {
        ad = &s->dev[i];
        AHCIPortRegs *pr = &ad->port_regs;

        map_page(&ad->lst,
                 ((uint64_t)pr->lst_addr_hi << 32) | pr->lst_addr, 1024);
        map_page(&ad->res_fis,
                 ((uint64_t)pr->fis_addr_hi << 32) | pr->fis_addr, 256);
        /*
         * All pending i/o should be flushed out on a migrate. However,
         * we might not have cleared the busy_slot since this is done
         * in a bh. Also, issue i/o against any slots that are pending.
         */
        if ((ad->busy_slot != -1) &&
            !(ad->port.ifs[0].status & (BUSY_STAT|DRQ_STAT))) {
            pr->cmd_issue &= ~(1 << ad->busy_slot);
            ad->busy_slot = -1;
        }
        check_cmd(s, i);
    }

    return 0;
}
