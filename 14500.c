static void charstring_end(void)
{
  byte *bp;

  sprintf(line, "%d ", (int) (charstring_bp - charstring_buf));
  eexec_string(line);
  sprintf(line, "%s ", cs_start);
  eexec_string(line);
  for (bp = charstring_buf; bp < charstring_bp; bp++)
    eexec_byte(*bp);
}
