bool effect_exists(effect_context_t *context)
{
 struct listnode *node;

    list_for_each(node, &created_effects_list) {
 effect_context_t *fx_ctxt = node_to_item(node,
 effect_context_t,
                                                 effects_list_node);
 if (fx_ctxt == context) {
 return true;
 }
 }
 return false;
}
