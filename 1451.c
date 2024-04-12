 void Test_glInitializePPAPI() {
   GLboolean init_ppapi = glInitializePPAPI(ppb_get_interface());
   EXPECT(init_ppapi == true);
   TEST_PASSED;
 }
