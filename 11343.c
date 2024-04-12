void RenderFrameImpl::RegisterMojoServices() {
  if (!frame_->parent()) {
    GetServiceRegistry()->AddService<image_downloader::ImageDownloader>(
        base::Bind(&ImageDownloaderImpl::CreateMojoService,
                   base::Unretained(this)));
   }
 }
