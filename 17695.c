static int pcd_probe(struct pcd_unit *cd, int ms, char *id)
{
	if (ms == -1) {
		for (cd->drive = 0; cd->drive <= 1; cd->drive++)
			if (!pcd_reset(cd) && !pcd_identify(cd, id))
				return 0;
	} else {
		cd->drive = ms;
		if (!pcd_reset(cd) && !pcd_identify(cd, id))
			return 0;
	}
	return -1;
}
