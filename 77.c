  void SetTopSites(const MostVisitedURLList& new_top_sites) {
    top_sites()->SetTopSites(new_top_sites,
                             TopSitesImpl::CALL_LOCATION_FROM_OTHER_PLACES);
  }
