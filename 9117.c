bool AXObject::isLandmarkRelated() const {
  switch (roleValue()) {
    case ApplicationRole:
    case ArticleRole:
    case BannerRole:
    case ComplementaryRole:
    case ContentInfoRole:
    case FooterRole:
    case FormRole:
    case MainRole:
    case NavigationRole:
    case RegionRole:
    case SearchRole:
      return true;
    default:
      return false;
  }
}
