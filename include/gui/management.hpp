#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "../libs.hpp"
#include "../graphics/graphics.hpp"

namespace windows{
  class node{
  public:
    typedef void (*callback)(window&);

    node(const window&, callback g_initializer=&default_init_callback, callback g_updater=&default_update_callback, callback g_death=&default_death_callback);
    ~node();

    static void default_init_callback(window&);
    static void default_update_callback(window&);
    static void default_death_callback(window&);
    
    void update();

    callback init_callback_get();
    callback update_callback_get();
    callback death_callback_get();
    
    window* window_get();

    graphics::gl_handle render_handle_get();
    
  private:
    void init();
    void die();
    
    bool initialized;
    
    callback initializer;
    callback updater;
    callback death;
    
    window identity;
  };

  class manager{
  public:
    typedef std::list<node> ring;
    
    manager();
    ~manager();
    
    void nodes_add(const node&);
    void nodes_clear();
    
    void cycle();
    
    bool nodes_present();
    
    static const bool YES;
    static const bool NO;
    
  private:
    void nodes_prune();
    
    ring nodes;
  };
}

#endif
