static void opl3_close(int dev)
{
	devc->busy = 0;
	devc->v_alloc->max_voice = devc->nr_voice = (devc->model == 2) ? 18 : 9;

	devc->fm_info.nr_drums = 0;
	devc->fm_info.perc_mode = 0;

	opl3_reset(dev);
}
