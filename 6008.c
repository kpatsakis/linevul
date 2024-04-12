  void RegisterProcess(const std::string& site, RenderProcessHost* process) {
    map_[site] = process;
  }
