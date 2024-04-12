error::Error DeleteHelper(GLsizei n,
                          const volatile ClientType* client_ids,
                          ClientServiceMap<ClientType, ServiceType>* id_map,
                          DeleteFunction delete_function) {
  DCHECK(n >= 0);
  std::vector<ServiceType> service_ids(n, 0);
  for (GLsizei ii = 0; ii < n; ++ii) {
    ClientType client_id = client_ids[ii];

    if (client_id != 0) {
      service_ids[ii] = id_map->GetServiceIDOrInvalid(client_id);
      id_map->RemoveClientID(client_id);
    }
  }

  delete_function(n, service_ids.data());

  return error::kNoError;
}
