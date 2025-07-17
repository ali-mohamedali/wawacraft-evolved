#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "../libs.hpp"
#include "../graphics/graphics.hpp"

namespace windows{
  class node{
  public:
    typedef void (*update_callback)(window);

    node(const window&, update_callback g_updater=&default_update_callback);
    ~node();
    
    static void default_update_callback(window);

    void update();
    
    update_callback update_callback_get();

    window* window_get();

    graphics::gl_handle render_handle_get();
    
  private:
    update_callback updater;
    
    window identity;
  };

  class manager{
  public:
    typedef std::list<node*> ring;
    
    manager();
    ~manager();
    
    void nodes_add(node*);
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
