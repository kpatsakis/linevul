void ChromeContentRendererClient::OnPurgeMemory() {
  DVLOG(1) << "Resetting spellcheck in renderer client";
  RenderThread* thread = RenderThread::Get();
  if (spellcheck_.get())
    thread->RemoveObserver(spellcheck_.get());
  spellcheck_.reset(new SpellCheck());
  thread->AddObserver(spellcheck_.get());
}
