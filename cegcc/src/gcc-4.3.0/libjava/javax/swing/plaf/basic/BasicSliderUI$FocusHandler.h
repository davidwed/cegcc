
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicSliderUI$FocusHandler__
#define __javax_swing_plaf_basic_BasicSliderUI$FocusHandler__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
      namespace event
      {
          class FocusEvent;
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
            class BasicSliderUI;
            class BasicSliderUI$FocusHandler;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicSliderUI$FocusHandler : public ::java::lang::Object
{

public:
  BasicSliderUI$FocusHandler(::javax::swing::plaf::basic::BasicSliderUI *);
  virtual void focusGained(::java::awt::event::FocusEvent *);
  virtual void focusLost(::java::awt::event::FocusEvent *);
public: // actually package-private
  ::javax::swing::plaf::basic::BasicSliderUI * __attribute__((aligned(__alignof__( ::java::lang::Object)))) this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicSliderUI$FocusHandler__
