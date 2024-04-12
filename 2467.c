AuthenticatorGenericErrorSheetModel::AuthenticatorGenericErrorSheetModel(
    AuthenticatorRequestDialogModel* dialog_model,
    base::string16 title,
    base::string16 description)
    : AuthenticatorSheetModelBase(dialog_model),
      title_(std::move(title)),
      description_(std::move(description)) {}
