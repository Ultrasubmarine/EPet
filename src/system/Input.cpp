//
//  Input.cpp
//  EPet
//
//  Created by marina porkhunova on 12.01.2024.
//

#include "Input.hpp"

//#if defined(__GNUG__) || defined(__GNUC__)
//#define OS_LINUX
//#elif defined(_MAC)
//#define OS_MAC
//#elif defined(_WIN32)
//#define OS_WIN
//#endif
//
//
//#ifdef OS_WIN
//#include <conio.h>
//#elif defined(OS_LINUX) || defined(OS_MAC)
//#include <unistd.h>
//#include <sys/socket.h>
//#endif

//bool StdinHasData()
//{
//#   if defined(OS_WIN)
//    // this works by harnessing Windows' black magic:
//    return _kbhit();
//#   elif defined(OS_LINUX) || defined(OS_MAC)
//    // using a timeout of 0 so we aren't waiting:
//    struct timespec timeout{ 0l, 0l };
//
//    // create a file descriptor set
//    fd_set fds{};
//
//    // initialize the fd_set to 0
//    FD_ZERO(&fds);
//    // set the fd_set to target file descriptor 0 (STDIN)
//    FD_SET(0, &fds);
//
//    // pselect the number of file descriptors that are ready, since
//    //  we're only passing in 1 file descriptor, it will return either
//    //  a 0 if STDIN isn't ready, or a 1 if it is.
//    return pselect(0 + 1, &fds, nullptr, nullptr, &timeout, nullptr) == 1;
//#   else
//    // throw a compiler error
//    static_assert(false, "Failed to detect a supported operating system!");
//#   endif
//}


#include <SDL2/SDL.h>
#include <iostream>

#define LEFT_KEY SDLK_a
#define MIDDLE_KEY SDLK_s
#define RIGHT_KEY SDLK_d

#include <map>
void PrintKeyInfo( SDL_KeyboardEvent *key );

struct Key
{
    enum State
    {
        pressed,
        released
    };
    
    State state;
    const uint unicode;
    const char *name;
    
};

//scancode - key name 
std::map<std::string, Key> inputTable;


bool Input()
{
    static SDL_Event event;
    if(SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym == 'a')
                    PrintKeyInfo( &event.key);
                break;
            }
        }
    }
    return true;
}


/* Print all information about a key event */
    void PrintKeyInfo( SDL_KeyboardEvent *key ){
        /* Is it a release or a press? */
        if( key->type == SDL_KEYUP )
            printf( "Release:- " );
        else
            printf( "Press:- " );

        /* Print the hardware scancode first */
        printf( "Scancode: 0x%02X", key->keysym.scancode );
        /* Print the name of the key */
        printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
        /* We want to print the unicode info, but we need to make */
        /* sure its a press event first (remember, release events */
        /* don't have unicode info                                */
        if( key->type == SDL_KEYDOWN ){
            /* If the Unicode value is less than 0x80 then the    */
            /* unicode value can be used to get a printable       */
            /* representation of the key, using (char)unicode.    */
            printf(", Unicode: " );
            if( key->keysym.scancode < 0x80 && key->keysym.scancode > 0 ){
                printf( "%c (0x%04X)", (char)key->keysym.scancode,
                        key->keysym.scancode );
            }
            else{
                printf( "? (0x%04X)", key->keysym.scancode);
            }
        }
        printf( "\n" );
        /* Print modifier info */
      //  PrintModifiers( key->keysym.mod );
    }
