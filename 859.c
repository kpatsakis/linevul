pp::URLLoader OutOfProcessInstance::CreateURLLoaderInternal() {
  pp::URLLoader loader(this);

  const PPB_URLLoaderTrusted* trusted_interface =
      reinterpret_cast<const PPB_URLLoaderTrusted*>(
          pp::Module::Get()->GetBrowserInterface(
              PPB_URLLOADERTRUSTED_INTERFACE));
  if (trusted_interface)
    trusted_interface->GrantUniversalAccess(loader.pp_resource());
  return loader;
}
