#include <iostream>

template<typename T>
class ArrayHandler {
private:
    size_t _size;
    T* _array;
    size_t _cnt;
    T _max;
    T _min; 
public:
    ArrayHandler(size_t size = 100000000) {
        _size = size;
        _cnt = 0;
        _array = new T[_size];
       
    }
    void AppendElem(T elem){
        // if (_cnt == _size){
        //     T* array = new T[_size * 10000000];
        //     for (size_t i = 0; i < _size; i++){
        //         array[i] = _array[i];
        //     }
        //     delete [] _array;
        //     _array = array;
        //     _size = _size * 10000000; 
        // }
        if (_cnt != 0){
            _min = (elem < _min) ? elem : _min;
            _max = (elem > _max) ? elem : _max;
        }
        else{
            _min = elem;
            _max = elem;
        }

        _array[_cnt++] = elem;
        
    }

    bool IsContains(const T& elem)const{
        for (size_t i = 0; i < _cnt; i++){
            if (_array[i] == elem) return true;
        }
        return false;
    }

    // T GetMax(){
    //     T max = _array[0];
    //     for(size_t i = 1; i < _cnt; i++)
    //     {
    //         if (_array[i] > max) max = _array[i];
    //     }
    //     return max;
    // };

    // T GetMin(){
    //     T min = _array[0];
    //     for(size_t i = 1; i < _cnt; i++)
    //     {
    //         if (_array[i] < min) min = _array[i];
    //     }
    //     return min;
    // };

    T GetMin(){
        return _min;
    }

    T GetMax(){
        return _max;
    }


    ~ArrayHandler() {
        delete [] _array;
    }

};