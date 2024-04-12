smb_ofile_close_and_next(smb_ofile_t *of)
{
	smb_ofile_t	*next_of;
	smb_tree_t	*tree;

	ASSERT(of);
	ASSERT(of->f_magic == SMB_OFILE_MAGIC);

	mutex_enter(&of->f_mutex);
	switch (of->f_state) {
	case SMB_OFILE_STATE_OPEN:
		/* The file is still open. */
		of->f_refcnt++;
		ASSERT(of->f_refcnt);
		tree = of->f_tree;
		mutex_exit(&of->f_mutex);
		smb_llist_exit(&of->f_tree->t_ofile_list);
		smb_ofile_close(of, 0);
		smb_ofile_release(of);
		smb_llist_enter(&tree->t_ofile_list, RW_READER);
		next_of = smb_llist_head(&tree->t_ofile_list);
		break;
	case SMB_OFILE_STATE_CLOSING:
	case SMB_OFILE_STATE_CLOSED:
		/*
		 * The ofile exists but is closed or
		 * in the process being closed.
		 */
		mutex_exit(&of->f_mutex);
		next_of = smb_llist_next(&of->f_tree->t_ofile_list, of);
		break;
	default:
		ASSERT(0);
		mutex_exit(&of->f_mutex);
		next_of = smb_llist_next(&of->f_tree->t_ofile_list, of);
		break;
	}
	return (next_of);
}
