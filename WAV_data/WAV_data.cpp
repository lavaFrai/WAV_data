#define FOR(x, from, to) for (int (x) = (from); (x) < (to); (x)++)
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void get_DWORD(ifstream & file, uint8_t * buffer)
{
    buffer[0] = file.get();
    buffer[1] = file.get();
    buffer[2] = file.get();
    buffer[3] = file.get();
}

void get_WORD(ifstream& file, uint8_t* buffer)
{
    buffer[0] = file.get();
    buffer[1] = file.get();
}

void print_DWORD(uint8_t * buffer)
{
    FOR_i(0, 4) cout << buffer[i];
}

bool compare_DWORD(uint8_t* buffer, const char * buffer2)
{
    FOR_i(0, 4)
    {
        if (buffer[i] != buffer2[i]) return 0;
    }
    return 1;
}

bool compare_DWORD(uint8_t* buffer, uint8_t * buffer2)
{
    FOR_i(0, 4)
    {
        if (buffer[i] != buffer2[i]) return 0;
    }
    return 1;
}

uint32_t DWORD_to_INT(uint8_t * buffer)
{
    uint32_t res = 0;
    res |= buffer[0];
    res |= buffer[1] << 8;
    res |= buffer[2] << 16;
    res |= buffer[3] << 24;
    return res;
}

int main(int argc, char* argv[])
{
    if (&argc == NULL) return 0;
    // cout << argv[1];
    // cout << "\n\n";
    ifstream fin(argv[1]);
    uint8_t buf[4];
    get_DWORD(fin, buf);
    cout << "Encode type:\t";
    print_DWORD(buf);
    cout << ' ';

    if (!compare_DWORD(buf, "RIFF"))
    {
        cout << "Not supportable type, terminating\n";
        system("pause");
        return 0;
    }
    get_DWORD(fin, buf);
    get_DWORD(fin, buf);
    print_DWORD(buf);
    cout << ' ';

    if (!compare_DWORD(buf, "WAVE"))
    {
        cout << "Not supportable type, terminating\n";
        system("pause");
        return 0;
    }
    get_DWORD(fin, buf);
    print_DWORD(buf);
    cout << ' ';

    if (!compare_DWORD(buf, "fmt "))
    {
        cout << "Not supportable type, terminating\n";
        system("pause");
        return 0;
    }
    cout << '\n';


    get_DWORD(fin, buf);
    get_WORD(fin, buf);
    cout << "Audio format:\t";
    if (buf[0] == 1)
    {
        cout << "linear quantization\n";
    }
    else
    {
        cout << "Not supportable type, terminating\n";
        system("pause");
        return 0;
    }

    get_WORD(fin, buf);
    cout << "Channels:\t";
    cout << (buf[0] | buf[1] << 8) << '\n';

    get_DWORD(fin, buf);
    cout << "Sample rate:\t";
    cout << DWORD_to_INT(buf) << '\n';

    get_DWORD(fin, buf);
    cout << "Byte/second:\t";
    cout << DWORD_to_INT(buf) << '\n';

    get_WORD(fin, buf);
    get_WORD(fin, buf);
    cout << "Sound depth:\t";
    cout << (buf[0] | buf[1] << 8) << "bit" << '\n';




    system("pause");
}
