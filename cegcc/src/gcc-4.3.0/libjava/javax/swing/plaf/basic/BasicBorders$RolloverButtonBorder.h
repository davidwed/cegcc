
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicBorders$RolloverButtonBorder__
#define __javax_swing_plaf_basic_BasicBorders$RolloverButtonBorder__

#pragma interface

#include <javax/swing/plaf/basic/BasicBorders$ButtonBorder.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Color;
        class Component;
        class Graphics;
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
            class BasicBorders$RolloverButtonBorder;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicBorders$RolloverButtonBorder : public ::javax::swing::plaf::basic::BasicBorders$ButtonBorder
{

public:
  BasicBorders$RolloverButtonBorder(::java::awt::Color *, ::java::awt::Color *, ::java::awt::Color *, ::java::awt::Color *);
  virtual void paintBorder(::java::awt::Component *, ::java::awt::Graphics *, jint, jint, jint, jint);
public: // actually package-private
  static const jlong serialVersionUID = 1976364864896996846LL;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicBorders$RolloverButtonBorder__
