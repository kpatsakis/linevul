static void i8042_unregister_ports(void)
{
	int i;

	for (i = 0; i < I8042_NUM_PORTS; i++) {
		if (i8042_ports[i].serio) {
			serio_unregister_port(i8042_ports[i].serio);
			i8042_ports[i].serio = NULL;
		}
	}
}
