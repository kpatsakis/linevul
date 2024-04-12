WebMediaPlayer::LoadTiming WebMediaPlayerImpl::Load(
    LoadType load_type,
    const blink::WebMediaPlayerSource& source,
    CORSMode cors_mode) {
  DVLOG(1) << __func__;
  DCHECK(source.IsURL());
  blink::WebURL url = source.GetAsURL();
  DVLOG(1) << __func__ << "(" << load_type << ", " << GURL(url) << ", "
           << cors_mode << ")";

  bool is_deferred = false;

  if (!defer_load_cb_.is_null()) {
    is_deferred = defer_load_cb_.Run(base::BindOnce(
        &WebMediaPlayerImpl::DoLoad, AsWeakPtr(), load_type, url, cors_mode));
  } else {
    DoLoad(load_type, url, cors_mode);
  }

  return is_deferred ? LoadTiming::kDeferred : LoadTiming::kImmediate;
}
