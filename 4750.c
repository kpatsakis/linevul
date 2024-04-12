png_push_restore_buffer(png_structp png_ptr, png_bytep buffer,
   png_size_t buffer_length)
{
   png_ptr->current_buffer = buffer;
   png_ptr->current_buffer_size = buffer_length;
   png_ptr->buffer_size = buffer_length + png_ptr->save_buffer_size;
   png_ptr->current_buffer_ptr = png_ptr->current_buffer;
}
