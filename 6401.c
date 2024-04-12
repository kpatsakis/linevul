grub_fshelp_find_file (const char *path, grub_fshelp_node_t rootnode,
		       grub_fshelp_node_t *foundnode,
		       int (*iterate_dir) (grub_fshelp_node_t dir,
					   int (*hook)
					   (const char *filename,
					    enum grub_fshelp_filetype filetype,
					    grub_fshelp_node_t node,
					    void *closure),
					   void *closure),
		       void *closure,
		       char *(*read_symlink) (grub_fshelp_node_t node),
		       enum grub_fshelp_filetype expecttype)
{
  grub_err_t err;
  struct grub_fshelp_find_file_closure c;

  c.rootnode = rootnode;
  c.iterate_dir = iterate_dir;
  c.closure = closure;
  c.read_symlink = read_symlink;
  c.symlinknest = 0;
  c.foundtype = GRUB_FSHELP_DIR;

  if (!path || path[0] != '/')
    {
      grub_error (GRUB_ERR_BAD_FILENAME, "bad filename");
      return grub_errno;
    }

  err = find_file (path, rootnode, foundnode, &c);
  if (err)
    return err;

  /* Check if the node that was found was of the expected type.  */
  if (expecttype == GRUB_FSHELP_REG && c.foundtype != expecttype)
    return grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a regular file");
  else if (expecttype == GRUB_FSHELP_DIR && c.foundtype != expecttype)
    return grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a directory");

  return 0;
}
