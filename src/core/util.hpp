namespace util {

    // Reverse iteration 
    template<class T>
    class reverse
    {
        T& obj;
    public:
        reverse(T &obj) : obj(obj) {}
        auto begin() {return obj.rbegin();}
        auto end() {return obj.rend();}
    };
}
