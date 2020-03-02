template<typename T>
class var
{
public:
    var(){}
    var(T value) : value_{value}{};
    T value(){return value_;}
    bool isSet() {return isSet_;}
    void operator=(T value){
        isSet_=true;
        value_ = value;
    }
    void operator+=(T value){
        isSet_=true;
        value_ = value_ + value;
    }
    void operator*=(T value)
    {
        isSet_=true;
        value_ = value_ * value;
    }
    void reset()
    {
        isSet_ = false;
    }
private:
    T value_{};
    bool isSet_{false};
};