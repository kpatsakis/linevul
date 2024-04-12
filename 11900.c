void PluginInstance::NPP_StreamAsFile(NPStream *stream, const char *fname) {
  DCHECK(npp_functions_ != 0);
  DCHECK(npp_functions_->asfile != 0);
  if (npp_functions_->asfile != 0) {
    npp_functions_->asfile(npp_, stream, fname);
  }

  FilePath file_name = FilePath::FromWStringHack(UTF8ToWide(fname));
  files_created_.push_back(file_name);
}
