static void i6300esb_realize(PCIDevice *dev, Error **errp)
{
    I6300State *d = WATCHDOG_I6300ESB_DEVICE(dev);

    i6300esb_debug("I6300State = %p\n", d);

    d->timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, i6300esb_timer_expired, d);
    d->previous_reboot_flag = 0;

    memory_region_init_io(&d->io_mem, OBJECT(d), &i6300esb_ops, d,
                          "i6300esb", 0x10);
    pci_register_bar(&d->dev, 0, 0, &d->io_mem);
     /* qemu_register_coalesced_mmio (addr, 0x10); ? */
 }
