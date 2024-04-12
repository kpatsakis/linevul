static int vhost_scsi_release(struct inode *inode, struct file *f)
{
	struct vhost_scsi *vs = f->private_data;
	struct vhost_scsi_target t;

	mutex_lock(&vs->dev.mutex);
	memcpy(t.vhost_wwpn, vs->vs_vhost_wwpn, sizeof(t.vhost_wwpn));
	mutex_unlock(&vs->dev.mutex);
	vhost_scsi_clear_endpoint(vs, &t);
	vhost_dev_stop(&vs->dev);
	vhost_dev_cleanup(&vs->dev, false);
	/* Jobs can re-queue themselves in evt kick handler. Do extra flush. */
	vhost_scsi_flush(vs);
	kfree(vs->dev.vqs);
	kvfree(vs);
	return 0;
}
