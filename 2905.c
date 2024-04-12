StringBuilder& StringBuilder::append(const StringPiece16& str) {
 if (!mError.empty()) {
 return *this;
 }

 const char16_t* const end = str.end();
 const char16_t* start = str.begin();
 const char16_t* current = start;
 while (current != end) {
 if (mLastCharWasEscape) {
 switch (*current) {
 case u't':
                    mStr += u'\t';
 break;
 case u'n':
                    mStr += u'\n';
 break;
 case u'#':
                    mStr += u'#';
 break;
 case u'@':
                    mStr += u'@';
 break;
 case u'?':
                    mStr += u'?';
 break;
 case u'"':
                    mStr += u'"';
 break;
 case u'\'':
                    mStr += u'\'';
 break;
 case u'\\':
                    mStr += u'\\';
 break;
 case u'u': {
                    current++;
 Maybe<char16_t> c = parseUnicodeCodepoint(&current, end);
 if (!c) {
                        mError = "invalid unicode escape sequence";
 return *this;
 }
                    mStr += c.value();
                    current -= 1;
 break;
 }

 default:
 break;
 }
            mLastCharWasEscape = false;
            start = current + 1;
 } else if (*current == u'"') {
 if (!mQuote && mTrailingSpace) {
 if (mTrailingSpace) {
 if (!mStr.empty()) {
                        mStr += u' ';
 }
                    mTrailingSpace = false;
 }
 }
            mQuote = !mQuote;
            mStr.append(start, current - start);
            start = current + 1;
 } else if (*current == u'\'' && !mQuote) {
            mError = "unescaped apostrophe";
 return *this;
 } else if (*current == u'\\') {
 if (!mQuote && mTrailingSpace) {
 if (!mStr.empty()) {
                    mStr += u' ';
 }
                mTrailingSpace = false;
 }
            mStr.append(start, current - start);
            start = current + 1;
            mLastCharWasEscape = true;
 } else if (!mQuote) {
 if (isspace16(*current)) {
 if (!mTrailingSpace) {
                    mTrailingSpace = true;
                    mStr.append(start, current - start);
 }

                start = current + 1;
 } else if (mTrailingSpace) {
 if (!mStr.empty()) {
                    mStr += u' ';
 }
                mTrailingSpace = false;
 }
 }
        current++;
 }
    mStr.append(start, end - start);
 return *this;
}
