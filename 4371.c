bool CellularNetwork::StartActivation() const {
  if (!EnsureCrosLoaded())
    return false;
  return ActivateCellularModem(service_path_.c_str(), NULL);
}
