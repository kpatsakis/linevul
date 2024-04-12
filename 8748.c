static bool is_valid(const char *test_name) {
 for (size_t i = 0; i < sanity_suite_size; ++i) {
 if (!strcmp(test_name, sanity_suite[i].function_name)) {
 return true;
 }
 }
 for (size_t i = 0; i < test_suite_size; ++i) {
 if (!strcmp(test_name, test_suite[i].function_name)) {
 return true;
 }
 }
 return false;
}
