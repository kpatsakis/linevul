 string16 Accelerator::GetShortcutText() const {
   int string_id = 0;
   switch(key_code_) {
    case ui::VKEY_TAB:
      string_id = IDS_APP_TAB_KEY;
      break;
    case ui::VKEY_RETURN:
      string_id = IDS_APP_ENTER_KEY;
      break;
    case ui::VKEY_ESCAPE:
      string_id = IDS_APP_ESC_KEY;
      break;
    case ui::VKEY_PRIOR:
      string_id = IDS_APP_PAGEUP_KEY;
      break;
    case ui::VKEY_NEXT:
      string_id = IDS_APP_PAGEDOWN_KEY;
      break;
    case ui::VKEY_END:
      string_id = IDS_APP_END_KEY;
      break;
    case ui::VKEY_HOME:
      string_id = IDS_APP_HOME_KEY;
      break;
    case ui::VKEY_INSERT:
      string_id = IDS_APP_INSERT_KEY;
      break;
    case ui::VKEY_DELETE:
      string_id = IDS_APP_DELETE_KEY;
      break;
    case ui::VKEY_LEFT:
      string_id = IDS_APP_LEFT_ARROW_KEY;
      break;
    case ui::VKEY_RIGHT:
      string_id = IDS_APP_RIGHT_ARROW_KEY;
      break;
    case ui::VKEY_BACK:
      string_id = IDS_APP_BACKSPACE_KEY;
      break;
    case ui::VKEY_F1:
      string_id = IDS_APP_F1_KEY;
      break;
    case ui::VKEY_F11:
      string_id = IDS_APP_F11_KEY;
      break;
    default:
      break;
  }

  string16 shortcut;
  if (!string_id) {
#if defined(OS_WIN)
    wchar_t key;
    if (key_code_ >= '0' && key_code_ <= '9')
      key = key_code_;
    else
      key = LOWORD(::MapVirtualKeyW(key_code_, MAPVK_VK_TO_CHAR));
    shortcut += key;
#elif defined(USE_AURA)
    const uint16 c = GetCharacterFromKeyCode(key_code_, false);
    if (c != 0) {
      shortcut += static_cast<string16::value_type>(base::ToUpperASCII(c));
    }
#elif defined(TOOLKIT_GTK)
    const gchar* name = NULL;
    switch (key_code_) {
      case ui::VKEY_OEM_2:
        name = static_cast<const gchar*>("/");
        break;
      default:
        name = gdk_keyval_name(gdk_keyval_to_lower(key_code_));
        break;
    }
    if (name) {
      if (name[0] != 0 && name[1] == 0)
        shortcut += static_cast<string16::value_type>(g_ascii_toupper(name[0]));
      else
        shortcut += UTF8ToUTF16(name);
    }
#endif
  } else {
    shortcut = l10n_util::GetStringUTF16(string_id);
  }

  string16 shortcut_rtl;
  bool adjust_shortcut_for_rtl = false;
  if (base::i18n::IsRTL() && shortcut.length() == 1 &&
      !IsAsciiAlpha(shortcut[0]) && !IsAsciiDigit(shortcut[0])) {
    adjust_shortcut_for_rtl = true;
    shortcut_rtl.assign(shortcut);
  }

  if (IsShiftDown())
    shortcut = l10n_util::GetStringFUTF16(IDS_APP_SHIFT_MODIFIER, shortcut);

  if (IsCtrlDown())
    shortcut = l10n_util::GetStringFUTF16(IDS_APP_CONTROL_MODIFIER, shortcut);
  else if (IsAltDown())
    shortcut = l10n_util::GetStringFUTF16(IDS_APP_ALT_MODIFIER, shortcut);

  if (adjust_shortcut_for_rtl) {
    int key_length = static_cast<int>(shortcut_rtl.length());
    DCHECK_GT(key_length, 0);
    shortcut_rtl.append(ASCIIToUTF16("+"));

    shortcut_rtl.append(shortcut, 0, shortcut.length() - key_length - 1);
    shortcut.swap(shortcut_rtl);
  }

  return shortcut;
}
