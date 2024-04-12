    virtual void GetEntryInfoCallback(
        base::PlatformFileError error,
        const FilePath& entry_path,
        scoped_ptr<GDataEntryProto> entry_proto) {
      last_error_ = error;
      entry_proto_ = entry_proto.Pass();
    }
