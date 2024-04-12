void XmlConfigParser::CharactersImpl(void* ctx, const xmlChar* ch, int len) {
  XmlConfigParser* context = FromContext(ctx);
  if (context->IsParsingData()) {
    context->master_prefs_ +=
        std::string(reinterpret_cast<const char*>(ch), len);
  }
}
