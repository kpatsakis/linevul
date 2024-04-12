void GDataDirectory::ToProto(GDataDirectoryProto* proto) const {
  GDataEntry::ToProto(proto->mutable_gdata_entry());
  DCHECK(proto->gdata_entry().file_info().is_directory());
  proto->set_refresh_time(refresh_time_.ToInternalValue());
  proto->set_start_feed_url(start_feed_url_.spec());
  proto->set_next_feed_url(next_feed_url_.spec());
  proto->set_upload_url(upload_url_.spec());
  proto->set_origin(origin_);
  for (GDataFileCollection::const_iterator iter = child_files_.begin();
       iter != child_files_.end(); ++iter) {
    GDataFile* file = iter->second;
    file->ToProto(proto->add_child_files());
  }
  for (GDataDirectoryCollection::const_iterator iter =
       child_directories_.begin();
       iter != child_directories_.end(); ++iter) {
    GDataDirectory* dir = iter->second;
    dir->ToProto(proto->add_child_directories());
  }
}
