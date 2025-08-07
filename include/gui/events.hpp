#ifndef EVENTS_H
#define EVENTS_H

#include "../libs.hpp"

namespace events{
  namespace keyboard{
    enum action
      {
	KB_KEY_NOACTION,
	KB_KEY_RELEASED,
	KB_KEY_PRESSED,
	KB_KEY_REPEATING
      };

    enum key
      {
	KB_KEY_NOKEY,
	KB_KEY_0,
	KB_KEY_1,
	KB_KEY_2,
	KB_KEY_3,
	KB_KEY_4,
	KB_KEY_5,
	KB_KEY_6,
	KB_KEY_7,
	KB_KEY_8,
	KB_KEY_9,
	KB_KEY_A,
	KB_KEY_B,
	KB_KEY_C,
	KB_KEY_D,
	KB_KEY_E,
	KB_KEY_F,
	KB_KEY_G,
	KB_KEY_H,
	KB_KEY_I,
	KB_KEY_J,
	KB_KEY_K,
	KB_KEY_L,
	KB_KEY_M,
	KB_KEY_N,
	KB_KEY_O,
	KB_KEY_P,
	KB_KEY_Q,
	KB_KEY_R,
	KB_KEY_S,
	KB_KEY_T,
	KB_KEY_U,
	KB_KEY_V,
	KB_KEY_W,
	KB_KEY_X,
	KB_KEY_Y,
	KB_KEY_Z
      };

    struct event{
      action state;
      key bkey;
    };

    class map{
    public:
      static event event_translate(int, int, int, int);

      static action action_code_lookup(int);
      static key key_code_lookup(int);

      static int reverse_action_code_lookup(action);
      static int reverse_key_code_lookup(key);

    private:
      static std::unordered_map<int, action> action_table;
      static std::unordered_map<int, key> key_table;
    };
  }
}

#endif
