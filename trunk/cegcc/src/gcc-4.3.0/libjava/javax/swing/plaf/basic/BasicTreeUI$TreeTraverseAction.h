
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicTreeUI$TreeTraverseAction__
#define __javax_swing_plaf_basic_BasicTreeUI$TreeTraverseAction__

#pragma interface

#include <javax/swing/AbstractAction.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
      namespace event
      {
          class ActionEvent;
      }
    }
  }
  namespace javax
  {
    namespace swing
    {
      namespace plaf
      {
        namespace basic
        {
            class BasicTreeUI;
            class BasicTreeUI$TreeTraverseAction;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicTreeUI$TreeTraverseAction : public ::javax::swing::AbstractAction
{

public:
  BasicTreeUI$TreeTraverseAction(::javax::swing::plaf::basic::BasicTreeUI *, jint, ::java::lang::String *);
  virtual void actionPerformed(::java::awt::event::ActionEvent *);
  virtual jboolean isEnabled();
public: // actually protected
  jint __attribute__((aligned(__alignof__( ::javax::swing::AbstractAction)))) direction;
public: // actually package-private
  ::javax::swing::plaf::basic::BasicTreeUI * this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicTreeUI$TreeTraverseAction__
