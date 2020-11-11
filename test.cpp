#include "Serializer.hpp"
#include <cassert>

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template<class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }

    template<class DeSerializer>
    Error deserialize(DeSerializer& deserializer){
        return deserializer(a, b, c);
    }
};

struct Data2{
    bool a;
    bool b;
    uint64_t c;

    template<class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }

    template<class DeSerializer>
    Error deserialize(DeSerializer& deserializer){
        return deserializer(a, b, c);
    }
};

int main(){
    Data x = {1, true , 2};
    Data y = {0, false, 0};
    Data2 z = {false, false, 0};
    std::stringstream ss;

    Serializer serializer(ss);
    const Error err1 = serializer.save(x);

    assert(err1 == Error::NoError);
    std::cout << "Serialization went OK" << std::endl;

    Deserializer deserializer(ss);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    std::cout << "Deserialization went OK" << std::endl;
    const Error err2 = deserializer.load(z);
    assert(err2 == Error::CorruptedArchive);
    std::cout << "Checking for CorruptedArchive went OK" << std::endl;
    std::cout << "Done" << std::endl;
    return 0;
}