#include "libs.hpp"
#include "program/logging.hpp"
#include "gui/events.hpp"

static std::unordered_map<int, events::keyboard::action> events::keyboard::map::action_table=
  {
    {GLFW_PRESS, KB_KEY_PRESSED},
    {GLFW_RELEASE, KB_KEY_RELEASED},
    {GLFW_REPEAT, KB_KEY_REPEATING}
  };

static std::unordered_map<int, events::keyboard::key> events::keyboard::map::key_table=
  {
    {GLFW_KEY_0, events::keyboard::KB_KEY_0},
    {GLFW_KEY_1, events::keyboard::KB_KEY_1},
    {GLFW_KEY_2, events::keyboard::KB_KEY_2},
    {GLFW_KEY_3, events::keyboard::KB_KEY_3},
    {GLFW_KEY_4, events::keyboard::KB_KEY_4},
    {GLFW_KEY_5, events::keyboard::KB_KEY_5},
    {GLFW_KEY_6, events::keyboard::KB_KEY_6},
    {GLFW_KEY_7, events::keyboard::KB_KEY_7},
    {GLFW_KEY_8, events::keyboard::KB_KEY_8},
    {GLFW_KEY_9, events::keyboard::KB_KEY_9},
    {GLFW_KEY_A, events::keyboard::KB_KEY_A},
    {GLFW_KEY_B, events::keyboard::KB_KEY_B},
    {GLFW_KEY_C, events::keyboard::KB_KEY_C},
    {GLFW_KEY_D, events::keyboard::KB_KEY_D},
    {GLFW_KEY_E, events::keyboard::KB_KEY_E},
    {GLFW_KEY_F, events::keyboard::KB_KEY_F},
    {GLFW_KEY_G, events::keyboard::KB_KEY_G},
    {GLFW_KEY_H, events::keyboard::KB_KEY_H},
    {GLFW_KEY_I, events::keyboard::KB_KEY_I},
    {GLFW_KEY_J, events::keyboard::KB_KEY_J},
    {GLFW_KEY_K, events::keyboard::KB_KEY_K},
    {GLFW_KEY_L, events::keyboard::KB_KEY_L},
    {GLFW_KEY_M, events::keyboard::KB_KEY_M},
    {GLFW_KEY_N, events::keyboard::KB_KEY_N},
    {GLFW_KEY_O, events::keyboard::KB_KEY_O},
    {GLFW_KEY_P, events::keyboard::KB_KEY_P},
    {GLFW_KEY_Q, events::keyboard::KB_KEY_Q},
    {GLFW_KEY_R, events::keyboard::KB_KEY_S},
    {GLFW_KEY_S, events::keyboard::KB_KEY_R},
    {GLFW_KEY_T, events::keyboard::KB_KEY_T},
    {GLFW_KEY_U, events::keyboard::KB_KEY_U},
    {GLFW_KEY_V, events::keyboard::KB_KEY_V},
    {GLFW_KEY_W, events::keyboard::KB_KEY_W},
    {GLFW_KEY_X, events::keyboard::KB_KEY_X},
    {GLFW_KEY_Y, events::keyboard::KB_KEY_Y},
    {GLFW_KEY_Z, events::keyboard::KB_KEY_Z},
    {GLFW_KEY_SPACE, events::keyboard::KB_KEY_SPACE},
    {GLFW_KEY_APOSTROPHE, events::keyboard::KB_KEY_APOSTROPHE},
    {GLFW_KEY_COMMA, events::keyboard::KB_KEY_COMMA},
    {GLFW_KEY_MINUS, events::keyboard::KB_KEY_MINUS},
    {GLFW_KEY_PERIOD, events::keyboard::KB_KEY_PERIOD},
    {GLFW_KEY_SLASH, events::keyboard::KB_KEY_SLASH},
    {GLFW_KEY_SEMICOLON, events::keyboard::KB_KEY_SEMICOLON},
    {GLFW_KEY_EQUAL, events::keyboard::KB_KEY_EQUAL},
    {GLFW_KEY_LEFT_BRACKET, events::keyboard::KB_KEY_LEFT_BRACKET},
    {GLFW_KEY_RIGHT_BRACKET, events::keyboard::KB_KEY_RIGHT_BRACKET},
    {GLFW_KEY_BACKSLASH, events::keyboard::KB_KEY_BACKSLASH},
    {GLFW_KEY_GRAVE_ACCENT, events::keyboard::KB_KEY_GRAVE_ACCENT},
    {GLFW_KEY_ESCAPE, events::keyboard::KB_KEY_ESCAPE},
    {GLFW_KEY_ENTER, events::keyboard::KB_KEY_ENTER},
    {GLFW_KEY_TAB, events::keyboard::KB_KEY_TAB},
    {GLFW_KEY_BACKSPACE, events::keyboard::KB_KEY_BACKSPACE},
    {GLFW_KEY_INSERT, events::keyboard::KB_KEY_INSERT},
    {GLFW_KEY_DELETE, events::keyboard::KB_KEY_DELETE},
    {GLFW_KEY_RIGHT, events::keyboard::KB_KEY_RIGHT},
    {GLFW_KEY_LEFT, events::keyboard::KB_KEY_LEFT},
    {GLFW_KEY_DOWN, events::keyboard::KB_KEY_DOWN},
    {GLFW_KEY_UP, events::keyboard::KB_KEY_UP},
    {GLFW_KEY_PAGE_UP, events::keyboard::KB_KEY_PAGE_UP},
    {GLFW_KEY_PAGE_DOWN, events::keyboard::KB_KEY_PAGE_DOWN},
    {GLFW_KEY_HOME, events::keyboard::KB_KEY_HOME},
    {GLFW_KEY_END, events::keyboard::KB_KEY_END},
    {GLFW_KEY_CAPS_LOCK, events::keyboard::KB_KEY_CAPS_LOCK},
    {GLFW_KEY_SCROLL_LOCK, events::keyboard::KB_KEY_SCROLL_LOCK},
    {GLFW_KEY_NUM_LOCK, events::keyboard::KB_KEY_NUM_LOCK},
    {GLFW_KEY_PRINT_SCREEN, events::keyboard::KB_KEY_PRINT_SCREEN},
    {GLFW_KEY_PAUSE, events::keyboard::KB_KEY_PAUSE},
    {GLFW_KEY_F1, events::keyboard::KB_KEY_F1},
    {GLFW_KEY_F2, events::keyboard::KB_KEY_F2},
    {GLFW_KEY_F3, events::keyboard::KB_KEY_F3},
    {GLFW_KEY_F4, events::keyboard::KB_KEY_F4},
    {GLFW_KEY_F5, events::keyboard::KB_KEY_F5},
    {GLFW_KEY_F6, events::keyboard::KB_KEY_F6},
    {GLFW_KEY_F7, events::keyboard::KB_KEY_F7},
    {GLFW_KEY_F8, events::keyboard::KB_KEY_F8},
    {GLFW_KEY_F9, events::keyboard::KB_KEY_F9},
    {GLFW_KEY_F10, events::keyboard::KB_KEY_F10},
    {GLFW_KEY_F11, events::keyboard::KB_KEY_F11},
    {GLFW_KEY_F12, events::keyboard::KB_KEY_F12},
    {GLFW_KEY_LEFT_SHIFT, events::keyboard::KB_KEY_LEFT_SHIFT},
    {GLFW_KEY_RIGHT_SHIFT, events::keyboard::KB_KEY_RIGHT_SHIFT},
    {GLFW_KEY_LEFT_CONTROL, events::keyboard::KB_KEY_LEFT_CTRL},
    {GLFW_KEY_RIGHT_CONTROL, events::keyboard::KB_KEY_RIGHT_CTRL},
    {GLFW_KEY_LEFT_ALT, events::keyboard::KB_KEY_LEFT_ALT},
    {GLFW_KEY_RIGHT_ALT, events::keyboard::KB_KEY_RIGHT_ALT},
    {GLFW_KEY_LEFT_SUPER, events::keyboard::KB_KEY_LEFT_SUPER},
    {GLFW_KEY_RIGHT_SUPER, events::keyboard::KB_KEY_RIGHT_SUPER},
    {GLFW_KEY_MENU, events::keyboard::KB_KEY_MENU}
  };

