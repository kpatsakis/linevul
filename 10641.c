reread_byte(struct file *file)
 /* Read a byte when an error is not expected to happen because the byte has
    * been read before without error.
    */
{
 int ch = getc(file->file);

 if (errno != 0)
      file->read_errno = errno;

 if (ch < 0 || ch > 255)
      stop(file, UNEXPECTED_ERROR_CODE, "reread");

 return (png_byte)ch;
}
