  explicit DeleteCacheCompletionCallback(MockHttpCache* cache)
      : cache_(cache),
        ALLOW_THIS_IN_INITIALIZER_LIST(callback_(
            base::Bind(&DeleteCacheCompletionCallback::OnComplete,
                       base::Unretained(this)))) {
  }
