void qib_device_remove(struct qib_devdata *dd)
{
	qib_user_remove(dd);
	qib_diag_remove(dd);
}
