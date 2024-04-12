void DemangleSymbols(std::string* text) {

#if defined(__GLIBCXX__) && !defined(__UCLIBC__)

  std::string::size_type search_from = 0;
  while (search_from < text->size()) {
    std::string::size_type mangled_start =
        text->find(kMangledSymbolPrefix, search_from);
    if (mangled_start == std::string::npos) {
      break;  // Mangled symbol not found.
    }

    std::string::size_type mangled_end =
        text->find_first_not_of(kSymbolCharacters, mangled_start);
    if (mangled_end == std::string::npos) {
      mangled_end = text->size();
    }
    std::string mangled_symbol =
        text->substr(mangled_start, mangled_end - mangled_start);

    int status = 0;
    scoped_ptr<char, base::FreeDeleter> demangled_symbol(
        abi::__cxa_demangle(mangled_symbol.c_str(), NULL, 0, &status));
    if (status == 0) {  // Demangling is successful.
      text->erase(mangled_start, mangled_end - mangled_start);
      text->insert(mangled_start, demangled_symbol.get());
      search_from = mangled_start + strlen(demangled_symbol.get());
    } else {
      search_from = mangled_start + 2;
    }
  }

#endif  // defined(__GLIBCXX__) && !defined(__UCLIBC__)
}
