    static gboolean detachCallback(WebKitWebInspector*, InspectorTest* test)
    {
        return test->detach();
    }
