reread_4(struct file *file)
 /* The same but for a four byte quantity */
{
   png_uint_32 result = 0;
 int i = 0;

 while (++i <= 4)
      result = (result << 8) + reread_byte(file);

 return result;
}
