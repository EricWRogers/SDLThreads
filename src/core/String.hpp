#pragma once
#include <stdio.h>
#include <string.h>

#include "Types.hpp"
#include "vec.h"

#define MAXSTINGSIZE (2000)

class String
{
public:
    String()
    {
        vec_init(&data, 1, char);
        data[0] = '\0';
    }

    String(const char* s)
    {
        vec_init(&data, strlen(s) + 1, char);
        strcpy(data, s);
    }

    ~String()
    {
        vec_free(&data);
    }

    u32 Count()
    {
        return vec_count(&size) - 1;
    }

    const char* CString()
    {
        return data;
    }

    operator const char*() const { return data; }
    operator bool() const { return data[0] == '\0'; }

    String& operator=(const char* cString)
    {
        if (this->data == cString) return *this;

        for (int i = 0; i < MAXSTINGSIZE; i++)
        {
            if (cString[i] == '\0')
            {
                if (i + 1 > vec_count(&data))
                    vec_resize(&data, i + 1, char);

                memcpy(data, cString, i);
                break;
            }
        }
        
        return *this;
    }

    String& operator=(String& _string)
    {
        if (this->data == _string.data) return *this;
        
        return _string;
    }

    String& operator+(const char* cString)
    {
        if (this->data == cString) return *this;

        for (int s = 0; s < MAXSTINGSIZE; s++)
        {
            if (this->data[s] == '\0')
            {
                for (int i = 0; i < MAXSTINGSIZE; i++)
                {
                    if (cString[i] == '\0')
                    {
                        memcpy(&(this->data[s]), cString, i);
                        break;
                    }
                }
                break;
            }
        }
        
        return *this;
    }

    String& operator+=(const char* cString)
    {
        if (this->data == cString) return *this;

        for (int s = 0; s < MAXSTINGSIZE; s++)
        {
            if (this->data[s] == '\0')
            {
                for (int i = 0; i < MAXSTINGSIZE; i++)
                {
                    if (cString[i] == '\0')
                    {
                        memcpy(&(this->data[s]), cString, i);
                        break;
                    }
                }
                break;
            }
        }
        
        return *this;
    }

    String& operator+(const u32 _number)
    {
        char str[100];
        sprintf(str, "%d", _number);
        *this += (const char *)&str;
        return *this;
    }

    String& operator+=(const u32 _number)
    {
        char str[100];
        sprintf(str, "%d", _number);
        *this += (const char *)&str;
        return *this;
    }

    String operator+(size_t n) const
    {
        if (n >= MAXSTINGSIZE) {
            return String("");
        }
        return String(*this + n);
    }

private:
    char* data;
};

inline String ToString(u32 _number)
{
    char str[100];
    sprintf(str, "%d", _number);
    return String((const char*)&str);
}
