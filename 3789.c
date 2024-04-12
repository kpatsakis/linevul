void RenderFrameImpl::OnSerializeAsMHTML(
    const FrameMsg_SerializeAsMHTML_Params& params) {
  TRACE_EVENT0("page-serialization", "RenderFrameImpl::OnSerializeAsMHTML");
  base::TimeTicks start_time = base::TimeTicks::Now();
  base::File file = IPC::PlatformFileForTransitToFile(params.destination_file);
  const WebString mhtml_boundary =
      WebString::FromUTF8(params.mhtml_boundary_marker);
  DCHECK(!mhtml_boundary.IsEmpty());

  std::vector<WebThreadSafeData> mhtml_contents;
  std::set<std::string> serialized_resources_uri_digests;
  MHTMLPartsGenerationDelegate delegate(params,
                                        &serialized_resources_uri_digests);

  MhtmlSaveStatus save_status = MhtmlSaveStatus::SUCCESS;
  bool has_some_data = false;

  if (IsMainFrame()) {
    TRACE_EVENT0("page-serialization",
                 "RenderFrameImpl::OnSerializeAsMHTML header");
    mhtml_contents.emplace_back(WebFrameSerializer::GenerateMHTMLHeader(
        mhtml_boundary, GetWebFrame(), &delegate));
    if (mhtml_contents.back().IsEmpty())
      save_status = MhtmlSaveStatus::FRAME_SERIALIZATION_FORBIDDEN;
    else
      has_some_data = true;
  }

  if (save_status == MhtmlSaveStatus::SUCCESS) {
    TRACE_EVENT0("page-serialization",
                 "RenderFrameImpl::OnSerializeAsMHTML parts serialization");
    mhtml_contents.emplace_back(WebFrameSerializer::GenerateMHTMLParts(
        mhtml_boundary, GetWebFrame(), &delegate));
    has_some_data |= !mhtml_contents.back().IsEmpty();
  }


  base::TimeDelta main_thread_use_time = base::TimeTicks::Now() - start_time;
  UMA_HISTOGRAM_TIMES(
      "PageSerialization.MhtmlGeneration.RendererMainThreadTime.SingleFrame",
      main_thread_use_time);

  if (save_status == MhtmlSaveStatus::SUCCESS && has_some_data) {
    base::PostTaskAndReplyWithResult(
        RenderThreadImpl::current()->GetFileThreadTaskRunner().get(), FROM_HERE,
        base::Bind(&WriteMHTMLToDisk, base::Passed(&mhtml_contents),
                   base::Passed(&file)),
        base::Bind(&RenderFrameImpl::OnWriteMHTMLToDiskComplete,
                   weak_factory_.GetWeakPtr(), params.job_id,
                   base::Passed(&serialized_resources_uri_digests),
                   main_thread_use_time));
  } else {
    file.Close();
    OnWriteMHTMLToDiskComplete(params.job_id, serialized_resources_uri_digests,
                               main_thread_use_time, save_status);
  }
}
