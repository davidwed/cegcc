/* LocaleInformation_ko_KR.java
   Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


// This file was automatically generated by localedef.

package gnu.java.locale;

import java.util.ListResourceBundle;

public class LocaleInformation_ko_KR extends ListResourceBundle
{
  static final String decimalSeparator = ".";
  static final String groupingSeparator = ",";
  static final String numberFormat = "#,###,##0.###";
  static final String percentFormat = "#,###,##0%";
  static final String[] weekdays = { null, "\uC77C\uC694\uC77C", "\uC6D4\uC694\uC77C", "\uD654\uC694\uC77C", "\uC218\uC694\uC77C", "\uBAA9\uC694\uC77C", "\uAE08\uC694\uC77C", "\uD1A0\uC694\uC77C" };

  static final String[] shortWeekdays = { null, "\uC77C", "\uC6D4", "\uD654", "\uC218", "\uBAA9", "\uAE08", "\uD1A0" };

  static final String[] shortMonths = { " 1\uC6D4", " 2\uC6D4", " 3\uC6D4", " 4\uC6D4", " 5\uC6D4", " 6\uC6D4", " 7\uC6D4", " 8\uC6D4", " 9\uC6D4", "10\uC6D4", "11\uC6D4", "12\uC6D4", null };

  static final String[] months = { "\uC77C\uC6D4", "\uC774\uC6D4", "\uC0BC\uC6D4", "\uC0AC\uC6D4", "\uC624\uC6D4", "\uC720\uC6D4", "\uCE60\uC6D4", "\uD314\uC6D4", "\uAD6C\uC6D4", "\uC2DC\uC6D4", "\uC2ED\uC77C\uC6D4", "\uC2ED\uC774\uC6D4", null };

  static final String[] ampms = { "\uC624\uC804", "\uC624\uD6C4" };

  static final String shortDateFormat = "yyyy MM dd";
  static final String defaultTimeFormat = "a hh m s";
  static final String currencySymbol = "\uFFE6";
  static final String intlCurrencySymbol = "KRW";
  static final String currencyFormat = "$#,###,##0.;$-#,###,##0.";

  private static final Object[][] contents =
  {
    { "weekdays", weekdays },
    { "shortWeekdays", shortWeekdays },
    { "shortMonths", shortMonths },
    { "months", months },
    { "ampms", ampms },
    { "shortDateFormat", shortDateFormat },
    { "defaultTimeFormat", defaultTimeFormat },
    { "currencySymbol", currencySymbol },
    { "intlCurrencySymbol", intlCurrencySymbol },
    { "currencyFormat", currencyFormat },
    { "decimalSeparator", decimalSeparator },
    { "groupingSeparator", groupingSeparator },
    { "numberFormat", numberFormat },
    { "percentFormat", percentFormat },
  };

  public Object[][] getContents () { return contents; }
}
