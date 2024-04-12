  void OnSetIsInert(bool is_inert) {
    base::PostTaskWithTraits(
        FROM_HERE, {content::BrowserThread::UI},
        base::BindOnce(&SetIsInertMessageFilter::OnSetIsInertOnUI, this,
                       is_inert));
  }
