static int prism2_close(struct net_device *dev)
{
	struct hostap_interface *iface;
	local_info_t *local;

	PDEBUG(DEBUG_FLOW, "%s: prism2_close\n", dev->name);

	iface = netdev_priv(dev);
	local = iface->local;

	if (dev == local->ddev) {
		prism2_sta_deauth(local, WLAN_REASON_DEAUTH_LEAVING);
	}
#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	if (!local->hostapd && dev == local->dev &&
	    (!local->func->card_present || local->func->card_present(local)) &&
	    local->hw_ready && local->ap && local->iw_mode == IW_MODE_MASTER)
		hostap_deauth_all_stas(dev, local->ap, 1);
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	if (dev == local->dev) {
		local->func->hw_shutdown(dev, HOSTAP_HW_ENABLE_CMDCOMPL);
	}

	if (netif_running(dev)) {
		netif_stop_queue(dev);
		netif_device_detach(dev);
	}

	cancel_work_sync(&local->reset_queue);
	cancel_work_sync(&local->set_multicast_list_queue);
	cancel_work_sync(&local->set_tim_queue);
#ifndef PRISM2_NO_STATION_MODES
	cancel_work_sync(&local->info_queue);
#endif
	cancel_work_sync(&local->comms_qual_update);

	module_put(local->hw_module);

	local->num_dev_open--;

	if (dev != local->dev && local->dev->flags & IFF_UP &&
	    local->master_dev_auto_open && local->num_dev_open == 1) {
		/* Close master radio interface automatically if it was also
		 * opened automatically and we are now closing the last
		 * remaining non-master device. */
		dev_close(local->dev);
	}

	return 0;
}
