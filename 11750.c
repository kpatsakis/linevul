base::FilePath GetTemporaryDownloadDirectory() {
  std::unique_ptr<base::Environment> env(base::Environment::Create());
  return base::nix::GetXDGDirectory(env.get(), "XDG_DATA_HOME", ".local/share");
}
