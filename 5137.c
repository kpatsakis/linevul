  void CreateDefaultSearchWithAdditionalJsonData(
      const std::string additional_json_data) {
    CreateDefaultSearchContextAndRequestSearchTerm();
    fetcher()->set_response_code(200);
    std::string response =
        escapeBarQuoted("{|search_term|:|obama|" + additional_json_data + "}");
    fetcher()->SetResponseString(response);
    fetcher()->delegate()->OnURLFetchComplete(fetcher());

    EXPECT_FALSE(is_invalid());
    EXPECT_EQ(200, response_code());
    EXPECT_EQ("obama", search_term());
  }
