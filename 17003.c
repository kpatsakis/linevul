  static AppListController* GetInstance() {
    return Singleton<AppListController,
                     LeakySingletonTraits<AppListController> >::get();
  }
