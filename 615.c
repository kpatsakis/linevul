AppListControllerDelegate* ExtensionAppItem::GetController() {
  return AppListService::Get(chrome::GetActiveDesktop())->
      GetControllerDelegate();
}
