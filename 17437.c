  virtual void Init() {
#if defined(OS_WIN)
    CoInitialize(NULL);
#endif

    render_process_ = new RenderProcess();
    render_process_->set_main_thread(new RenderThread(channel_id_));
    base::Thread::SetThreadWasQuitProperly(true);
  }
