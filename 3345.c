static bool IsOfficeType(const std::string& type_hint) {
  return (type_hint == "application/msword" ||
          type_hint == "application/vnd.ms-excel" ||
          type_hint == "application/vnd.ms-powerpoint" ||
          type_hint == "application/vnd.openxmlformats-officedocument."
                       "wordprocessingml.document" ||
          type_hint == "application/vnd.openxmlformats-officedocument."
                       "spreadsheetml.sheet" ||
          type_hint == "application/vnd.openxmlformats-officedocument."
                       "presentationml.presentation" ||
          type_hint == "application/vnd.ms-excel.sheet.macroenabled.12" ||
          type_hint == "application/vnd.ms-word.document.macroenabled.12" ||
          type_hint == "application/vnd.ms-powerpoint.presentation."
                       "macroenabled.12" ||
          type_hint == "application/mspowerpoint" ||
          type_hint == "application/msexcel" ||
          type_hint == "application/vnd.ms-word" ||
          type_hint == "application/vnd.ms-word.document.12" ||
          type_hint == "application/vnd.msword");
}
