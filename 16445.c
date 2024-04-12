void BindImageAnnotator(image_annotation::mojom::AnnotatorRequest request,
                        RenderFrameHost* const frame_host) {
  content::BrowserContext::GetConnectorFor(
      frame_host->GetProcess()->GetBrowserContext())
      ->BindInterface(image_annotation::mojom::kServiceName,
                      std::move(request));
}
