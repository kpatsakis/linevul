static void do_unflock(struct file *file, struct file_lock *fl)
{
	struct gfs2_file *fp = file->private_data;
	struct gfs2_holder *fl_gh = &fp->f_fl_gh;

	mutex_lock(&fp->f_fl_mutex);
	flock_lock_file_wait(file, fl);
	if (fl_gh->gh_gl) {
		gfs2_glock_dq_wait(fl_gh);
		gfs2_holder_uninit(fl_gh);
	}
	mutex_unlock(&fp->f_fl_mutex);
}
