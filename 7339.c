static ssize_t vhost_scsi_tpg_show_nexus(struct se_portal_group *se_tpg,
					char *page)
{
	struct vhost_scsi_tpg *tpg = container_of(se_tpg,
				struct vhost_scsi_tpg, se_tpg);
	struct vhost_scsi_nexus *tv_nexus;
	ssize_t ret;

	mutex_lock(&tpg->tv_tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	if (!tv_nexus) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		return -ENODEV;
	}
	ret = snprintf(page, PAGE_SIZE, "%s\n",
			tv_nexus->tvn_se_sess->se_node_acl->initiatorname);
	mutex_unlock(&tpg->tv_tpg_mutex);

	return ret;
}
