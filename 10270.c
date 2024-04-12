void CheckNextNameValuePair(HttpUtil::NameValuePairsIterator* parser,
                            bool expect_next,
                            bool expect_valid,
                            std::string expected_name,
                            std::string expected_value) {
  ASSERT_EQ(expect_next, parser->GetNext());
  ASSERT_EQ(expect_valid, parser->valid());
  if (!expect_next || !expect_valid) {
    return;
  }

  CheckCurrentNameValuePair(parser,
                            expect_valid,
                            expected_name,
                            expected_value);
}
