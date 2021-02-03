//! @file
//! This file deals with all the functions for drawing menubars and menus

#include "menubar.hpp"

namespace better {
    static std::array<std::vector<Uint8>, 256> letters2 {
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //9
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //10
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //11
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //12
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //13
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //14
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //15
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //16
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //17
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //18
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //19
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //20
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //21
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //22
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //23
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //24
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //25
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //26
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //27
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //28
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //29
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //30
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //31
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //Space
        {0,8,8,8,8,8,8,0,0,8,8,0,0,0,0,0}, //!
        {0,20,20,20,0,0,0,0,0,0,0,0,0,0,0,0}, //"
        {0,54,54,127,127,54,54,127,127,54,54,0,0,0,0,0}, //# make thinner
        {16,124,20,18,20,20,24,112,80,80,62,16,0,0,0,0}, //$ make go down
        {0,78,42,46,16,16,8,8,116,84,114,0,0,0,0,0}, //%
        {0,28,34,34,18,20,8,84,52,50,42,68,0,0,0,0}, //&
        {0,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0}, //'
        {32,32,16,16,8,8,8,8,8,8,8,8,16,16,32,32}, //(
        {4,4,8,8,16,16,16,16,16,16,16,16,8,8,4,4}, //)
        {0,42,20,62,20,42,0,0,0,0,0,0,0,0,0,0}, //*
        {0,0,0,0,0,8,8,62,8,8,0,0,0,0,0,0}, //+
        {0,0,0,0,0,0,0,0,0,8,8,4,0,0,0,0}, //,
        {0,0,0,0,0,0,0,62,0,0,0,0,0,0,0,0}, //-
        {0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0}, //.
        {0,64,32,32,16,16,8,8,4,4,2,0,0,0,0,0}, ///
        {0,24,36,36,66,114,78,66,36,36,24,0,0,0,0,0}, //0
        {0,16,24,20,16,16,16,16,16,16,60,0,0,0,0,0}, //1
        {0,24,36,68,66,64,32,32,16,12,126,0,0,0,0,0}, //2
        {0,14,48,32,32,28,16,32,32,48,14,0,0,0,0,0}, //3
        {0,32,48,48,40,40,36,126,32,32,32,0,0,0,0,0}, //4
        {0,62,2,2,2,14,16,32,32,16,14,0,0,0,0,0}, //5
        {0,48,8,4,4,26,34,66,34,36,24,0,0,0,0,0}, //6
        {0,62,32,32,16,16,8,8,4,4,2,0,0,0,0,0}, //7
        {0,24,36,66,36,24,36,66,66,36,24,0,0,0,0,0}, //8
        {0,24,36,66,66,68,120,64,32,32,28,0,0,0,0,0}, //9
        {0,0,0,8,8,0,0,0,8,8,0,0,0,0,0,0}, //:
        {0,0,0,8,8,0,0,0,0,8,8,4,0,0,0,0}, //;
        {0,0,96,24,6,1,1,6,24,96,0,0,0,0,0,0}, //<
        {0,0,0,0,0,0,126,0,126,0,0,0,0,0,0,0}, //=
        {0,0,1,6,24,96,96,24,6,1,0,0,0,0,0,0}, //>
        {0,12,16,32,32,16,8,8,0,8,8,0,0,0,0,0}, //?
        {0,0,24,36,90,165,165,165,57,66,36,24,0,0,0,0}, //@
        {0,0,24,24,36,36,90,66,66,66,66,0,0,0,0,0}, //A
        {0,0,14,18,18,14,18,34,34,18,14,0,0,0,0,0}, //B
        {0,0,112,12,6,2,2,2,6,12,112,0,0,0,0,0}, //C
        {0,0,14,18,34,34,34,34,34,18,14,0,0,0,0,0}, //D
        {0,0,62,2,2,2,30,2,2,2,62,0,0,0,0,0}, //E
        {0,0,62,2,2,2,62,2,2,2,2,0,0,0,0,0}, //F
        {0,0,56,4,2,2,58,34,34,36,56,0,0,0,0,0}, //G
        {0,0,34,34,34,34,62,34,34,34,34,0,0,0,0,0}, //H
        {0,0,28,8,8,8,8,8,8,8,28,0,0,0,0,0}, //I
        {0,0,62,32,32,32,32,32,34,20,8,0,0,0,0,0}, //J
        {0,0,34,18,10,6,6,10,18,18,34,0,0,0,0,0}, //K
        {0,0,2,2,2,2,2,2,2,2,62,0,0,0,0,0}, //L
        {0,0,66,66,102,102,90,66,66,66,66,0,0,0,0,0}, //M
        {0,0,34,34,38,38,42,42,50,50,34,0,0,0,0,0}, //N
        {0,0,24,36,66,66,66,66,66,36,24,0,0,0,0,0}, //O
        {0,0,30,34,34,34,34,30,2,2,2,0,0,0,0,0}, //P
        {0,0,24,36,66,66,66,66,66,36,24,112,0,0,0,0}, //Q
        {0,0,14,18,18,18,14,2,6,10,18,0,0,0,0,0}, //R
        {0,0,120,4,2,4,24,32,64,64,62,0,0,0,0,0}, //S
        {0,0,62,8,8,8,8,8,8,8,8,0,0,0,0,0}, //T
        {0,0,66,66,66,66,66,66,66,36,24,0,0,0,0,0}, //U
        {0,0,66,66,66,66,36,36,36,24,24,0,0,0,0,0}, //V
        {0,0,66,66,66,66,90,102,102,66,66,0,0,0,0,0}, //W
        {0,0,66,66,36,36,24,36,36,66,66,0,0,0,0,0}, //X
        {0,0,34,34,20,20,8,8,8,8,8,0,0,0,0,0}, //Y
        {0,0,126,64,32,32,16,8,8,4,126,0,0,0,0,0}, //Z
        {28,4,4,4,4,4,4,4,4,4,4,4,4,4,4,28}, //[
        {0,2,4,4,8,8,16,16,32,32,64,0,0,0,0,0}, //Backslash
        {56,32,32,32,32,32,32,32,32,32,32,32,32,32,32,56}, //]
        {0,8,20,34,0,0,0,0,0,0,0,0,0,0,0,0}, //^
        {0,0,0,0,0,0,0,0,0,0,127,0,0,0,0,0}, //_
        {0,6,8,0,0,0,0,0,0,0,0,0,0,0,0,0}, //`
        {0,0,0,0,0,28,34,60,34,50,44,0,0,0,0,0}, //a
        {0,2,2,2,2,30,34,34,34,34,30,0,0,0,0,0}, //b
        {0,0,0,0,0,56,4,4,4,4,56,0,0,0,0,0}, //c
        {0,32,32,32,32,60,34,34,34,50,44,0,0,0,0,0}, //d
        {0,0,0,0,0,28,34,62,2,2,60,0,0,0,0,0}, //e
        {0,48,8,4,30,4,4,4,4,4,4,0,0,0,0,0}, //f
        {0,0,0,0,0,60,18,18,18,12,2,28,34,34,28,0}, //g
        {0,2,2,2,2,26,38,34,34,34,34,0,0,0,0,0}, //h
        {0,16,16,0,0,24,16,16,16,16,56,0,0,0,0,0}, //i
        {0,16,16,0,0,30,16,16,16,16,16,16,16,16,12,0}, //j
        {0,2,2,2,2,50,10,6,10,18,34,0,0,0,0,0}, //k
        {0,14,8,8,8,8,8,8,8,8,62,0,0,0,0,0}, //l
        {0,0,0,0,0,36,90,90,90,90,90,0,0,0,0,0}, //m
        {0,0,0,0,0,26,38,34,34,34,34,0,0,0,0,0}, //n
        {0,0,0,0,0,28,34,34,34,34,28,0,0,0,0,0}, //o
        {0,0,0,0,0,30,34,34,34,34,30,2,2,2,2,0}, //p
        {0,0,0,0,0,60,34,34,34,34,60,32,32,32,32,0}, //q
        {0,0,0,0,0,26,38,2,2,2,2,0,0,0,0,0}, //r
        {0,0,0,0,0,60,2,28,32,32,30,0,0,0,0,0}, //s
        {0,0,0,4,4,62,4,4,4,4,56,0,0,0,0,0}, //t
        {0,0,0,0,0,34,34,34,34,50,44,0,0,0,0,0}, //u
        {0,0,0,0,0,34,34,20,20,20,8,0,0,0,0,0}, //v
        {0,0,0,0,0,34,34,42,42,20,20,0,0,0,0,0}, //w
        {0,0,0,0,0,66,36,24,24,36,66,0,0,0,0,0}, //x
        {0,0,0,0,0,66,66,68,36,40,16,16,8,8,6,0}, //y
        {0,0,0,0,0,62,16,8,4,2,62,0,0,0,0,0}, //z
        {24,4,4,4,4,4,4,4,2,4,4,4,4,4,4,24}, //{
        {0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0}, //|
        {24,32,32,32,32,32,32,32,64,32,32,32,32,32,32,24}, //}
        {0,0,0,0,0,0,68,76,50,34,0,0,0,0,0,0}} //~
    };
}

