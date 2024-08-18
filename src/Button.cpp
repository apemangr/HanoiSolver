#include "../include/Button.hpp"
#include "../include/Screen.hpp"
#include <iostream>

Button::Button( int x,
                int y,
                const std::string &text,
                SDL_Color text_color,
                SDL_Color button_color,
                TTF_Font *font)
    : text_color(text_color),
      button_color(button_color), 
      font(font), 
      text(text),
      texture(nullptr) 
{
    button_rect.x = x;
    button_rect.y = y;
    create_texture();
}

Button::~Button() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Button::render() {

     SDL_SetRenderDrawColor(Screen::renderer, button_color.r, button_color.g, button_color.b, button_color.a);
     SDL_RenderFillRect(Screen::renderer, &button_rect);
    
     // Draw contour
     SDL_SetRenderDrawColor(Screen::renderer, 255, 255, 255, 255);
     SDL_RenderDrawRect(Screen::renderer, &button_rect);


    if (texture != nullptr) {
        // Centrando el texto dentro del botón
        SDL_Rect textRect = {   
            button_rect.x + (button_rect.w - button_rect.w) / 2 + 10,
            button_rect.y + (button_rect.h - button_rect.h) / 2 + 10, 
            button_rect.w - 25, 
            button_rect.h - 25 
        };
        SDL_RenderCopy(Screen::renderer, texture, nullptr, &textRect);
    }

}

bool Button::handle_events(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > button_rect.x && x < button_rect.x + button_rect.w &&
            y > button_rect.y && y < button_rect.y + button_rect.h) {
            if (e->type == SDL_MOUSEBUTTONUP) {
                return true;
            }
        }
    }
    return false;
}
void Button::create_texture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), text_color);
    if (textSurface == nullptr) {
        SDL_Log("Unable to create text surface! TTF Error: %s", TTF_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(Screen::renderer, textSurface);
    if (texture == nullptr) {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
    } else {
        button_rect.w = textSurface->w; // Agrega relleno
        button_rect.h = textSurface->h; // Agrega relleno
    }

    SDL_FreeSurface(textSurface);
}

