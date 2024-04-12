bool isJavaPackageName(const StringPiece16& str) {
 if (str.empty()) {
 return false;
 }

 size_t pieces = 0;
 for (const StringPiece16& piece : tokenize(str, u'.')) {
        pieces++;
 if (piece.empty()) {
 return false;
 }

 if (piece.data()[0] == u'_' || piece.data()[piece.size() - 1] == u'_') {
 return false;
 }

 if (findNonAlphaNumericAndNotInSet(piece, u"_") != piece.end()) {
 return false;
 }
 }
 return pieces >= 1;
}
