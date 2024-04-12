  int IsExtendedReportingCheckboxVisibleOnInterstitial() {
    const std::string command = base::StringPrintf(
        "var node = document.getElementById('extended-reporting-opt-in');"
        "if (node) {"
        "  window.domAutomationController.send(node.offsetWidth > 0 || "
        "      node.offsetHeight > 0 ? %d : %d);"
        "} else {"
        "  window.domAutomationController.send(%d);"
        "}",
        security_interstitials::CMD_TEXT_FOUND,
        security_interstitials::CMD_TEXT_NOT_FOUND,
        security_interstitials::CMD_ERROR);

    content::WebContents* tab =
        browser()->tab_strip_model()->GetActiveWebContents();
    WaitForInterstitial(tab);
    int result = 0;
    EXPECT_TRUE(content::ExecuteScriptAndExtractInt(
        AreCommittedInterstitialsEnabled()
            ? tab->GetMainFrame()
            : tab->GetInterstitialPage()->GetMainFrame(),
        command, &result));
    return result;
  }
