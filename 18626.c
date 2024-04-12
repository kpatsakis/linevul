int rdfa_parse(rdfacontext* context)
{
  int rval;

  rval = rdfa_parse_start(context);
  if(rval != RDFA_PARSE_SUCCESS)
  {
    context->done = 1;
    return rval;
  }

  do
  {
     size_t wblen;
     int done;

     wblen = context->buffer_filler_callback(
        context->working_buffer, context->wb_allocated,
        context->callback_data);
     done = (wblen == 0);

     rval = rdfa_parse_chunk(context, context->working_buffer, wblen, done);
     context->done=done;
  }
  while(!context->done && rval == RDFA_PARSE_SUCCESS);

  rdfa_parse_end(context);

  return rval;
}
