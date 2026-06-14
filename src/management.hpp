#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "libs.hpp"
#include "settings.hpp"
#include "graphics.hpp"
#include "common.hpp"
#include "events.hpp"

namespace windows{
  class manager;
  
  class node{
  public:
    friend class manager;
    
    node(const window&);
    ~node();
    
    virtual void window_update();
    virtual void window_respond(events::keyboard::event);
    
    window* window_get();

    manager* superior_get();
    
    graphics::gl_handle render_handle_get();
    
  protected:
    void superior_set(manager*);
    
    bool initialized;
    
    window identity;
    
    manager* superior;
    
  private:
    void init();
  };
  
  class manager_register{
  public:
    template <typename I, typename J, I i, I j> friend class settings::handle;
    
    typedef std::unordered_map<GLFWwindow*, node*> node_resource_table;

    static bool clear(manager*);
    
    static bool superior_clear(manager*);
    static bool superior_set(manager*);
    
    static bool set_key_callback(manager*, node*);
    
  private:
    static void standard_key_callback(GLFWwindow*, int, int, int, int);
    
    static void mutex_set(bool);
    static bool mutex_get();
    
    static bool mutex;
    
    static node_resource_table bnode_table;
    
    static manager* superior;
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

    events::keyboard::event node_key_get(node*, events::keyboard::key);
    
    static const bool YES;
    static const bool NO;
    
  private:
    void nodes_prune();
    
    ring nodes;

    manager_register bregister;
    settings::handle<bool, manager_register, common::values::MUTEX_DROPPED, common::values::MUTEX_HELD> register_handle;
  };
}

#endif
