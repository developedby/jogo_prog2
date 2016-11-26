#ifndef PROMPT
#define PROMPT

#include <pentagon_commander.hpp>

#define MAX_LOG_LINES 500

bool key[ALLEGRO_KEY_MAX];
const float prompt_width = 500.0; //Numero qualquer, trocar depois
const float prompt_height = 100.0;
const float log_width = 500.0;
const float log_height = SCREEN_H - prompt_height;


using namespace std;

class Prompt
{
private:
    static Prompt *object;
    string log[MAX_LOG_LINES];
    string current_line;
    string feedback_line;
    int pressed_character;
    ALLEGRO_BITMAP *screen;
    GraphicElement prompt_box;
    float width;
    float height;
    float x;
    float y;
    GraphicElement log_box;
    float log_width;
    float log_height;
    float log_x;
    float log_y;
    int log_pos;
    bool show_log;
    int n_log_lines;
    Prompt();
public:
    virtual ~Prompt();
    void printPrompt(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);
    void setShowLog();
    bool getShowLog();
    static Prompt* getPrompt();
    void setPressedCharacter(ALLEGRO_EVENT *event);
    void processPressedCharacter();
};

void Prompt::printPrompt(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font)
{
    prompt_box.printOnScreen();
    al_set_target_bitmap(screen);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_text(font, al_map_rgb(255,255,255), 10, SCREEN_H - font_size - 2, ALLEGRO_ALIGN_LEFT, current_line.c_str());
    al_draw_text(font, al_map_rgb(255,255,255), 10, SCREEN_H - 3*(font_size - 2), ALLEGRO_ALIGN_LEFT, feedback_line.c_str());
    al_draw_text(font, al_map_rgb(255,255,255), 10, SCREEN_H - 4*(font_size - 2), ALLEGRO_ALIGN_LEFT, log[0].c_str());
    if(show_log)
    {
        log_box.printOnScreen();
        al_set_target_bitmap(screen);
        for(int i=log_pos; i<n_log_lines; i++)
        {
            al_draw_text(font, al_map_rgb(255,255,255), 10, SCREEN_H - (6+i)*(font_size - 2), ALLEGRO_ALIGN_LEFT, current_line.c_str());
        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(screen, 0, 0, 0);
}

Prompt* Prompt::object = nullptr;

Prompt::~Prompt()
{
    delete object;
}

Prompt* Prompt::getPrompt()
{
    if(object == nullptr)
    {
        object = new Prompt();
    }
    return object;
}

Prompt::Prompt()
{
    int i;
    n_log_lines = 0;
    log_pos = 0;
    show_log = false;
    for(i=0; i<MAX_LOG_LINES; i++)
    {
        log[i].clear();
    }
    current_line.clear();
    feedback_line.clear();
    x = 0;
    log_x = 0;
    y = SCREEN_H - height;
    log_y = y - log_y;
    pressed_character = -1;
    screen = al_create_bitmap(log_width, log_height + prompt_height);
    prompt_box.loadSprite("prompt_box.png", 1, prompt_width, prompt_height);
    log_box.loadSprite("log_box.png", 1, log_width, log_height);
    prompt_box.setDrawingTarget(screen);
    log_box.setDrawingTarget(screen);
    //Add bitmap creation;
}

void Prompt::setPressedCharacter(ALLEGRO_EVENT *event)
{
    if(event->type == ALLEGRO_KEY_UP)
        pressed_character = event->keyboard.keycode;
    else
        pressed_character = -1;
}

void Prompt::processPressedCharacter()
{
    if(pressed_character!=-1)
    {
        switch(pressed_character)
        {
            case ALLEGRO_KEY_A:
                current_line.append("a");
                break;
            case ALLEGRO_KEY_B:
                current_line.append("b");
                break;
            case ALLEGRO_KEY_C:
                current_line.append("c");
                break;
            case ALLEGRO_KEY_D:
                current_line.append("d");
                break;
            case ALLEGRO_KEY_E:
                current_line.append("e");
                break;
            case ALLEGRO_KEY_F:
                current_line.append("f");
                break;
            case ALLEGRO_KEY_G:
                current_line.append("g");
                break;
            case ALLEGRO_KEY_H:
                current_line.append("h");
                break;
            case ALLEGRO_KEY_I:
                current_line.append("i");
                break;
            case ALLEGRO_KEY_J:
                current_line.append("j");
                break;
            case ALLEGRO_KEY_K:
                current_line.append("k");
                break;
            case ALLEGRO_KEY_L:
                current_line.append("l");
                break;
            case ALLEGRO_KEY_M:
                current_line.append("m");
                break;
            case ALLEGRO_KEY_N:
                current_line.append("n");
                break;
            case ALLEGRO_KEY_O:
                current_line.append("o");
                break;
            case ALLEGRO_KEY_P:
                current_line.append("p");
                break;
            case ALLEGRO_KEY_Q:
                current_line.append("q");
                break;
            case ALLEGRO_KEY_R:
                current_line.append("r");
                break;
            case ALLEGRO_KEY_S:
                current_line.append("s");
                break;
            case ALLEGRO_KEY_T:
                current_line.append("t");
                break;
            case ALLEGRO_KEY_U:
                current_line.append("u");
                break;
            case ALLEGRO_KEY_V:
                current_line.append("v");
                break;
            case ALLEGRO_KEY_W:
                current_line.append("w");
                break;
            case ALLEGRO_KEY_X:
                current_line.append("x");
                break;
            case ALLEGRO_KEY_Y:
                current_line.append("y");
                break;
            case ALLEGRO_KEY_Z:
                current_line.append("z");
                break;
            case ALLEGRO_KEY_0:
                current_line.append("0");
                break;
            case ALLEGRO_KEY_1:
                current_line.append("1");
                break;
            case ALLEGRO_KEY_2:
                current_line.append("2");
                break;
            case ALLEGRO_KEY_3:
                current_line.append("3");
                break;
            case ALLEGRO_KEY_4:
                current_line.append("4");
                break;
            case ALLEGRO_KEY_5:
                current_line.append("5");
                break;
            case ALLEGRO_KEY_6:
                current_line.append("6");
                break;
            case ALLEGRO_KEY_7:
                current_line.append("7");
                break;
            case ALLEGRO_KEY_8:
                current_line.append("8");
                break;
            case ALLEGRO_KEY_9:
                current_line.append("9");
                break;
            case ALLEGRO_KEY_SPACE:
                current_line.append(" ");
                break;
            case ALLEGRO_KEY_BACKSPACE:
                current_line.pop_back();
                break;
            case ALLEGRO_KEY_ENTER:
            {
                int i;
                for(i=0; i<n_log_lines; i++)
                    log[i+1] = log[i];
                log[0] = current_line;
                n_log_lines++;
                //send command
                current_line.clear();
                //write feedback
            }
                break;
            case ALLEGRO_KEY_TAB:
                show_log = !show_log;
                break;
            case ALLEGRO_KEY_UP:
                if(log_pos < n_log_lines)
                    log_pos++;
                break;
            case ALLEGRO_KEY_DOWN:
                if(log_pos > 0)
                    log_pos--;
                break;
            default:
                break;
        }
    }
}

#endif //PROMPT
