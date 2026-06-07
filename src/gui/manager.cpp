#include "libs.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

static const bool windows::manager::YES=common::signals::YES;
static const bool windows::manager::NO=common::signals::NO;

windows::manager::manager():
  bregister(),
  register_handle(&bregister)
{ 
  logging::log pen("manager", "windows::manager");

  pen.record("Internal window-ring manager initialized.");

  pen.record("New internal window-ring manager is holding the manager-register.");
  if(windows::manager_register::superior_set(this)==common::signals::SUCCESS){
    register_handle.hold();
    pen.record("Internal window-ring manager succeeded in holding the manager-register mutex.");
  }else{
    pen.error("Failed to register with manager-register; the internal window-ring manager and its nodes might not function properly.");
  }
}

windows::manager::~manager()
{
  logging::log pen("~manager", "windows::manager");
  pen.record("Destroying internal window-ring manager.");
  
  nodes.clear();

  windows::manager_register::clear(this);
  windows::manager_register::superior_clear(this);

  register_handle.drop();
}

void windows::manager::nodes_add(windows::node* g_node)
{
  logging::log pen("nodes_add", "windows::manager");
  pen.record("Adding new window-node to window-ring.");
  
  nodes.push_front(g_node);

  pen.record("Binding the manager to be the node's superior.");
  (*nodes.begin())->superior_set(this);

  pen.record("Binding key-events callback for the node's window.");
  if(windows::manager_register::set_key_callback(this, *(nodes.begin()))==common::signals::FAILURE){
    pen.error("Failed to bind key-events callback for a node's window. Window won't respond properly now.");
  }else{
    pen.record("Succeeded at binding key-events callback for the node's window.");
  }
}

void windows::manager::nodes_clear()
{
  logging::log pen("nodes_clear", "windows::manager");
  pen.record("Clearing all nodes in window-ring.");
  
  nodes.clear();
}

void windows::manager::cycle()
{
  nodes_prune();

  if(nodes_present()==YES){
    for(ring::iterator i=nodes.begin(); i!=nodes.end(); i++){
      if(*i!=NULL){
	(*i)->window_update();
      }
    }
  }
}

bool windows::manager::nodes_present()
{
  return (nodes.size()>=1) ? YES : NO;
}
 
void windows::manager::nodes_prune()
{
  logging::log pen("nodes_prune", "windows::manager");
  
  for(ring::iterator i=nodes.begin(); i!=nodes.end(); i++){
    if(*i!=NULL){
      if((*i)->window_get()->should_close()==windows::window::YES){
	pen.record("Erasing window-node scheduled to close.");
	pen.record("Destroying window-node, then removing from window-ring.");
	delete (*i);
	i=nodes.erase(i);
      }
    }else{
      pen.error("Invalid window-node pointer present, removing from window-ring.");
      i=nodes.erase(i);
    }
  }
}

events::keyboard::event windows::manager::node_key_get(windows::node* g_node, events::keyboard::key g_key)
{
  if(g_node!=NULL){
    events::keyboard::event ret;

    ret.bkey=g_key;
    ret.state=events::keyboard::map::action_code_lookup(glfwGetKey(windows::reserve::get_window_handle(*(g_node->window_get())), events::keyboard::map::reverse_key_code_lookup(g_key)));

    return ret;
  }

  return events::keyboard::event{events::keyboard::KB_KEY_NOACTION, events::keyboard::KB_KEY_NOKEY};
}
