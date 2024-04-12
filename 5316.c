bool AXObject::nameFromContents() const {
  switch (roleValue()) {
    case AnchorRole:
    case ButtonRole:
    case CheckBoxRole:
    case DirectoryRole:
    case DisclosureTriangleRole:
    case HeadingRole:
    case LineBreakRole:
    case LinkRole:
    case ListBoxOptionRole:
    case ListItemRole:
    case MenuItemRole:
    case MenuItemCheckBoxRole:
    case MenuItemRadioRole:
    case MenuListOptionRole:
    case PopUpButtonRole:
    case RadioButtonRole:
    case StaticTextRole:
    case StatusRole:
    case SwitchRole:
    case TabRole:
    case ToggleButtonRole:
    case TreeItemRole:
      return true;
    default:
      return false;
  }
}
