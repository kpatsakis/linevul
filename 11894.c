SecurityHandler::SecurityHandler()
    : DevToolsDomainHandler(Security::Metainfo::domainName),
      enabled_(false),
      host_(nullptr) {
}
