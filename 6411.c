type_message(struct file *file, png_uint_32 type, const char *what)
 /* Error message for a chunk; the chunk name comes from 'type' */
{
 if (file->global->errors)
 {
      fputs(file->file_name, stderr);
      type_sep(stderr);
      type_name(type, stderr);
      type_sep(stderr);
      fputs(what, stderr);
      putc('\n', stderr);
 }
}
