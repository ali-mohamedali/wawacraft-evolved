#ifndef SETTINGS_H
#define SETTINGS_H

#include "../libs.hpp"

namespace settings{
  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value> 
  class handle{
  public:
    handle(object*);

    void hold();
    void drop();
  
    mutex_type get_state();
  private:
    void set(mutex_type);
  
    mutex_type get();

    object* handled_object;
  };

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  handle<mutex_type, object, default_value, held_value>::handle(object* g_object)
  {
    if(g_object){
      handled_object=g_object;
    }
  }

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  void handle<mutex_type, object, default_value, held_value>::hold()
  {
    set(held_value);
  }

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  void handle<mutex_type, object, default_value, held_value>::drop()
  {
    set(default_value);
  }

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  mutex_type handle<mutex_type, object, default_value, held_value>::get_state()
  {
    return get();
  }

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  void handle<mutex_type, object, default_value, held_value>::set(mutex_type g_value)
  {
    handled_object->mutex_set(g_value);
  }

  template <typename mutex_type, typename object, mutex_type default_value, mutex_type held_value>
  mutex_type handle<mutex_type, object, default_value, held_value>::get()
  {
    return handled_object->mutex_get();
  }
  
  template <typename type, typename string_type=std::string, typename mutex_type=bool, mutex_type m_default_value=false, mutex_type m_held_value=true>
  class setting{
  public:
    typedef std::unordered_map<string_type, type> table;

    template <typename I, typename J, I i, I j> friend class handle;

    setting(type, table, void (*)());

    void responder_set(void (*)());
    
    void default_set(type);
    void values_set(table);
  
    void manage(string_type);

    mutex_type held();
  
    type access();
  
  private:
    void alert();
    
    void set(type);
    type search(string_type);

    void mutex_set(mutex_type);
    mutex_type mutex_get();

    void (*responder)();
    
    type default_value;
    type data;
 
    mutex_type mutex;
  
    table values;
  };

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  setting<type, string_type, mutex_type, m_default_value, m_held_value>::setting(type g_default_value, table g_values, void(*g_responder)()=NULL):
    default_value(g_default_value),
    values(g_values),
    data(g_default_value),
    mutex(m_default_value),
    responder(g_responder)
  {
  
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::responder_set(void(*g_responder)())
  {
    responder=g_responder;
  }
  
  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::default_set(type g_default_value)
  {
    default_value=g_default_value;

    if(mutex_get()==m_held_value){
      data=default_value;
    }
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::values_set(table g_values)
  {
    if(mutex_get()==m_held_value){
      set(default_value);
    }

    values.clear();
    values=g_values;
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::manage(string_type g_option)
  {
    set(search(g_option));
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  mutex_type setting<type, string_type, mutex_type, m_default_value, m_held_value>::held()
  {
    return mutex_get();
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  type setting<type, string_type, mutex_type, m_default_value, m_held_value>::access()
  {
    return data;
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::alert()
  {
    if(responder!=NULL){
      (*responder)();
    }
  }
  
  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::set(type g_value)
  {
    data=g_value;

    alert();
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  type setting<type, string_type, mutex_type, m_default_value, m_held_value>::search(string_type g_option)
  { 
    typename table::iterator i=values.find(g_option);

    if(i!=values.end()){
      return i->second;
    }else{
      return default_value;
    }
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  void setting<type, string_type, mutex_type, m_default_value, m_held_value>::mutex_set(mutex_type g_value)
  {
    mutex=g_value;

    if(mutex==m_default_value){
      data=default_value;
    }
  }

  template <typename type, typename string_type, typename mutex_type, mutex_type m_default_value, mutex_type m_held_value>
  mutex_type setting<type, string_type, mutex_type, m_default_value, m_held_value>::mutex_get()
  {
    return mutex;
  }
}

#endif
