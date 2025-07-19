#include "libs.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

static const bool windows::manager::YES=true;
static const bool windows::manager::NO=false;

windows::manager::manager()
{
  logging::log pen("manager", "windows::manager");

  pen.record("Internal window-ring manager initialized.");
}

windows::manager::~manager()
{
  logging::log pen("~manager", "windows::manager");
  pen.record("Destroying internal window-ring manager.");
  
  nodes.clear();
}

void windows::manager::nodes_add(const windows::node& g_node)
{
  logging::log pen("nodes_add", "windows::manager");
  pen.record("Adding new window-node to window-ring.");
  
  nodes.push_front(g_node);
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
      i->update();
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
    if(i->window_get()->should_close()==windows::window::YES){
      pen.record("Erasing window-node scheduled to close.");
      i=nodes.erase(i);
    }
  }
}
