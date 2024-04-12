static u16 setup_card(struct airo_info *ai, u8 *mac, int lock)
{
	Cmd cmd;
	Resp rsp;
	int status;
	SsidRid mySsid;
	__le16 lastindex;
	WepKeyRid wkr;
	int rc;

	memset( &mySsid, 0, sizeof( mySsid ) );
	kfree (ai->flash);
	ai->flash = NULL;

	/* The NOP is the first step in getting the card going */
	cmd.cmd = NOP;
	cmd.parm0 = cmd.parm1 = cmd.parm2 = 0;
	if (lock && down_interruptible(&ai->sem))
		return ERROR;
	if ( issuecommand( ai, &cmd, &rsp ) != SUCCESS ) {
		if (lock)
			up(&ai->sem);
		return ERROR;
	}
	disable_MAC( ai, 0);

	if (!test_bit(FLAG_MPI,&ai->flags)) {
		cmd.cmd = CMD_ENABLEAUX;
		if (issuecommand(ai, &cmd, &rsp) != SUCCESS) {
			if (lock)
				up(&ai->sem);
			airo_print_err(ai->dev->name, "Error checking for AUX port");
			return ERROR;
		}
		if (!aux_bap || rsp.status & 0xff00) {
			ai->bap_read = fast_bap_read;
			airo_print_dbg(ai->dev->name, "Doing fast bap_reads");
		} else {
			ai->bap_read = aux_bap_read;
			airo_print_dbg(ai->dev->name, "Doing AUX bap_reads");
		}
	}
	if (lock)
		up(&ai->sem);
	if (ai->config.len == 0) {
		int i;
		tdsRssiRid rssi_rid;
		CapabilityRid cap_rid;

		kfree(ai->APList);
		ai->APList = NULL;
		kfree(ai->SSID);
		ai->SSID = NULL;
		status = readConfigRid(ai, lock);
		if ( status != SUCCESS ) return ERROR;

		status = readCapabilityRid(ai, &cap_rid, lock);
		if ( status != SUCCESS ) return ERROR;

		status = PC4500_readrid(ai,RID_RSSI,&rssi_rid,sizeof(rssi_rid),lock);
		if ( status == SUCCESS ) {
			if (ai->rssi || (ai->rssi = kmalloc(512, GFP_KERNEL)) != NULL)
				memcpy(ai->rssi, (u8*)&rssi_rid + 2, 512); /* Skip RID length member */
		}
		else {
			kfree(ai->rssi);
			ai->rssi = NULL;
			if (cap_rid.softCap & cpu_to_le16(8))
				ai->config.rmode |= RXMODE_NORMALIZED_RSSI;
			else
				airo_print_warn(ai->dev->name, "unknown received signal "
						"level scale");
		}
		ai->config.opmode = adhoc ? MODE_STA_IBSS : MODE_STA_ESS;
		ai->config.authType = AUTH_OPEN;
		ai->config.modulation = MOD_CCK;

		if (le16_to_cpu(cap_rid.len) >= sizeof(cap_rid) &&
		    (cap_rid.extSoftCap & cpu_to_le16(1)) &&
		    micsetup(ai) == SUCCESS) {
			ai->config.opmode |= MODE_MIC;
			set_bit(FLAG_MIC_CAPABLE, &ai->flags);
		}

		/* Save off the MAC */
		for( i = 0; i < ETH_ALEN; i++ ) {
			mac[i] = ai->config.macAddr[i];
		}

		/* Check to see if there are any insmod configured
		   rates to add */
		if ( rates[0] ) {
			memset(ai->config.rates,0,sizeof(ai->config.rates));
			for( i = 0; i < 8 && rates[i]; i++ ) {
				ai->config.rates[i] = rates[i];
			}
		}
		set_bit (FLAG_COMMIT, &ai->flags);
	}

	/* Setup the SSIDs if present */
	if ( ssids[0] ) {
		int i;
		for( i = 0; i < 3 && ssids[i]; i++ ) {
			size_t len = strlen(ssids[i]);
			if (len > 32)
				len = 32;
			mySsid.ssids[i].len = cpu_to_le16(len);
			memcpy(mySsid.ssids[i].ssid, ssids[i], len);
		}
		mySsid.len = cpu_to_le16(sizeof(mySsid));
	}

	status = writeConfigRid(ai, lock);
	if ( status != SUCCESS ) return ERROR;

	/* Set up the SSID list */
	if ( ssids[0] ) {
		status = writeSsidRid(ai, &mySsid, lock);
		if ( status != SUCCESS ) return ERROR;
	}

	status = enable_MAC(ai, lock);
	if (status != SUCCESS)
		return ERROR;

	/* Grab the initial wep key, we gotta save it for auto_wep */
	rc = readWepKeyRid(ai, &wkr, 1, lock);
	if (rc == SUCCESS) do {
		lastindex = wkr.kindex;
		if (wkr.kindex == cpu_to_le16(0xffff)) {
			ai->defindex = wkr.mac[0];
		}
		rc = readWepKeyRid(ai, &wkr, 0, lock);
	} while(lastindex != wkr.kindex);

	try_auto_wep(ai);

	return SUCCESS;
}
