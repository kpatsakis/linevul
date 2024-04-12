void iov_iter_pipe(struct iov_iter *i, int direction,
			struct pipe_inode_info *pipe,
 			size_t count)
 {
 	BUG_ON(direction != ITER_PIPE);
 	i->type = direction;
 	i->pipe = pipe;
 	i->idx = (pipe->curbuf + pipe->nrbufs) & (pipe->buffers - 1);
	i->iov_offset = 0;
	i->count = count;
}
