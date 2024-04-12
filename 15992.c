void LoadingPredictor::PrepareForPageLoad(const GURL& url,
                                          HintOrigin origin,
                                          bool preconnectable) {
  if (shutdown_)
    return;

  if (origin == HintOrigin::OMNIBOX) {
    HandleOmniboxHint(url, preconnectable);
    return;
  }

  if (active_hints_.find(url) != active_hints_.end())
    return;

  bool has_preconnect_prediction = false;
  PreconnectPrediction prediction;
  has_preconnect_prediction =
      resource_prefetch_predictor_->PredictPreconnectOrigins(url, &prediction);
  has_preconnect_prediction =
      AddInitialUrlToPreconnectPrediction(url, &prediction);

  if (!has_preconnect_prediction)
    return;

  ++total_hints_activated_;
  active_hints_.emplace(url, base::TimeTicks::Now());
  if (IsPreconnectAllowed(profile_))
    MaybeAddPreconnect(url, std::move(prediction.requests), origin);
}
