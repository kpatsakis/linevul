PHPAPI php_stream *_php_stream_temp_create(int mode, size_t max_memory_usage STREAMS_DC TSRMLS_DC)
{
	php_stream_temp_data *self;
	php_stream *stream;

	self = ecalloc(1, sizeof(*self));
	self->smax = max_memory_usage;
	self->mode = mode;
	self->meta = NULL;
	stream = php_stream_alloc_rel(&php_stream_temp_ops, self, 0, mode & TEMP_STREAM_READONLY ? "rb" : "w+b");
	stream->flags |= PHP_STREAM_FLAG_NO_BUFFER;
	self->innerstream = php_stream_memory_create_rel(mode);
	php_stream_encloses(stream, self->innerstream);

	return stream;
}
