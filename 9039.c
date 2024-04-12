void AutoFillManager::UploadFormData() {
  if (!disable_download_manager_requests_ && upload_form_structure_.get()) {
    bool was_autofilled = false;
    std::list<std::string>::iterator it;
    int total_form_checked = 0;
    for (it = autofilled_forms_signatures_.begin();
         it != autofilled_forms_signatures_.end() && total_form_checked < 3;
         ++it, ++total_form_checked) {
      if (*it == upload_form_structure_->FormSignature())
        was_autofilled = true;
    }
    if (total_form_checked == 3 && it != autofilled_forms_signatures_.end()) {
      autofilled_forms_signatures_.erase(it,
                                         autofilled_forms_signatures_.end());
    }
    download_manager_.StartUploadRequest(*(upload_form_structure_.get()),
                                         was_autofilled);
  }
}
