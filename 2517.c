WebMediaPlayer* RenderView::createMediaPlayer(
    WebFrame* frame, WebMediaPlayerClient* client) {
  FOR_EACH_OBSERVER(
      RenderViewObserver, observers_, WillCreateMediaPlayer(frame, client));

  scoped_ptr<media::MessageLoopFactory> message_loop_factory(
      new media::MessageLoopFactoryImpl());
  scoped_ptr<media::FilterCollection> collection(
      new media::FilterCollection());

  const CommandLine* cmd_line = CommandLine::ForCurrentProcess();
  if (!cmd_line->HasSwitch(switches::kDisableAudio)) {
    collection->AddAudioRenderer(new AudioRendererImpl());
  }

  scoped_refptr<webkit_glue::WebVideoRenderer> video_renderer;
  bool pts_logging = cmd_line->HasSwitch(switches::kEnableVideoLogging);
  scoped_refptr<webkit_glue::VideoRendererImpl> renderer(
      new webkit_glue::VideoRendererImpl(pts_logging));
  collection->AddVideoRenderer(renderer);
  video_renderer = renderer;

  scoped_ptr<webkit_glue::WebMediaPlayerImpl> result(
      new webkit_glue::WebMediaPlayerImpl(client,
                                          collection.release(),
                                          message_loop_factory.release(),
                                          media_stream_impl_.get()));
  if (!result->Initialize(frame,
                          cmd_line->HasSwitch(switches::kSimpleDataSource),
                          video_renderer)) {
    return NULL;
  }
  return result.release();
}
