#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <queue>

class JsonValue {
public:
    virtual ~JsonValue() = 0;

    virtual void print(std::ostream& out) = 0;
};

class NumberValue :public JsonValue
{
    int value;
public:
    NumberValue(int x)
    {
        this->value = x;
    }

    void print(std::ostream& out)
    {
        out << this->value;
    }


};

class StringValue : public JsonValue
{
    const char* value;
public:
    StringValue(const char* value)
    {
        this->value = value;
    }

    void print(std::ostream& out)
    {
        out << this->value;
    }
};

class ArrayValue : public JsonValue
{
    StringValue* valori_string[100];
    int count_string;
    NumberValue* valori_num[100];
    int count_num;


public:
    ArrayValue()
    {
        count_string = 0;
        count_num = 0;
    }

    void add(StringValue* string)
    {
        count_string++;
        valori_string[count_string] = string;
    }

    void add(NumberValue* number)
    {
        count_num++;
        valori_num[count_num] = number;
    }

    void print(std::ostream& out)
    {
        if (count_num != 0)
            for (int i = 1;i <= count_num;i++)
                out << valori_num[i];
        else if(count_string != 0)
            for (int i = 1;i <= count_string;i++)
                out << valori_string[i];
    }
};

class BoolValue : public JsonValue
{
    bool value;

public:
    BoolValue(bool x)
    {
        this->value = x;
    }

    void print(std::ostream& out)
    {
        out << this->value;
    }
};

class NullValue : public JsonValue
{
    int value;
public:
    NullValue()
    {
        this->value = 0;
    }

    void print(std::ostream& out)
    {
        out << "null";
    }

};

class ObjectValue
{
    int count_elem = 0;

    struct {
        const char* name;
        NumberValue* num = nullptr;
        NullValue* nul = nullptr;
        BoolValue* bol = nullptr;
        ArrayValue* array = nullptr;
        StringValue* str = nullptr;
        ObjectValue* obj = nullptr;

    }elem[100];

public:
    void add(const char* name, NumberValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].num = value;
    }

    void add(const char* name, NullValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].nul = value;
    }

    void add(const char* name, ArrayValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].array = value;
    }

    void add(const char* name, BoolValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].bol = value;
    }

    void add(const char* name, StringValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].str = value;
    }

    void add(const char* name, ObjectValue* value)
    {
        count_elem++;
        elem[count_elem].name = name;
        elem[count_elem].obj = value;
    }

    void print(std::ostream& out)
    {
        for(int i=1;i<=count_elem;i++)
            out<<elem[i].name;
    }
};


int main() {
    auto array_numbers = new ArrayValue();
    array_numbers->add(new NumberValue(5));
    array_numbers->add(new NumberValue(10));
    array_numbers->add(new NumberValue(15));

    auto array_strings = new ArrayValue();
    array_strings->add(new StringValue("abc"));
    array_strings->add(new StringValue("def"));
    array_strings->add(new StringValue("ghi"));

    auto subobject = new ObjectValue();
    subobject->add("email", new StringValue("t@gmail.com"));
    subobject->add("name", new StringValue("T"));
    subobject->add("online", new BoolValue(true));

    auto object = new ObjectValue();
    object->add("n", new NullValue());
    object->add("array_numbers", array_numbers);
    object->add("array_strings", array_strings);
    object->add("info", subobject);

    object->print(std::cout);
}
