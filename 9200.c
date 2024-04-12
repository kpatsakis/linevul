xpathExprTest(const char *filename, const char *result,
              const char *err ATTRIBUTE_UNUSED,
              int options ATTRIBUTE_UNUSED) {
    return(xpathCommonTest(filename, result, 0, 1));
}
