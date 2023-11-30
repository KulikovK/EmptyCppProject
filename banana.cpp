#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
void Blat(void* ptr_)
{
    std::cout << *(int*)(ptr_) << std::endl;
}

struct info_t
{
    size_t m_len;
    char *buffer;

    info_t(const char* _msg)
    {
        auto len = strlen(_msg) + 1;
        assert(len != 0 || "Jopa");
        m_len = len;
        buffer = new char[m_len];
        strcpy(buffer, _msg);
    }

    void dump(std::ostream& stream = std::cout) {
        if (!buffer) 
            std::cout << "Buffer is null!\n"; 
            //return;
        stream << this->buffer << "\n";
        
    }
};

typedef info_t INFO;

int main()
{
    INFO i("AAAAAA, ebat!");
    std::cout << "AAAAAAAAAA EBAT!\n";
    std::cout << i.buffer << std::endl;
    return 0;
}
