static void xsltFixImportedCompSteps(xsltStylesheetPtr master,
			xsltStylesheetPtr style) {
    xsltStylesheetPtr res;
    xmlHashScan(style->templatesHash,
	            (xmlHashScanner) xsltNormalizeCompSteps, master);
    master->extrasNr += style->extrasNr;
    for (res = style->imports; res != NULL; res = res->next) {
        xsltFixImportedCompSteps(master, res);
    }
}
