smb_ofile_delete(void *arg)
{
	smb_tree_t	*tree;
	smb_ofile_t	*of = (smb_ofile_t *)arg;

	SMB_OFILE_VALID(of);
	ASSERT(of->f_refcnt == 0);
	ASSERT(of->f_state == SMB_OFILE_STATE_CLOSED);
	ASSERT(!SMB_OFILE_OPLOCK_GRANTED(of));

	tree = of->f_tree;
	smb_llist_enter(&tree->t_ofile_list, RW_WRITER);
	smb_llist_remove(&tree->t_ofile_list, of);
	smb_idpool_free(&tree->t_fid_pool, of->f_fid);
	atomic_dec_32(&tree->t_session->s_file_cnt);
	smb_llist_exit(&tree->t_ofile_list);

	mutex_enter(&of->f_mutex);
	mutex_exit(&of->f_mutex);

	switch (of->f_ftype) {
	case SMB_FTYPE_BYTE_PIPE:
	case SMB_FTYPE_MESG_PIPE:
		smb_opipe_dealloc(of->f_pipe);
		of->f_pipe = NULL;
		break;
	case SMB_FTYPE_DISK:
		if (of->f_odir != NULL)
			smb_odir_release(of->f_odir);
		smb_node_rem_ofile(of->f_node, of);
		smb_node_release(of->f_node);
		break;
	default:
		ASSERT(!"f_ftype");
		break;
	}

	of->f_magic = (uint32_t)~SMB_OFILE_MAGIC;
	mutex_destroy(&of->f_mutex);
	crfree(of->f_cr);
	smb_user_release(of->f_user);
	kmem_cache_free(smb_cache_ofile, of);
}
