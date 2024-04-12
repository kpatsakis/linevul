command_send_data (Fep *fep,
		   FepControlMessage *request)
{
  ssize_t total = 0;

  while (total < request->args[0].len)
    {
      ssize_t bytes_sent = _fep_output_send_data (fep,
						  request->args[0].str + total,
						  request->args[0].len - total);
      if (bytes_sent < 0)
	break;
      total += bytes_sent;
    }
}
