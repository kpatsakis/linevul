void PageHandler::GotManifest(std::unique_ptr<GetAppManifestCallback> callback,
                              const GURL& manifest_url,
                              blink::mojom::ManifestDebugInfoPtr debug_info) {
  std::unique_ptr<Array<Page::AppManifestError>> errors =
      Array<Page::AppManifestError>::create();
  bool failed = true;
  if (debug_info) {
    failed = false;
    for (const auto& error : debug_info->errors) {
      errors->addItem(Page::AppManifestError::Create()
                          .SetMessage(error->message)
                          .SetCritical(error->critical)
                          .SetLine(error->line)
                          .SetColumn(error->column)
                          .Build());
      if (error->critical)
        failed = true;
    }
  }
  callback->sendSuccess(
      manifest_url.possibly_invalid_spec(), std::move(errors),
      failed ? Maybe<std::string>() : debug_info->raw_manifest);
}
