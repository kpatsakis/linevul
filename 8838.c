void ResourceMessageFilter::OnGetWindowRect(gfx::NativeViewId view,
                                            IPC::Message* reply_msg) {
   ChromeThread::PostTask(
      ChromeThread::BACKGROUND_X11, FROM_HERE,
      NewRunnableMethod(
          this, &ResourceMessageFilter::DoOnGetWindowRect, view, reply_msg));
}
