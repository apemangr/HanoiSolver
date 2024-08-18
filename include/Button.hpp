#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button{
public:
    Button( int x,
            int y,
            const std::string &text,
            SDL_Color text_color,
            SDL_Color button_color,
            TTF_Font *font);
    ~Button();

    void render();
    bool handle_events(SDL_Event *e);
    void create_texture();

private:
    SDL_Rect button_rect;
    SDL_Color button_color;
    SDL_Color text_color;
    TTF_Font* font;
    SDL_Texture* texture;
    std::string text;

};

#endif // BUTTON_HPP

