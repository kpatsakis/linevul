void HTMLMediaElement::AudioSourceProviderImpl::wrap(
    WebAudioSourceProvider* provider) {
  MutexLocker locker(provideInputLock);

  if (m_webAudioSourceProvider && provider != m_webAudioSourceProvider)
    m_webAudioSourceProvider->setClient(nullptr);

  m_webAudioSourceProvider = provider;
  if (m_webAudioSourceProvider)
    m_webAudioSourceProvider->setClient(m_client.get());
}
