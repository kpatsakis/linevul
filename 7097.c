void BlacklistAddOneDll(const wchar_t* module_name,
                        bool check_in_browser,
                        sandbox::TargetPolicy* policy) {
  HMODULE module = check_in_browser ? ::GetModuleHandleW(module_name) : NULL;
  if (!module) {
    std::wstring name(module_name);
    size_t period = name.rfind(L'.');
    DCHECK_NE(std::string::npos, period);
    DCHECK_LE(3U, (name.size() - period));
    if (period <= 8)
      return;
    for (int ix = 0; ix < 3; ++ix) {
      const wchar_t suffix[] = {'~', ('1' + ix), 0};
      std::wstring alt_name = name.substr(0, 6) + suffix;
      alt_name += name.substr(period, name.size());
      if (check_in_browser) {
        module = ::GetModuleHandleW(alt_name.c_str());
        if (!module)
          return;
        if (!IsExpandedModuleName(module, module_name))
          return;
      }
      policy->AddDllToUnload(alt_name.c_str());
    }
  }
  policy->AddDllToUnload(module_name);
  DVLOG(1) << "dll to unload found: " << module_name;
  return;
}
