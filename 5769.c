e1000e_txdesc_writeback(E1000ECore *core, dma_addr_t base,
                        struct e1000_tx_desc *dp, bool *ide, int queue_idx)
{
    uint32_t txd_upper, txd_lower = le32_to_cpu(dp->lower.data);

    if (!(txd_lower & E1000_TXD_CMD_RS) &&
        !(core->mac[IVAR] & E1000_IVAR_TX_INT_EVERY_WB)) {
        return 0;
    }

    *ide = (txd_lower & E1000_TXD_CMD_IDE) ? true : false;

    txd_upper = le32_to_cpu(dp->upper.data) | E1000_TXD_STAT_DD;

    dp->upper.data = cpu_to_le32(txd_upper);
    pci_dma_write(core->owner, base + ((char *)&dp->upper - (char *)dp),
                  &dp->upper, sizeof(dp->upper));
    return e1000e_tx_wb_interrupt_cause(core, queue_idx);
}
