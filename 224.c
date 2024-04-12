struct sas_phy *sas_get_local_phy(struct domain_device *dev)
{
	struct sas_ha_struct *ha = dev->port->ha;
	struct sas_phy *phy;
	unsigned long flags;

	/* a published domain device always has a valid phy, it may be
	 * stale, but it is never NULL
	 */
	BUG_ON(!dev->phy);

	spin_lock_irqsave(&ha->phy_port_lock, flags);
	phy = dev->phy;
	get_device(&phy->dev);
	spin_unlock_irqrestore(&ha->phy_port_lock, flags);

	return phy;
}
