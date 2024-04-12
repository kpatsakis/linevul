string16 GetUrlWithLang(const GURL& url) {
  return ASCIIToUTF16(google_util::AppendGoogleLocaleParam(url).spec());
}
