content::ColorChooser* ShowColorChooser(content::WebContents* web_contents,
                                        SkColor initial_color) {
#if defined(USE_ASH)
  gfx::NativeView native_view = web_contents->GetView()->GetNativeView();
  if (GetHostDesktopTypeForNativeView(native_view) == HOST_DESKTOP_TYPE_ASH)
    return ColorChooserAura::Open(web_contents, initial_color);
#endif
  return ColorChooserWin::Open(web_contents, initial_color);
}
