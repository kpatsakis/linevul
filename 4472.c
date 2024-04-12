void ExpectFilledCreditCardYearMonthWithYearMonth(int page_id,
                                                  const FormData& filled_form,
                                                  int expected_page_id,
                                                  bool has_address_fields,
                                                  const char* year,
                                                  const char* month) {
  ExpectFilledForm(page_id, filled_form, expected_page_id, "", "", "", "", "",
                   "", "", "", "", "", "", "Miku Hatsune", "4234567890654321",
                   month, year, has_address_fields, true, true);
}
