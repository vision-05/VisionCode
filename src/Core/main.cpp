#define SDL_MAIN_HANDLED

#include <SDL2-2.0.12/include/SDL.h>
#include <immer/flex_vector.hpp>
#include <vector>

#include "datatypes.hpp"
#include "fileUtils.hpp"
#include "renderchars.hpp"

namespace better {

better::Text verticalNav(better::Text text, SDL_Keycode key);
better::Text horizontalNav(better::Text text, SDL_Keycode key);
better::Text scroll(better::Text text, SDL_Event event);

}

int main(int argc, char* argv[]) {
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    std::vector<better::Text> texts {};

    SDL_Window* window = SDL_CreateWindow("Better Code",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1200,792,0);
    

    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_PixelFormat* format;
    format = surface->format;

    
    char filename[] = "main.cpp";
    better::Text firstText {better::readFile(filename), {0,0}, 0, 0};
    texts.push_back(firstText);

    better::renderText(surface, texts.back().textEdit, texts.back().topLineNumber, texts.back().topColumnNumber);
    better::renderCursor(surface, texts.back().cursor.column, texts.back().cursor.row, texts.back().topLineNumber, texts.back().topColumnNumber);
    SDL_UpdateWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x22, 0x22, 0x22));

    bool isScroll {false};

    SDL_Event event;
    while(1) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }

            else if(event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_DOWN || event.key.keysym.scancode == SDL_SCANCODE_UP)) {
                texts[texts.size() - 1] = better::verticalNav(texts.back(), event.key.keysym.scancode);
            }

            else if(event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_RIGHT || event.key.keysym.scancode == SDL_SCANCODE_LEFT)) {
                texts[texts.size() - 1] = better::horizontalNav(texts.back(), event.key.keysym.scancode);
            }

            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                texts.push_back(better::newLine(texts.back()));
            }

            else if(event.type == SDL_MOUSEWHEEL) { //set bool scroll to true
                texts[texts.size() - 1] = better::scroll(texts.back(), event);
                isScroll = true;
            }

            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                better::Cursor tempCursor {better::findCursorPos(texts.back().topLineNumber, texts.back().topColumnNumber, event)};
                if(tempCursor.column > texts.back().textEdit[tempCursor.row].size()) {
                    tempCursor.column = texts.back().textEdit[tempCursor.row].size();
                }
                texts[texts.size() - 1].cursor = tempCursor;
                isScroll = false;
            }

            else if(event.type == SDL_KEYDOWN) {
                if(isScroll) {
                    texts[texts.size() - 1].topLineNumber = texts.back().cursor.row;
                    texts[texts.size() - 1].topColumnNumber = 0;
                }
                switch(event.key.keysym.sym) {
                    case '\b':
                        texts.push_back(better::backspace(texts.back()));
                        break;
                    default:
                        texts.push_back(better::updateText(texts.back(),event.key.keysym.sym)); //save the text at its current state (find out why newline weird behaviour/still printing newline)
                }

            }
            better::renderText(surface, texts.back().textEdit, texts.back().topLineNumber, texts.back().topColumnNumber);
            //dont render cursor if scroll is true
            if(!isScroll) {
                better::renderCursor(surface, texts.back().cursor.column, texts.back().cursor.row, texts.back().topLineNumber, texts.back().topColumnNumber);
            }
            SDL_UpdateWindowSurface(window);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x22, 0x22, 0x22));
        }
    }
    
}

better::Text better::scroll(better::Text text, SDL_Event event) { //make sure not to move cursor
    int row {text.topLineNumber + 66};
    int column {text.topColumnNumber + 150};

    if(event.wheel.y > 0) {
        for(int times{}; times < event.wheel.y; ++times) {
            if(text.topLineNumber) {
                row -= 1;
                text.topLineNumber -= 1;
            }
        }
    }
    else {
        for(int times{}; times > event.wheel.y; --times) {
            if((row == text.topLineNumber + 66) && (row < text.textEdit.size())) {
                row += 1;
                text.topLineNumber += 1;
            }
        }
    }

    if(event.wheel.x > 0) {
        for(int times{}; times < event.wheel.x; ++times) {
            if((column == text.topColumnNumber + 150) && (column < text.textEdit[row].size())) {
                column += 1;
                text.topColumnNumber += 1;
            }
        }
    }
    else {
        for(int times{}; times > event.wheel.x; --times) {
            if(text.topColumnNumber) {
                column -= 1;
                text.topColumnNumber -= 1;
            }
        }
    }

    return text;
}

better::Text better::verticalNav(better::Text text, SDL_Keycode key) {
    switch(key) {
        case SDL_SCANCODE_DOWN:
            if(text.cursor.row < text.textEdit.size()) {
                if(text.topLineNumber == text.textEdit.size() - 66) {
                    return text;
                }
                if(text.textEdit[text.cursor.row + 1].size() < text.cursor.column) { //check the next row has less elements than current column of cursor position
                    text.cursor.column = text.textEdit[text.cursor.row + 1].size();
                    text.cursor.row += 1;
                }
                else {
                    text.cursor.row += 1;
                }
                if(text.cursor.row == text.topLineNumber + 66) {
                    text.topLineNumber += 1; //scroll down
                }
            }
            break;

        case SDL_SCANCODE_UP:
            if(text.cursor.row) {
                if(text.textEdit[text.cursor.row - 1].size() < text.cursor.column) { //check the next row has less elements than current column of cursor position
                    text.cursor.column = text.textEdit[text.cursor.row - 1].size();
                    text.cursor.row -= 1;
                }
                else {
                    text.cursor.row -= 1;
                }
                if(text.cursor.row == text.topLineNumber) {
                    text.topLineNumber -= 1;
                }
            }
            break;
    }

    //TODO: recalculate the cursor pixelIndex here
    return text;
}

better::Text better::horizontalNav(better::Text text, SDL_Keycode key) {
    switch(key) {
        case SDL_SCANCODE_RIGHT:
            if((text.cursor.row != text.textEdit.size() - 1) || (text.cursor.row == text.textEdit.size() - 1 && text.cursor.column < text.textEdit[text.cursor.row].size())) {
                if(text.cursor.column == text.textEdit[text.cursor.row].size()) {
                    text.cursor.column = 0;
                    text.cursor.row += 1;
                    text.topColumnNumber = 0;
                }
                else {
                    text.cursor.column += 1;
                }
                if(text.cursor.column == text.topColumnNumber + 150) {
                    text.topColumnNumber += 1;
                }
            }
            break;

        case SDL_SCANCODE_LEFT:
            if((text.cursor.row) || (!text.cursor.row && text.cursor.column)) {
                if(!text.cursor.column) {
                    text.cursor.row -= 1;
                    text.cursor.column = text.textEdit[text.cursor.row].size();
                }
                else {
                    text.cursor.column -= 1;
                }
                if((text.cursor.column == text.topColumnNumber) && (text.cursor.column)) {
                    text.topColumnNumber -= 1;
                }
            }
            break;
    }
    return text;
}