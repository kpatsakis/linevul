static int AddChannel(int val,
               int adder) {
  Fixed sum = static_cast<Fixed>(val) + static_cast<Fixed>(adder);
  if (sum > max_value)
    return max_value;
  if (sum < min_value)
    return min_value;
  return static_cast<int>(sum);
}
