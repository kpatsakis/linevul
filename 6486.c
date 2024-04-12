int id_create(void *ptr)
{
  static int id = 0;
  id_link(++id, ptr);
  return id;
}
