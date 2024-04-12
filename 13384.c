void ProfileDependencyManager::AddEdge(ProfileKeyedBaseFactory* depended,
                                       ProfileKeyedBaseFactory* dependee) {
  edges_.insert(std::make_pair(depended, dependee));
  destruction_order_.clear();
}
