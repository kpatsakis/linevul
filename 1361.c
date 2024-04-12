fifo_close(notify_fifo_t* fifo)
{
	if (fifo->fd != -1) {
		close(fifo->fd);
		fifo->fd = -1;
	}
	if (fifo->created_fifo)
		unlink(fifo->name);
}
