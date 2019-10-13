#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "params.hpp"
#include "bios.hpp"
#include "window.hpp"
#include <emulator.hpp>

typedef union SDL_Event SDL_Event;

class Application
{
private:
    Window     window;
    BiosReader bios;
    Emulator   emu;

    bool running;

    bool init(Params& params);
    void free();
    bool frame();
    void handle_event(SDL_Event& event);

    void key_event(int32_t keycode, bool down);

    enum class RomType { NONE, ELF, ISO, CSO };
    bool open_rom(const char* path);

public:
    Application();
    ~Application() = default;

    int run(Params& params);
};

#endif//__APPLICATION_HPP__
