class CPUType {
    public:
       typedef enum {Unknown, Intel, AMD} Type;
       CPUType();
       Type type;
       Type & operator=(Type t) { type = t; return type; }
};