void better::drawMenuBar(SDL_Surface* surface, std::string menus, Uint32 colorfg, Uint32 colorbg, int windowWidth, int columnOffset, int characterHeight, int characterWidth) {
    SDL_LockSurface(surface);
    int column {};
    for(const char& letter : menus) {
        better::renderLetter(surface, better::charCheck(letter, better::letters2), column + static_cast<int>(columnOffset / characterWidth), 0, colorfg, colorbg, characterHeight, characterWidth);
        ++column;
    }
    SDL_UnlockSurface(surface);
}

void better::drawMenus(SDL_Surface* surface, std::vector<std::string> menus, Uint32 color, Uint32 colorbg, int columnOffset, int characterHeight, int characterWidth) {
    SDL_LockSurface(surface);
    if(!menus.size()) {
        return;
    }
    const int menuWidth {characterWidth * 20};
    int menuHeight {characterHeight * static_cast<int>(menus.size())};

    SDL_Rect menu {.x = columnOffset, .y = characterHeight, .w = menuWidth, .h = menuHeight};
    SDL_FillRect(surface, &menu, SDL_MapRGBA(surface->format, better::getRed(colorbg), better::getGreen(colorbg), better::getBlue(colorbg), better::getAlpha(colorbg)));

    int column {0};
    int row {1};

    for(int i{}; i < menus.size(); ++i) {
        for(const char& letter : menus[i]) {
	    better::renderLetter(surface, better::charCheck(letter, better::letters2), column + static_cast<int>(columnOffset / characterWidth), row, color, colorbg, characterHeight, characterWidth);
            ++column;
        }
        column = 0;
        ++row;
    }
    SDL_UnlockSurface(surface);
}