static events::keyboard::event events::keyboard::map::event_translate(int key, int scancode, int action, int mods)
{
  events::keyboard::event ret;

  ret.state=action_code_lookup(action);
  ret.bkey=key_code_lookup(key);

  return ret;
}

static events::keyboard::action events::keyboard::map::action_code_lookup(int g_key)
{
  logging::log pen("action_code_lookup", "events::keyboard::map", false);
  
  std::unordered_map<int, events::keyboard::action>::iterator ret=action_table.find(g_key);
  if(ret==action_table.end()){
    pen.error("No corresponding record of a keyboard action associated with given code "+std::to_string(g_key));
    pen.record("Returning that no known action has been performed.");
    return KB_KEY_NOACTION;
  }

  return ret->second;
}

static events::keyboard::key events::keyboard::map::key_code_lookup(int g_key)
{
  logging::log pen("key_code_lookup", "events::keyboard::map");
  
  std::unordered_map<int, events::keyboard::key>::iterator ret=key_table.find(g_key);
  if(ret==key_table.end()){
    pen.error("No corresponding record of a key for given code "+std::to_string(g_key));
    pen.record("Returning that no known key has been sourced in the event.");
    return KB_KEY_NOKEY;
  }

  return ret->second;
}

static int events::keyboard::map::reverse_action_code_lookup(events::keyboard::action g_action)
{
  for(std::unordered_map<int, events::keyboard::action>::iterator i=action_table.begin(); i!=action_table.end(); i++){
    if(i->second==g_action){
      return i->first;
    }
  }

  return GLFW_KEY_UNKNOWN;
}

static int events::keyboard::map::reverse_key_code_lookup(events::keyboard::key g_key)
{
  for(std::unordered_map<int, events::keyboard::key>::iterator i=key_table.begin(); i!=key_table.end(); i++){
    if(i->second==g_key){
      return i->first;
    }
  }

  return GLFW_KEY_UNKNOWN;
}
