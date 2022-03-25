#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    string line; // Временно записываю в строку

    ifstream in("in.cpp"); // Открываю файл чтения

    ofstream out;
    out.open("out.cpp"); // Открываю файл записи

    if (in.is_open())
    {
        // Флаг для проверки является ли строка комментом
        bool isComment = false;

        // Читаю построчно из файла in в стоку line
        while (getline(in, line))
        {
            // Если стоит флаг многострочного коммента
            if (isComment)
            {
                // Если в конце строки стоит */ , то убираю флаг многострочного коммента
                if (line[line.length() - 1] == '/' && line[line.length() - 2] == '*')
                {
                    isComment = false;
                }
            }
            else
            {
                // Ищу / в строке
                std::string::iterator findSlash = find(line.begin(), line.end(), '/');
                if (findSlash != line.end())
                {
                    // Ищу где начинается /
                    string newLine = line.substr(0, findSlash - line.begin());

                    // Если начинается с /* , то это многострочный коммент
                    if (*(findSlash + 1) == '*')
                    {
                        if (newLine != "")
                        {
                            out << newLine << endl;
                        }
                        if (line[line.length() - 1] == '/' && line[line.length() - 2] == '*')
                        {
                            isComment = false;
                        }
                        else
                        {
                            isComment = true;
                        }
                    }
                    // Если начинается с // , то это однострочный коммент, иначе - не коммент
                    else if (*(findSlash + 1) == '/')
                    {
                        if (newLine != "")
                        {
                            out << newLine << endl;
                        }
                    }
                    else
                    {
                        out << line << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }
        }
    }

    in.close();

    return 0;
}