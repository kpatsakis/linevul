void LockScreenMediaControlsView::MediaControllerImageChanged(
    media_session::mojom::MediaSessionImageType type,
    const SkBitmap& bitmap) {
  if (hide_controls_timer_->IsRunning())
    return;

  SkBitmap converted_bitmap;
  if (bitmap.colorType() == kN32_SkColorType) {
    converted_bitmap = bitmap;
  } else {
    SkImageInfo info = bitmap.info().makeColorType(kN32_SkColorType);
    if (converted_bitmap.tryAllocPixels(info)) {
      bitmap.readPixels(info, converted_bitmap.getPixels(),
                        converted_bitmap.rowBytes(), 0, 0);
    }
  }

  switch (type) {
    case media_session::mojom::MediaSessionImageType::kArtwork: {
      base::Optional<gfx::ImageSkia> session_artwork =
          gfx::ImageSkia::CreateFrom1xBitmap(converted_bitmap);
      SetArtwork(session_artwork);
      break;
    }
    case media_session::mojom::MediaSessionImageType::kSourceIcon: {
      gfx::ImageSkia session_icon =
          gfx::ImageSkia::CreateFrom1xBitmap(converted_bitmap);
      if (session_icon.isNull()) {
        session_icon = gfx::CreateVectorIcon(message_center::kProductIcon,
                                             kIconSize, gfx::kChromeIconGrey);
      }
      header_row_->SetAppIcon(session_icon);
    }
  }
}
