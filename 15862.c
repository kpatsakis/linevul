void CrostiniUpgrader::OnCancel(CrostiniResult result) {
  for (auto& observer : upgrader_observers_) {
    observer.OnCanceled();
  }
}
