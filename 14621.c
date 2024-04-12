  void VisitAndAddFavicon(const GURL& page_url) {
    history_service_->AddPage(page_url, base::Time::Now(), nullptr, 0, GURL(),
        history::RedirectList(), ui::PAGE_TRANSITION_LINK,
        history::SOURCE_BROWSED, false);

    SkBitmap bitmap;
    bitmap.allocN32Pixels(gfx::kFaviconSize, gfx::kFaviconSize);
    bitmap.eraseColor(SK_ColorBLUE);
    favicon_service_->SetFavicons({page_url}, page_url,
                                  favicon_base::IconType::kFavicon,
                                  gfx::Image::CreateFrom1xBitmap(bitmap));
  }
