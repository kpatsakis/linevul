    void test(TestCase testCase)
    {
        MockHTMLResourcePreloader preloader;
        KURL baseURL(ParsedURLString, testCase.baseURL);
        m_scanner->appendToEnd(String(testCase.inputHTML));
        m_scanner->scanAndPreload(&preloader, baseURL, nullptr);

        preloader.preloadRequestVerification(testCase.type, testCase.preloadedURL, testCase.outputBaseURL, testCase.resourceWidth, testCase.preferences);
    }
