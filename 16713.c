content::ColorChooser* Browser::OpenColorChooser(WebContents* web_contents,
                                                 int color_chooser_id,
                                                 SkColor color) {
#if defined(OS_WIN)
  if (!color_chooser_.get())
    color_chooser_.reset(content::ColorChooser::Create(color_chooser_id,
                                                       web_contents,
                                                       color));
#else
  if (color_chooser_.get())
    color_chooser_->End();
  color_chooser_.reset(content::ColorChooser::Create(color_chooser_id,
                                                     web_contents,
                                                     color));
#endif
  return color_chooser_.get();
}
