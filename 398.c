static void pl022_write(void *opaque, hwaddr offset,
                        uint64_t value, unsigned size)
{
    PL022State *s = (PL022State *)opaque;

    switch (offset) {
    case 0x00: /* CR0 */
        s->cr0 = value;
        /* Clock rate and format are ignored.  */
        s->bitmask = (1 << ((value & 15) + 1)) - 1;
        break;
    case 0x04: /* CR1 */
        s->cr1 = value;
        if ((s->cr1 & (PL022_CR1_MS | PL022_CR1_SSE))
                   == (PL022_CR1_MS | PL022_CR1_SSE)) {
            BADF("SPI slave mode not implemented\n");
        }
        pl022_xfer(s);
        break;
    case 0x08: /* DR */
        if (s->tx_fifo_len < 8) {
            DPRINTF("TX %02x\n", (unsigned)value);
            s->tx_fifo[s->tx_fifo_head] = value & s->bitmask;
            s->tx_fifo_head = (s->tx_fifo_head + 1) & 7;
            s->tx_fifo_len++;
            pl022_xfer(s);
        }
        break;
    case 0x10: /* CPSR */
        /* Prescaler.  Ignored.  */
        s->cpsr = value & 0xff;
        break;
    case 0x14: /* IMSC */
        s->im = value;
        pl022_update(s);
        break;
    case 0x20: /* DMACR */
        if (value) {
            qemu_log_mask(LOG_UNIMP, "pl022: DMA not implemented\n");
        }
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "pl022_write: Bad offset %x\n", (int)offset);
    }
}
