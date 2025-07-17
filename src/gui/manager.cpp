#include "libs.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

static const bool windows::manager::YES=true;
static const bool windows::manager::NO=false;

windows::manager::manager()
{
  
}

windows::manager::~manager()
{
  nodes.clear();
}

void windows::manager::nodes_add(windows::node* g_node)
{
  nodes.push_front(g_node);
}

void windows::manager::nodes_clear()
{
  nodes.clear();
}

void windows::manager::cycle()
{
  nodes_prune();

  if(nodes_present()==YES){
    for(ring::iterator i=nodes.begin(); i!=nodes.end(); i++){
      (*i)->update();
    }
  }
}

bool windows::manager::nodes_present()
{
  return (nodes.size()>=1) ? YES : NO;
}

void windows::manager::nodes_prune()
{
  for(ring::iterator i=nodes.begin(); i!=nodes.end(); i++){
    if((*i)->window_get()->should_close()==windows::window::YES){
      (*i)->windows::node::~node();
      
      i=nodes.erase(i);
    }
  }
}
