static int read_capacity_16(struct scsi_disk *sdkp, struct scsi_device *sdp,
						unsigned char *buffer)
{
	unsigned char cmd[16];
	struct scsi_sense_hdr sshdr;
	int sense_valid = 0;
	int the_result;
	int retries = 3, reset_retries = READ_CAPACITY_RETRIES_ON_RESET;
	unsigned int alignment;
	unsigned long long lba;
	unsigned sector_size;

	if (sdp->no_read_capacity_16)
		return -EINVAL;

	do {
		memset(cmd, 0, 16);
		cmd[0] = SERVICE_ACTION_IN;
		cmd[1] = SAI_READ_CAPACITY_16;
		cmd[13] = RC16_LEN;
		memset(buffer, 0, RC16_LEN);

		the_result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
					buffer, RC16_LEN, &sshdr,
					SD_TIMEOUT, SD_MAX_RETRIES, NULL);

		if (media_not_present(sdkp, &sshdr))
			return -ENODEV;

		if (the_result) {
			sense_valid = scsi_sense_valid(&sshdr);
			if (sense_valid &&
			    sshdr.sense_key == ILLEGAL_REQUEST &&
			    (sshdr.asc == 0x20 || sshdr.asc == 0x24) &&
			    sshdr.ascq == 0x00)
				/* Invalid Command Operation Code or
				 * Invalid Field in CDB, just retry
				 * silently with RC10 */
				return -EINVAL;
			if (sense_valid &&
			    sshdr.sense_key == UNIT_ATTENTION &&
			    sshdr.asc == 0x29 && sshdr.ascq == 0x00)
				/* Device reset might occur several times,
				 * give it one more chance */
				if (--reset_retries > 0)
					continue;
		}
		retries--;

	} while (the_result && retries);

	if (the_result) {
		sd_printk(KERN_NOTICE, sdkp, "READ CAPACITY(16) failed\n");
		read_capacity_error(sdkp, sdp, &sshdr, sense_valid, the_result);
		return -EINVAL;
	}

	sector_size = get_unaligned_be32(&buffer[8]);
	lba = get_unaligned_be64(&buffer[0]);

	sd_read_protection_type(sdkp, buffer);

	if ((sizeof(sdkp->capacity) == 4) && (lba >= 0xffffffffULL)) {
		sd_printk(KERN_ERR, sdkp, "Too big for this kernel. Use a "
			"kernel compiled with support for large block "
			"devices.\n");
		sdkp->capacity = 0;
		return -EOVERFLOW;
	}

	/* Logical blocks per physical block exponent */
	sdkp->physical_block_size = (1 << (buffer[13] & 0xf)) * sector_size;

	/* Lowest aligned logical block */
	alignment = ((buffer[14] & 0x3f) << 8 | buffer[15]) * sector_size;
	blk_queue_alignment_offset(sdp->request_queue, alignment);
	if (alignment && sdkp->first_scan)
		sd_printk(KERN_NOTICE, sdkp,
			  "physical block alignment offset: %u\n", alignment);

	if (buffer[14] & 0x80) { /* LBPME */
		sdkp->lbpme = 1;

		if (buffer[14] & 0x40) /* LBPRZ */
			sdkp->lbprz = 1;

		sd_config_discard(sdkp, SD_LBP_WS16);
	}

	sdkp->capacity = lba + 1;
	return sector_size;
}
