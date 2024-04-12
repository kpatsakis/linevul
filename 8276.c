TestObserver::TestObserver(ResourcePrefetchPredictor* predictor)
    : predictor_(predictor) {
  predictor_->SetObserverForTesting(this);
}
