  int AggregateProfilesIntoAutofillPrefs(const std::string& filename) {
    CHECK(test_server()->Start());

    std::string data;
    base::FilePath data_file =
        ui_test_utils::GetTestFilePath(base::FilePath().AppendASCII("autofill"),
                                       base::FilePath().AppendASCII(filename));
    CHECK(file_util::ReadFileToString(data_file, &data));
    std::vector<std::string> lines;
    base::SplitString(data, '\n', &lines);
    for (size_t i = 0; i < lines.size(); ++i) {
      if (StartsWithASCII(lines[i], "#", false))
        continue;
      std::vector<std::string> fields;
      base::SplitString(lines[i], '|', &fields);
      if (fields.empty())
        continue;  // Blank line.
      CHECK_EQ(12u, fields.size());

      FormMap data;
      data["NAME_FIRST"] = fields[0];
      data["NAME_MIDDLE"] = fields[1];
      data["NAME_LAST"] = fields[2];
      data["EMAIL_ADDRESS"] = fields[3];
      data["COMPANY_NAME"] = fields[4];
      data["ADDRESS_HOME_LINE1"] = fields[5];
      data["ADDRESS_HOME_LINE2"] = fields[6];
      data["ADDRESS_HOME_CITY"] = fields[7];
      data["ADDRESS_HOME_STATE"] = fields[8];
      data["ADDRESS_HOME_ZIP"] = fields[9];
      data["ADDRESS_HOME_COUNTRY"] = fields[10];
      data["PHONE_HOME_WHOLE_NUMBER"] = fields[11];

      FillFormAndSubmit("duplicate_profiles_test.html", data);
    }
    return lines.size();
  }
