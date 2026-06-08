#include "libs.hpp"
#include "common.hpp"
#include "logging.hpp"
#include "management.hpp"
#include "events.hpp"

static bool windows::manager_register::mutex=common::values::MUTEX_DROPPED;
static windows::manager* windows::manager_register::superior=NULL;
static std::unordered_map<GLFWwindow*, windows::node*> windows::manager_register::bnode_table={};

static bool windows::manager_register::clear(windows::manager* requesting_manager)
{
  if(requesting_manager==superior || mutex==common::values::MUTEX_DROPPED){
    bnode_table.clear();
    return common::signals::SUCCESS;
  }

  return common::signals::FAILURE;
}

static bool windows::manager_register::superior_clear(windows::manager* requesting_manager)
{
  if(requesting_manager==superior || mutex==common::values::MUTEX_DROPPED){
    return superior_set(NULL);
  }

  return common::signals::FAILURE;
}

static bool windows::manager_register::superior_set(windows::manager* g_superior)
{
  if((mutex==common::values::MUTEX_DROPPED) || (g_superior==superior) || (superior==NULL)){
    superior=g_superior;
    return common::signals::SUCCESS;
  }

  return common::signals::FAILURE;
}

static bool windows::manager_register::set_key_callback(windows::manager* requesting_manager, windows::node* g_node)
{
  if(requesting_manager==superior || mutex==common::values::MUTEX_DROPPED){
    if(g_node!=NULL){
      bnode_table.insert({windows::reserve::get_window_handle(*(g_node->window_get())), g_node});
      
      glfwSetKeyCallback(windows::reserve::get_window_handle(*(g_node->window_get())), &standard_key_callback);
      return common::signals::SUCCESS;
    }
  }

  return common::signals::FAILURE;
}

static void windows::manager_register::standard_key_callback(GLFWwindow* g_window, int key, int scancode, int action, int mods)
{
  logging::log pen("standard_key_callback", "windows::manager_register", false);
  
  std::unordered_map<GLFWwindow*, node*>::iterator found_node=bnode_table.find(g_window);
  
  if(found_node!=bnode_table.end()){
    if(found_node->second!=NULL){
      found_node->second->window_respond(events::keyboard::map::event_translate(key, scancode, action, mods));
      return common::signals::SUCCESS;
    }else{
      pen.error("Invalid window-node pointer registered in table, remarking failure upon exit.");
      pen.record("Removing entry from the table now.");
      
      bnode_table.erase(found_node);
      
      return common::signals::FAILURE;
    }
  }else{
    pen.record("No associated node found for a window resource pointer. A request was made for a resource that doesn\'t exist.");
    pen.record("Window resource pointer might be invalidated soon anyway.");
    return common::signals::FAILURE;
  }
}

static void windows::manager_register::mutex_set(bool g_mutex)
{
  mutex=g_mutex;
}

static bool windows::manager_register::mutex_get()
{
  return mutex;
}
