void LoadingDataCollector::RecordFirstContentfulPaint(
    const NavigationID& navigation_id,
    const base::TimeTicks& first_contentful_paint) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  auto nav_it = inflight_navigations_.find(navigation_id);
  if (nav_it != inflight_navigations_.end())
    nav_it->second->first_contentful_paint = first_contentful_paint;
}
