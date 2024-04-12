static bool pipe_buf_can_merge(struct pipe_buffer *buf)
{
	return buf->ops == &anon_pipe_buf_ops;
}
