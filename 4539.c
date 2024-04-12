HTMLImportsController::HTMLImportsController(Document& master)
     : root_(HTMLImportTreeRoot::Create(&master)) {}
