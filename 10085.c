  void ShowLocalBubble() {
    controller()->ShowBubbleForLocalSave(CreditCard(),
                                         base::Bind(&SaveCardCallback));
  }
