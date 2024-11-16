#include "Set.h"


// Set::Set(size_t mp) : _bitField(10) {

// }
Set :: Set(size_t mp) :  _maxPower(mp), _bitField(BitField(mp)) {} // !!!!

// Set::Set(const Set &s) : _bitField(10){} 
Set :: Set(const Set& s) : _maxPower (s._maxPower), _bitField(BitField(s._bitField)) {}//!

// Set::Set(const BitField &bf) : _bitField(10){}
Set :: Set(const BitField& bf) : _maxPower(bf.GetLength()), _bitField(bf) {};


size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    if (!(Elem < _maxPower && Elem >= 0)) throw "elem < 0 or elem > _maxPower";
    if(IsMember(Elem)) throw "elem is already in the set";
    else _bitField.SetBit(Elem);

}
void Set::DelElem(const uint64_t Elem){
    if (!(Elem < _maxPower && Elem >= 0)) throw "elem < 0 or elem > _maxPower";
    if (!IsMember(Elem)) throw "elem is not in the set";
    else _bitField.ClrBit(Elem); 
}
bool Set::IsMember(const uint64_t Elem) const{
    return _bitField.GetBit(Elem);;
}


bool Set::operator== (const Set &s) const{
    return _bitField == s._bitField;;
}
bool Set::operator!= (const Set &s) const{
    return !(_bitField == s._bitField);
}
Set& Set::operator=(const Set &s){
    if ((*this) == s) return *this;
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){


    InsElem(Elem);
    return *this;
}
                                  
Set Set::operator- (const uint64_t Elem){
    // Set newSet(_maxPower);

    this->DelElem(Elem);

    return *this;
    
}
                                   
Set Set :: operator+(const Set& tmp)const{ // !!!
    size_t newmaxPower = _maxPower > tmp._maxPower ? _maxPower : tmp._maxPower;
    Set newSet(newmaxPower);
    newSet._bitField = _bitField | tmp._bitField;
    return newSet;
}

Set Set::operator* (const Set &s)const{
    size_t newmaxPower = _maxPower > s._maxPower ? _maxPower : s._maxPower;
    Set newSet(newmaxPower);
    newSet._bitField = _bitField & s._bitField;
    return newSet;
}

Set Set::operator~ (){
    Set newSet(_maxPower);
    newSet._bitField = ~_bitField;
    return newSet;
}

// Set Set :: Universal()const{
//     Set newSet(_maxPower);
//     for(size_t i = 0; i < _maxPower; ++i){
//         newSet._bitField.SetBit(i); 
//     }
//     return newSet;
// }

std::vector<uint64_t> Set::GetPrimary(){
    Set newSet(_maxPower);
    std::vector<uint64_t> answer;
    for(size_t i = 1; i < _maxPower; ++i){
        newSet._bitField.SetBit(i);
    }

    // std :: cout << newSet << std :: endl;
    for (size_t i = 2; i * i < _maxPower; i++){ // finds prime numbers up to _maxPower
        if (newSet.IsMember(i)){
            for (size_t j = i * 2; j < _maxPower; j+=i){
                if(newSet.IsMember(j)) newSet.DelElem(j);
            }
        }
    }
    for (size_t i = 0; i < _maxPower;i++){
        if(newSet.IsMember(i)){
            answer.push_back(i);
            // std :: cout << i << " ";
        }


    }
    // std :: cout << std :: endl << " end" << std :: endl;
    return answer;
}