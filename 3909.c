struct net_device *init_airo_card( unsigned short irq, int port, int is_pcmcia,
				  struct device *dmdev)
{
	return _init_airo_card ( irq, port, is_pcmcia, NULL, dmdev);
}
