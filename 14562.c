static void cull_user_controllers(void)
{
	int i, j;

	for (i = 0;  i < nr_subsystems; i++) {
		if (strncmp(subsystems[i], "name=", 5) != 0)
			continue;
		for (j = i;  j < nr_subsystems-1; j++)
			subsystems[j] = subsystems[j+1];
		nr_subsystems--;
	}
}
