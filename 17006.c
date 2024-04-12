on_javascript_confirm(Ewk_View_Smart_Data *smartData, const char *message)
{
    Browser_Window *window = browser_view_find(smartData->self);

    Eina_Bool ok = EINA_FALSE;

    Evas_Object *confirm_popup = elm_popup_add(window->window);
    evas_object_size_hint_weight_set(confirm_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(confirm_popup, message);
    elm_object_part_text_set(confirm_popup, "title,text", "Confirmation");

    /* Popup buttons */
    Evas_Object *cancel_button = elm_button_add(confirm_popup);
    elm_object_text_set(cancel_button, "Cancel");
    elm_object_part_content_set(confirm_popup, "button1", cancel_button);
    evas_object_smart_callback_add(cancel_button, "clicked", quit_event_loop, NULL);
    Evas_Object *ok_button = elm_button_add(confirm_popup);
    elm_object_text_set(ok_button, "OK");
    elm_object_part_content_set(confirm_popup, "button2", ok_button);
    evas_object_smart_callback_add(ok_button, "clicked", on_ok_clicked, &ok);
    elm_object_focus_set(ok_button, EINA_TRUE);
    evas_object_show(confirm_popup);

    /* Make modal */
    ecore_main_loop_begin();

    evas_object_del(confirm_popup);

    return ok;
}
