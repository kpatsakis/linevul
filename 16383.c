png_set_benign_errors(png_structp png_ptr, int allowed)
{
   png_debug(1, "in png_set_benign_errors");

   if (allowed)
      png_ptr->flags |= PNG_FLAG_BENIGN_ERRORS_WARN;
   else
      png_ptr->flags &= ~PNG_FLAG_BENIGN_ERRORS_WARN;
}
