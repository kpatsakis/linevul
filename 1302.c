void AffineTransform::recompose(const DecomposedType& decomp)
{
    this->setA(decomp.remainderA);
    this->setB(decomp.remainderB);
    this->setC(decomp.remainderC);
    this->setD(decomp.remainderD);
    this->setE(decomp.translateX);
    this->setF(decomp.translateY);
    this->rotateRadians(decomp.angle);
    this->scale(decomp.scaleX, decomp.scaleY);
}
