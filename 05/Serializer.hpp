#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

enum class Error {
    NoError, CorruptedArchive, Unserializable
};

template<typename T, typename Y>
struct IsSame {
    static constexpr bool value = false;
};

template <typename T>
struct IsSame<T, T> {
    static constexpr bool value = true;
};

template<typename T>
struct Serializable;

template<typename T>
struct DeSerializable;

class Serializer{
    static constexpr char Separator = ' ';
    std::ostream& out_;
public:
    explicit Serializer(std::ostream& out) : out_(out) {}
    template<class T>
    Error save(T& object){
        if(Serializable<T>::value)
            return object.serialize(*this);
        else
            return Error::Unserializable;
    }

    template<typename... ArgsT>
    Error operator()(ArgsT&... args){
        return process(args...);
    }
private:
    template<typename T>
    Error help(T& obj) {
        if(IsSame<T, bool>::value) {
            if(obj)
                out_ << "true" << Separator;
            else
                out_ << "false" << Separator;
            return Error::NoError;
        }
        else if(IsSame<T, uint64_t>::value) {
            out_ << obj << Separator;
            return Error::NoError;
        }
        else
            return Error::CorruptedArchive;
    }

    template<typename... ArgsT>
    Error process();

    template<typename T, typename... ArgsT>
    Error process(T& ob, ArgsT&... args){
        Error err = help(ob);
        if(err == Error::NoError)
            return process(args...);
        else
            return Error::CorruptedArchive;
    }

    Error process(){
        return Error::NoError;
    }

};

class Deserializer{
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in) : in_(in) {}

    template<class T>
    Error load(T& object){
        if(DeSerializable<T>::value)
            return object.deserialize(*this);
        else
            return Error::Unserializable;
    }

    template<typename... ArgsT>
    Error operator()(ArgsT&... args){
        return process(args...);
    }

private:

    template<typename... ArgsT>
    Error process();

    template<typename T, typename... ArgsT>
    Error process(T& ob, ArgsT&... args){
        Error err = help(ob);
        if(err == Error::NoError)
            return process(args...);
        else
            return Error::CorruptedArchive;
    }

    Error process() {
        return Error::NoError;
    }

    template<typename T>
    Error help(T& obj) {
        if(IsSame<T, bool>::value){
            std::string val;
            in_ >> val;
            if(val == "true")
                obj = true;
            else if (val == "false")
                obj = false;
            else
                return Error::CorruptedArchive;

            return Error::NoError;
        }
        else if(IsSame<T, uint64_t>::value) {
            std::string val;
            in_ >> val;
            try {
                size_t amount;
                obj = std::stoull(val, &amount);
                if(amount != val.size())
                    return Error::CorruptedArchive;
            }
            catch(const std::logic_error& e) {
                std::cout << e.what() << std::endl;
                return Error::CorruptedArchive;
            }
            return Error::NoError;
        }
        else {
            return Error::CorruptedArchive;
        }
    }
};

template<typename T>
struct Serializable {
private:
    static int check(...);

    template<typename U>
    static auto check(U *u) -> decltype(u->serialize(*((Serializer*) nullptr)));
public:
    static constexpr bool value = IsSame<Error, decltype(Serializable<T>::check((T*) nullptr))>::value; // true или false;
};

template<typename T>
struct DeSerializable {
private:
    static int check(...);

    template<typename U>
    static auto check(U *u) -> decltype(u->deserialize(*((Deserializer*) nullptr)));
public:
    static constexpr bool value = IsSame<Error, decltype(DeSerializable<T>::check((T*) nullptr))>::value; // true или false;
};
