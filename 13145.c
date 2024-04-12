    void doWriteHmacKey(const blink::WebCryptoKey& key)
    {
        ASSERT(key.algorithm().paramsType() == blink::WebCryptoKeyAlgorithmParamsTypeHmac);

        append(static_cast<uint8_t>(HmacKeyTag));
        ASSERT(!(key.algorithm().hmacParams()->lengthBits() % 8));
        doWriteUint32(key.algorithm().hmacParams()->lengthBits() / 8);
        doWriteAlgorithmId(key.algorithm().hmacParams()->hash().id());
    }
