  UIDNAWrapper() {
    UErrorCode err = U_ZERO_ERROR;
    value = uidna_openUTS46(UIDNA_CHECK_BIDI, &err);
    CHECK(U_SUCCESS(err)) << "failed to open UTS46 data with error: "
                          << u_errorName(err)
                          << ". If you see this error message in a test "
                          << "environment your test environment likely lacks "
                          << "the required data tables for libicu. See "
                          << "https://crbug.com/778929.";
  }
