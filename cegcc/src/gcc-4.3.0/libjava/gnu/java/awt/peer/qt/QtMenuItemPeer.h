
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_awt_peer_qt_QtMenuItemPeer__
#define __gnu_java_awt_peer_qt_QtMenuItemPeer__

#pragma interface

#include <gnu/java/awt/peer/qt/QtMenuComponentPeer.h>
extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace awt
      {
        namespace peer
        {
          namespace qt
          {
              class QtMenuItemPeer;
              class QtToolkit;
          }
        }
      }
    }
  }
  namespace java
  {
    namespace awt
    {
        class MenuItem;
    }
  }
}

class gnu::java::awt::peer::qt::QtMenuItemPeer : public ::gnu::java::awt::peer::qt::QtMenuComponentPeer
{

public:
  QtMenuItemPeer(::gnu::java::awt::peer::qt::QtToolkit *, ::java::awt::MenuItem *);
public: // actually protected
  virtual void init();
  virtual void setup();
private:
  void create(::java::lang::String *, jboolean, jboolean);
public:
  virtual void finalize();
  virtual void dispose();
private:
  void fireClick(jint);
public:
  virtual void disable();
  virtual void enable();
  virtual void setEnabled(jboolean);
  virtual void setLabel(::java::lang::String *);
  virtual void setState(jboolean);
  static ::java::lang::Class class$;
};

#endif // __gnu_java_awt_peer_qt_QtMenuItemPeer__
