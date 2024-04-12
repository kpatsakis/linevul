void WebContext::setHostMappingRules(const QStringList& rules) {
  DCHECK(!IsInitialized());

  construct_props_->host_mapping_rules.clear();

  for (QStringList::const_iterator it = rules.cbegin();
       it != rules.cend(); ++it) {
    construct_props_->host_mapping_rules.push_back((*it).toStdString());
  }
}
