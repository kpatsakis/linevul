void mndp_broadcast() {
	struct mt_packet pdata;
	struct utsname s_uname;
	struct net_interface *interface;
	unsigned int uptime;
#if defined(__APPLE__)
	int mib[] = {CTL_KERN, KERN_BOOTTIME};
	struct timeval boottime;
	size_t tv_size = sizeof(boottime);
	if (sysctl(mib, sizeof(mib)/sizeof(mib[0]), &boottime, &tv_size, NULL, 0) == -1) {
	  return;
	}
	uptime = htole32(boottime.tv_sec);
#elif defined(__linux__)
	struct sysinfo s_sysinfo;

	if (sysinfo(&s_sysinfo) != 0) {
		return;
	}

	/* Seems like ping uptime is transmitted as little endian? */
	uptime = htole32(s_sysinfo.uptime);
#else
	struct timespec ts;

	if (clock_gettime(CLOCK_UPTIME, &ts) != -1) {
		uptime = htole32(((unsigned int)ts.tv_sec));
	}
#endif

	if (uname(&s_uname) != 0) {
		return;
	}

	DL_FOREACH(interfaces, interface) {
		struct mt_mndp_hdr *header = (struct mt_mndp_hdr *)&(pdata.data);

		if (interface->has_mac == 0) {
			continue;
		}

		mndp_init_packet(&pdata, 0, 1);
		mndp_add_attribute(&pdata, MT_MNDPTYPE_ADDRESS, interface->mac_addr, ETH_ALEN);
		mndp_add_attribute(&pdata, MT_MNDPTYPE_IDENTITY, s_uname.nodename, strlen(s_uname.nodename));
		mndp_add_attribute(&pdata, MT_MNDPTYPE_VERSION, s_uname.release, strlen(s_uname.release));
		mndp_add_attribute(&pdata, MT_MNDPTYPE_PLATFORM, PLATFORM_NAME, strlen(PLATFORM_NAME));
		mndp_add_attribute(&pdata, MT_MNDPTYPE_HARDWARE, s_uname.machine, strlen(s_uname.machine));
		mndp_add_attribute(&pdata, MT_MNDPTYPE_TIMESTAMP, &uptime, 4);
		mndp_add_attribute(&pdata, MT_MNDPTYPE_SOFTID, MT_SOFTID_MACTELNET, strlen(MT_SOFTID_MACTELNET));
		mndp_add_attribute(&pdata, MT_MNDPTYPE_IFNAME, interface->name, strlen(interface->name));

		header->cksum = in_cksum((unsigned short *)&(pdata.data), pdata.size);
		send_special_udp(interface, MT_MNDP_PORT, &pdata);
	}
}
