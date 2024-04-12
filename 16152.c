 void CheckTMPrediction() const {
 for (int p = 0; p < num_planes_; p++)
 for (int y = 0; y < block_size_; y++)
 for (int x = 0; x < block_size_; x++) {
 const int expected = ClipByte(data_ptr_[p][x - stride_]
 + data_ptr_[p][stride_ * y - 1]
 - data_ptr_[p][-1 - stride_]);
          ASSERT_EQ(expected, data_ptr_[p][y * stride_ + x]);
 }
 }
