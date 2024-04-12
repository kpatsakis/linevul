AutofillManager::AutofillManager(TabContentsWrapper* tab_contents,
                                 PersonalDataManager* personal_data)
    : TabContentsObserver(tab_contents->tab_contents()),
      tab_contents_wrapper_(tab_contents),
      personal_data_(personal_data),
      download_manager_(NULL),
      disable_download_manager_requests_(true),
      metric_logger_(new AutofillMetrics),
      has_logged_autofill_enabled_(false),
      has_logged_address_suggestions_count_(false) {
  DCHECK(tab_contents);
}
