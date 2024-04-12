int reset_airo_card( struct net_device *dev )
{
	int i;
	struct airo_info *ai = dev->ml_priv;

	if (reset_card (dev, 1))
		return -1;

	if ( setup_card(ai, dev->dev_addr, 1 ) != SUCCESS ) {
		airo_print_err(dev->name, "MAC could not be enabled");
		return -1;
	}
	airo_print_info(dev->name, "MAC enabled %pM", dev->dev_addr);
	/* Allocate the transmit buffers if needed */
	if (!test_bit(FLAG_MPI,&ai->flags))
		for( i = 0; i < MAX_FIDS; i++ )
			ai->fids[i] = transmit_allocate (ai,AIRO_DEF_MTU,i>=MAX_FIDS/2);

	enable_interrupts( ai );
	netif_wake_queue(dev);
	return 0;
}
