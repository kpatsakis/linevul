static FxInfo **DestroyFxThreadSet(FxInfo **fx_info)
{
  register ssize_t
    i;

  assert(fx_info != (FxInfo **) NULL);
  for (i=0; i < (ssize_t) GetMagickResourceLimit(ThreadResource); i++)
    if (fx_info[i] != (FxInfo *) NULL)
      fx_info[i]=DestroyFxInfo(fx_info[i]);
  fx_info=(FxInfo **) RelinquishMagickMemory(fx_info);
  return(fx_info);
}
