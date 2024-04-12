display_cache_file(struct display *dp, const char *filename)
 /* Does the initial cache of the file. */
{
 FILE *fp;
 int ret;

   dp->filename = filename;

 if (filename != NULL)
 {
      fp = fopen(filename, "rb");
 if (fp == NULL)
         display_log(dp, USER_ERROR, "open failed: %s", strerror(errno));
 }

 else
      fp = stdin;

   ret = buffer_from_file(&dp->original_file, fp);

   fclose(fp);

 if (ret != 0)
      display_log(dp, APP_ERROR, "read failed: %s", strerror(ret));
}
