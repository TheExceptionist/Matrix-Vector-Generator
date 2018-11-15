#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 
#include <stdlib.h>  

#define TRUE 1
#define FALSE 0

#define ACCEPT 0
#define STORE 1
#define ACCEPT_INT 2

#define DEBUG

namespace e_std
{
    typedef uint8_t e_byte;
    typedef uint16_t e_halfword;
    typedef uint32_t e_word;
    typedef uint64_t e_doubleword;

    typedef int8_t e_int8;
    typedef int16_t e_int16;
    typedef int32_t e_int32;
    typedef int64_t e_int64;

    typedef const char* e_str;
    typedef e_byte e_bool;

	bool accept(const std::string& question, const std::string& match)
	{
		std::string input;
		printf("%s\n", question.c_str());

		std::cin >> input;

		if (match.compare(input) == 0) return true;
		else return false;
	}

	void store(const std::string& question, std::string* storeTo)
	{
		std::string input;
		printf("%s\n", question.c_str());

		std::cin >> input;
		*storeTo = input;
	}

    int acceptInt(const std::string& question)
	{
		std::string input;
		printf("%s\n", question.c_str());

        std::string::size_type size;

		std::cin >> input;

        int answer = 0;

        try
        {
            answer = (std::stoi(input, &size));
        }
        catch(const std::invalid_argument& ia)
        {
            fprintf(stderr, "Invalid argument: %s!\n", input.c_str());
        }

		return answer;
	}

    int loopAccept(const std::string& question, const std::string& match, std::string* storeTo, const int type)
    {
        bool invalid = true;
        int answer = 0;

        do
        {
            switch(type)
            {
                case ACCEPT:
                {
                    invalid = accept(question, match);

                    if(invalid)
                    {
                        printf("Invalid Answer!\n");
                    }
                }
                break;
                case STORE:
                {
                    store(question, storeTo);
                    invalid = false;
                }
                break;
                case ACCEPT_INT:
                {
                    answer = acceptInt(question);
                    invalid = false;
                }
                break;
                default:
                {
                    printf("Invalid Accept Type!\n");
                }
            }
        }
        while(invalid);

        return answer;
    }

    void println(const std::string& str)
    {
        printf("%s\n", str.c_str());
    }

    int randInt(int min, int max)
    {
        return ((rand() % (max - min)) + min);
    }
}
#endif
