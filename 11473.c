PP_Bool Paint(PP_Resource resource,
              const PP_Rect* rect,
              PP_Resource image_id) {
  scoped_refptr<PPB_Widget_Impl> widget(
      Resource::GetAs<PPB_Widget_Impl>(resource));
  if (!widget)
    return PP_FALSE;

  scoped_refptr<PPB_ImageData_Impl> image(
      Resource::GetAs<PPB_ImageData_Impl>(image_id));
  if (!image)
    return PP_FALSE;

  return BoolToPPBool(widget->Paint(rect, image));
}
