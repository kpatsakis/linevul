static void eexec_start(char *string)
{
  eexec_string("currentfile eexec\n");
  if (pfb && w.blocktyp != PFB_BINARY) {
    pfb_writer_output_block(&w);
    w.blocktyp = PFB_BINARY;
  }

  in_eexec = 1;
  er = 55665;
  eexec_byte(0);
  eexec_byte(0);
  eexec_byte(0);
  eexec_byte(0);
  eexec_string(string);
}
