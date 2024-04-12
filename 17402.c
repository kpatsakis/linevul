void SVGElement::MapInstanceToElement(SVGElement* instance) {
  DCHECK(instance);
  DCHECK(instance->InUseShadowTree());

  HeapHashSet<WeakMember<SVGElement>>& instances =
      EnsureSVGRareData()->ElementInstances();
  DCHECK(!instances.Contains(instance));

  instances.insert(instance);
}
