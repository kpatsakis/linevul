 CreateTransformWithCompositorElementId(
     const CompositorElementId& compositor_element_id) {
   TransformPaintPropertyNode::State state;
  state.compositor_element_id = compositor_element_id;
  return TransformPaintPropertyNode::Create(TransformPaintPropertyNode::Root(),
                                             std::move(state));
 }
