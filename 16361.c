bool StartsWithCommandLineGoogleBaseURL(const GURL& url) {
  const GURL& base_url(CommandLineGoogleBaseURL());
  return base_url.is_valid() &&
         base::StartsWith(url.possibly_invalid_spec(), base_url.spec(),
                          base::CompareCase::SENSITIVE);
}
