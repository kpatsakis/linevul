media::CdmFactory* RenderFrameImpl::GetCdmFactory() {
#if defined(ENABLE_BROWSER_CDMS)
  if (!cdm_manager_)
    cdm_manager_ = new RendererCdmManager(this);
#endif  // defined(ENABLE_BROWSER_CDMS)

  if (!cdm_factory_) {
    DCHECK(frame_);

#if defined(ENABLE_MOJO_MEDIA)
    cdm_factory_.reset(new media::MojoCdmFactory(GetMediaServiceFactory()));
#else
    cdm_factory_.reset(new RenderCdmFactory(
#if defined(ENABLE_PEPPER_CDMS)
        base::Bind(&PepperCdmWrapperImpl::Create, frame_)
#elif defined(ENABLE_BROWSER_CDMS)
        cdm_manager_
#endif
        ));
#endif  //  defined(ENABLE_MOJO_MEDIA)
  }

  return cdm_factory_.get();
}
