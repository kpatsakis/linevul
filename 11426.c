  int MakeFrontendID(const std::string& cc_sid,
                     const std::string& profile_sid) const {
    return autofill_manager_->MakeFrontendID(cc_sid, profile_sid);
  }
