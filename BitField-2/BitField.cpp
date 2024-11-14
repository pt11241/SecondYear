#include "BitField.h"


size_t BitField::GetMemIndex(size_t n) const{
    if (n < _sizeBit && n >= 0) return n / (sizeof(uint16_t) * 8);
    throw "n is out of range";
    return 0;
}
uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % (sizeof(uint16_t) * 8));
}

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = (_sizeBit / (sizeof(uint16_t) * 8)) + (_sizeBit % (sizeof(uint16_t) * 8) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; i++){
        _mem[i] = 0;
    }
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; i++){
        _mem[i] = tmp._mem[i];
    }

}

BitField& BitField::operator=(const BitField& tmp) {
    if (this == &tmp) throw "object = object ?";
    if (_sizeBit != tmp._sizeBit){
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        delete [] _mem;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < tmp._memSize; i++){
        _mem[i] = tmp._mem[i];
    }
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    if (n < _sizeBit && n >= 0) _mem[GetMemIndex(n)] |= GetMask(n);
    throw "o";
}
void BitField::ClrBit(size_t n) {
    if (n < _sizeBit && n >= 0) _mem[GetMemIndex(n)] = _mem[GetMemIndex(n)] & (~GetMask(n)); 
    throw "o";
}
uint8_t BitField::GetBit(size_t n) const {
    if (n < _sizeBit && n >= 0) {
        uint8_t bf = _mem[GetMemIndex(n)] & GetMask(n);
        if (static_cast<int>(bf) == 0) return 0;
        return 1;
    }
    else throw "GetBit() n is out of range";
 
    return 0;
}

BitField BitField :: operator|(const BitField& tmp){
    size_t maxSize = _sizeBit > tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    BitField newBF(maxSize); 
    // newBF.TBitFieldPrint();
    for (size_t i = 0; i < _sizeBit; i++){
        newBF._mem[i] |= _mem[i]; 
    }
    // std :: cout << std :: endl;
    // newBF.TBitFieldPrint();
    for (size_t i = 0; i < _sizeBit; i++){
        newBF._mem[i] |= tmp._mem[i];
    }
    // std :: cout << std :: endl;
    // newBF.TBitFieldPrint();

    return newBF;
}
BitField BitField :: operator&(const BitField& tmp){
    size_t maxSize = _sizeBit > tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    BitField newBF(maxSize);
    for (size_t i = 0; i < maxSize; i++){
        newBF._mem[i] = (_mem[i] & tmp._mem[i]);
    }
    return newBF;
};

// BitField BitField::operator&(const BitField& tmp) {
//     return *this;
// }
BitField BitField::operator^(const BitField& tmp) {
    return *this;
}
bool BitField::operator==(const BitField& tmp) const{
    return true;
}
BitField BitField::operator~(){
    return *this;
}


void BitField :: BitFieldPrint(){
    for (size_t i = 0; i < _sizeBit; i++){
        std :: cout << static_cast<int>((*this).GetBit(i));
    }
}