  bool HostFound(const std::string& host) {
    return base::Contains(successful_dns_lookups_, host);
  }
