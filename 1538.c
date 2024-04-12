HostCache::Entry::Entry(int error,
                        const AddressList& addresses,
                        base::TimeTicks expires,
                        int network_changes)
    : error_(error),
      addresses_(addresses),
      ttl_(base::TimeDelta::FromSeconds(-1)),
      expires_(expires),
      network_changes_(network_changes),
      total_hits_(0),
      stale_hits_(0) {}
