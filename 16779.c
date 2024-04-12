 bool PluginInstance::Start(const GURL& url,
                            char** const param_names,
                            char** const param_values,
                           int param_count,
                           bool load_manually) {
  load_manually_ = load_manually;
  unsigned short mode = load_manually_ ? NP_FULL : NP_EMBED;
  npp_->ndata = this;

  NPError err = NPP_New(mode, param_count,
      const_cast<char **>(param_names), const_cast<char **>(param_values));
  return err == NPERR_NO_ERROR;
}
