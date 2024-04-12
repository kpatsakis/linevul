    bool writeCryptoKey(const blink::WebCryptoKey& key)
    {
        append(static_cast<uint8_t>(CryptoKeyTag));

        switch (key.algorithm().paramsType()) {
        case blink::WebCryptoKeyAlgorithmParamsTypeAes:
            doWriteAesKey(key);
            break;
        case blink::WebCryptoKeyAlgorithmParamsTypeHmac:
            doWriteHmacKey(key);
            break;
        case blink::WebCryptoKeyAlgorithmParamsTypeRsaHashed:
            doWriteRsaHashedKey(key);
            break;
        case blink::WebCryptoKeyAlgorithmParamsTypeNone:
            ASSERT_NOT_REACHED();
            return false;
        }

        doWriteKeyUsages(key.usages(), key.extractable());

        blink::WebVector<uint8_t> keyData;
        if (!blink::Platform::current()->crypto()->serializeKeyForClone(key, keyData))
            return false;

        doWriteUint32(keyData.size());
        append(keyData.data(), keyData.size());
        return true;
    }
