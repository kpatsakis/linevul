double timeDelta(base::TimeTicks time,
                 base::TimeTicks start,
                 double invalid_value = -1) {
  return time.is_null() ? invalid_value : (time - start).InMillisecondsF();
}
