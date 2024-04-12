void Browser::RunFileChooser(content::RenderFrameHost* render_frame_host,
                             const content::FileChooserParams& params) {
  FileSelectHelper::RunFileChooser(render_frame_host, params);
}
