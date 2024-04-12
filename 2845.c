void HistogramEnumerate(const std::string& name, int sample, int maximum,
                        int out_of_range_replacement) {
  if (sample < 0 || sample >= maximum) {
    if (out_of_range_replacement < 0)
      return;
    else
      sample = out_of_range_replacement;
  }
  const PPB_UMA_Private* ptr = GetUMAInterface();
  if (ptr == NULL) return;
  ptr->HistogramEnumeration(pp::Var(name).pp_var(), sample, maximum);
}
