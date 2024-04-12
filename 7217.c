PP_Bool ReadImageData(PP_Resource device_context_2d,
                      PP_Resource image,
                      const PP_Point* top_left) {
  EnterResource<PPB_Graphics2D_API> enter(device_context_2d, true);
  if (enter.failed())
    return PP_FALSE;
  return BoolToPPBool(static_cast<PPB_Graphics2D_Impl*>(enter.object())->
      ReadImageData(image, top_left));
}
