TestingAutomationProvider::TestingAutomationProvider(Profile* profile)
    : AutomationProvider(profile),
#if defined(TOOLKIT_VIEWS)
      popup_menu_waiter_(NULL),
#endif
#if defined(OS_CHROMEOS)
      power_manager_observer_(NULL),
#endif
      redirect_query_(0) {
  BrowserList::AddObserver(this);
  registrar_.Add(this, chrome::NOTIFICATION_SESSION_END,
                 content::NotificationService::AllSources());
#if defined(OS_CHROMEOS)
  AddChromeosObservers();
#endif
}
