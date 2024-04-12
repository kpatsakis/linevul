static void ieee80211_assign_perm_addr(struct ieee80211_local *local,
				       struct net_device *dev,
				       enum nl80211_iftype type)
{
	struct ieee80211_sub_if_data *sdata;
	u64 mask, start, addr, val, inc;
	u8 *m;
	u8 tmp_addr[ETH_ALEN];
	int i;

	/* default ... something at least */
	memcpy(dev->perm_addr, local->hw.wiphy->perm_addr, ETH_ALEN);

	if (is_zero_ether_addr(local->hw.wiphy->addr_mask) &&
	    local->hw.wiphy->n_addresses <= 1)
		return;


	mutex_lock(&local->iflist_mtx);

	switch (type) {
	case NL80211_IFTYPE_MONITOR:
		/* doesn't matter */
		break;
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_AP_VLAN:
		/* match up with an AP interface */
		list_for_each_entry(sdata, &local->interfaces, list) {
			if (sdata->vif.type != NL80211_IFTYPE_AP)
				continue;
			memcpy(dev->perm_addr, sdata->vif.addr, ETH_ALEN);
			break;
		}
		/* keep default if no AP interface present */
		break;
	default:
		/* assign a new address if possible -- try n_addresses first */
		for (i = 0; i < local->hw.wiphy->n_addresses; i++) {
			bool used = false;

			list_for_each_entry(sdata, &local->interfaces, list) {
				if (memcmp(local->hw.wiphy->addresses[i].addr,
					   sdata->vif.addr, ETH_ALEN) == 0) {
					used = true;
					break;
				}
			}

			if (!used) {
				memcpy(dev->perm_addr,
				       local->hw.wiphy->addresses[i].addr,
				       ETH_ALEN);
				break;
			}
		}

		/* try mask if available */
		if (is_zero_ether_addr(local->hw.wiphy->addr_mask))
			break;

		m = local->hw.wiphy->addr_mask;
		mask =	((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
			((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
			((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

		if (__ffs64(mask) + hweight64(mask) != fls64(mask)) {
			/* not a contiguous mask ... not handled now! */
			printk(KERN_DEBUG "not contiguous\n");
			break;
		}

		m = local->hw.wiphy->perm_addr;
		start = ((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
			((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
			((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

		inc = 1ULL<<__ffs64(mask);
		val = (start & mask);
		addr = (start & ~mask) | (val & mask);
		do {
			bool used = false;

			tmp_addr[5] = addr >> 0*8;
			tmp_addr[4] = addr >> 1*8;
			tmp_addr[3] = addr >> 2*8;
			tmp_addr[2] = addr >> 3*8;
			tmp_addr[1] = addr >> 4*8;
			tmp_addr[0] = addr >> 5*8;

			val += inc;

			list_for_each_entry(sdata, &local->interfaces, list) {
				if (memcmp(tmp_addr, sdata->vif.addr,
							ETH_ALEN) == 0) {
					used = true;
					break;
				}
			}

			if (!used) {
				memcpy(dev->perm_addr, tmp_addr, ETH_ALEN);
				break;
			}
			addr = (start & ~mask) | (val & mask);
		} while (addr != start);

		break;
	}

	mutex_unlock(&local->iflist_mtx);
}
