void AudioRendererHost::OnCreated(media::AudioOutputController* controller) {
  BrowserThread::PostTask(
      BrowserThread::IO,
      FROM_HERE,
      base::Bind(
          &AudioRendererHost::DoCompleteCreation,
          this,
          make_scoped_refptr(controller)));
}
