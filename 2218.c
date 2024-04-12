wkbReadPointP(wkbObj *w, pointObj *p)
{
  memcpy(&(p->x), w->ptr, sizeof(double));
  w->ptr += sizeof(double);
  memcpy(&(p->y), w->ptr, sizeof(double));
  w->ptr += sizeof(double);
}
