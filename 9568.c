  void InsertIntoMap(GDataCacheMetadataMap::CacheMap* cache_map,
                     const std::string& resource_id,
                     const std::string& md5,
                     GDataCache::CacheSubDirectoryType sub_dir_type,
                     int cache_state) {
    cache_map->insert(std::make_pair(
         resource_id, GDataCache::CacheEntry(md5, sub_dir_type, cache_state)));
   }
