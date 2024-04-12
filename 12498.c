  void InitTextfields(int count) {
    ASSERT_FALSE(textfield_);
    textfield_ = new TestTextfield();
    textfield_->set_controller(this);
    widget_ = new Widget();

    Widget::InitParams params =
        CreateParams(Widget::InitParams::TYPE_WINDOW_FRAMELESS);

    params.bounds = gfx::Rect(100, 100, 100, 100);
    widget_->Init(params);
    input_method_->SetDelegate(
        test::WidgetTest::GetInputMethodDelegateForWidget(widget_));
    View* container = new View();
    widget_->SetContentsView(container);
    container->AddChildView(textfield_);
    textfield_->SetBoundsRect(params.bounds);
    textfield_->set_id(1);
    test_api_.reset(new TextfieldTestApi(textfield_));

    for (int i = 1; i < count; i++) {
      Textfield* textfield = new Textfield();
      container->AddChildView(textfield);
      textfield->set_id(i + 1);
    }

    model_ = test_api_->model();
    model_->ClearEditHistory();

    widget_->Show();
    textfield_->RequestFocus();

    event_generator_.reset(
        new ui::test::EventGenerator(widget_->GetNativeWindow()));
    event_generator_->set_target(ui::test::EventGenerator::Target::WINDOW);
  }
