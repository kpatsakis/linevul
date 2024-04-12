static void SetupSettingsAutofillPageTest(Profile* profile,
                                          const char* first_name,
                                          const char* middle_name,
                                          const char* last_name,
                                          const char* email,
                                          const char* company,
                                          const char* address1,
                                          const char* address2,
                                          const char* city,
                                          const char* state,
                                          const char* zipcode,
                                          const char* country,
                                          const char* phone) {
  autofill_test::DisableSystemServices(profile);
  AutofillProfile autofill_profile;
  autofill_test::SetProfileInfo(&autofill_profile,
                                first_name,
                                middle_name,
                                last_name,
                                email,
                                company,
                                address1,
                                address2,
                                city,
                                state,
                                zipcode,
                                country,
                                phone);
  PersonalDataManager* personal_data_manager =
      PersonalDataManagerFactory::GetForProfile(profile);
  ASSERT_TRUE(personal_data_manager);
  personal_data_manager->AddProfile(autofill_profile);
}
