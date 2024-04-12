DownloadItemImpl::DownloadItemImpl(
    Delegate* delegate,
    const DownloadCreateInfo& info,
    scoped_ptr<DownloadRequestHandleInterface> request_handle,
    bool is_otr,
    const net::BoundNetLog& bound_net_log)
    : request_handle_(request_handle.Pass()),
      download_id_(info.download_id),
      target_disposition_(
          (info.prompt_user_for_save_location) ?
              TARGET_DISPOSITION_PROMPT : TARGET_DISPOSITION_OVERWRITE),
      url_chain_(info.url_chain),
      referrer_url_(info.referrer_url),
      suggested_filename_(UTF16ToUTF8(info.save_info.suggested_name)),
      forced_file_path_(info.save_info.file_path),
      transition_type_(info.transition_type),
      has_user_gesture_(info.has_user_gesture),
      content_disposition_(info.content_disposition),
      mime_type_(info.mime_type),
      original_mime_type_(info.original_mime_type),
      referrer_charset_(info.referrer_charset),
      remote_address_(info.remote_address),
      total_bytes_(info.total_bytes),
      received_bytes_(0),
      bytes_per_sec_(0),
      last_reason_(content::DOWNLOAD_INTERRUPT_REASON_NONE),
      start_tick_(base::TimeTicks::Now()),
      state_(IN_PROGRESS),
      danger_type_(content::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS),
      start_time_(info.start_time),
      db_handle_(DownloadItem::kUninitializedHandle),
      delegate_(delegate),
      is_paused_(false),
      open_when_complete_(false),
      file_externally_removed_(false),
      safety_state_(SAFE),
      auto_opened_(false),
      is_persisted_(false),
      is_otr_(is_otr),
      is_temporary_(!info.save_info.file_path.empty()),
      all_data_saved_(false),
      opened_(false),
      open_enabled_(true),
      delegate_delayed_complete_(false),
      bound_net_log_(bound_net_log),
      ALLOW_THIS_IN_INITIALIZER_LIST(weak_ptr_factory_(this)) {
  delegate_->Attach();
  Init(true /* actively downloading */,
       download_net_logs::SRC_NEW_DOWNLOAD);

  bound_net_log_.AddEvent(
      net::NetLog::TYPE_DOWNLOAD_URL_REQUEST,
      info.request_bound_net_log.source().ToEventParametersCallback());

  info.request_bound_net_log.AddEvent(
      net::NetLog::TYPE_DOWNLOAD_STARTED,
      bound_net_log_.source().ToEventParametersCallback());
}
