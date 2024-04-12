  std::string GetRequestStringForPNACL(const std::string& fragment) const {
    return RequestString(test_page_url_ + fragment, "navigate", "include") +
           RequestString(GetURL("/pnacl_url_loader.nmf"), "same-origin",
                         "same-origin") +
           RequestString(GetURL("/pnacl_url_loader_newlib_pnacl.pexe"),
                         "same-origin", "same-origin");
  }
