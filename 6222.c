void TestPresentationLocksFocusImpl(WebXrVrBrowserTestBase* t,
                                    std::string filename) {
  t->LoadUrlAndAwaitInitialization(t->GetFileUrlForHtmlTestFile(filename));
  t->EnterSessionWithUserGestureOrFail();
  t->ExecuteStepAndWait("stepSetupFocusLoss()");
  t->EndTest();
}
