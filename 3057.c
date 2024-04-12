  void OnRedirectQueryComplete(std::vector<GURL>* rv,
                               const history::RedirectList* redirects) {
    rv->insert(rv->end(), redirects->begin(), redirects->end());
    base::ThreadTaskRunnerHandle::Get()->PostTask(
        FROM_HERE, base::MessageLoop::QuitWhenIdleClosure());
  }
