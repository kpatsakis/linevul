    void doWriteNumber(double number)
    {
        append(reinterpret_cast<uint8_t*>(&number), sizeof(number));
    }
