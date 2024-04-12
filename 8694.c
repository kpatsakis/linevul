    void doWriteAlgorithmId(blink::WebCryptoAlgorithmId id)
    {
        switch (id) {
        case blink::WebCryptoAlgorithmIdAesCbc:
            return doWriteUint32(AesCbcTag);
        case blink::WebCryptoAlgorithmIdHmac:
            return doWriteUint32(HmacTag);
        case blink::WebCryptoAlgorithmIdRsaSsaPkcs1v1_5:
            return doWriteUint32(RsaSsaPkcs1v1_5Tag);
        case blink::WebCryptoAlgorithmIdSha1:
            return doWriteUint32(Sha1Tag);
        case blink::WebCryptoAlgorithmIdSha256:
            return doWriteUint32(Sha256Tag);
        case blink::WebCryptoAlgorithmIdSha384:
            return doWriteUint32(Sha384Tag);
        case blink::WebCryptoAlgorithmIdSha512:
            return doWriteUint32(Sha512Tag);
        case blink::WebCryptoAlgorithmIdAesGcm:
            return doWriteUint32(AesGcmTag);
        case blink::WebCryptoAlgorithmIdRsaOaep:
            return doWriteUint32(RsaOaepTag);
        case blink::WebCryptoAlgorithmIdAesCtr:
            return doWriteUint32(AesCtrTag);
        case blink::WebCryptoAlgorithmIdAesKw:
            return doWriteUint32(AesKwTag);
        }
        ASSERT_NOT_REACHED();
    }
