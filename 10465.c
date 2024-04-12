static void shm_destroy(struct ipc_namespace *ns, struct shmid_kernel *shp)
{
	struct file *shm_file;

	shm_file = shp->shm_file;
	shp->shm_file = NULL;
	ns->shm_tot -= (shp->shm_segsz + PAGE_SIZE - 1) >> PAGE_SHIFT;
	shm_rmid(ns, shp);
	shm_unlock(shp);
	if (!is_file_hugepages(shm_file))
		shmem_lock(shm_file, 0, shp->mlock_user);
	else if (shp->mlock_user)
		user_shm_unlock(i_size_read(file_inode(shm_file)),
				shp->mlock_user);
	fput(shm_file);
	ipc_rcu_putref(shp, shm_rcu_free);
}