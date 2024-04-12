const char* PassphraseRequiredReasonToString(
    PassphraseRequiredReason reason) {
  switch (reason) {
    case REASON_PASSPHRASE_NOT_REQUIRED:
      return "REASON_PASSPHRASE_NOT_REQUIRED";
    case REASON_ENCRYPTION:
      return "REASON_ENCRYPTION";
    case REASON_DECRYPTION:
      return "REASON_DECRYPTION";
    default:
      NOTREACHED();
      return "INVALID_REASON";
  }
}
