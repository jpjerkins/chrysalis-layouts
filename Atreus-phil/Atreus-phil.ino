/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"



#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_Plus LSHIFT(Key_Equals)

enum {
  QWERTY,
  FUN,
  UPPER
};

/* *INDENT-OFF* */
KEYMAPS(
  [0] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W       ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S       ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X       ,Key_C       ,Key_V         ,Key_B         ,Key_Esc
      ,Key_Esc ,Key_LeftGui ,Key_Tab     ,MO(2)         ,Key_LeftShift ,Key_Enter

                    ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                    ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
      ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
      ,MO(1)        ,Key_Space ,MO(3)      ,Key_Minus ,Key_Quote  ,Key_Enter
  ),
/*
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B, Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_LeftShift ,Key_Backspace ,Key_LeftControl

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_LeftAlt  ,Key_Space ,MO(FUN)    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At           ,Key_UpArrow   ,Key_Dollar           ,Key_Percent
      ,Key_LeftParen   ,Key_LeftArrow    ,Key_DownArrow ,Key_RightArrow       ,Key_RightParen
      ,Key_LeftBracket ,Key_RightBracket ,Key_Hash      ,Key_LeftCurlyBracket ,Key_RightCurlyBracket ,Key_Caret
      ,TG(UPPER)       ,Key_Insert       ,Key_LeftGui   ,Key_LeftShift        ,Key_Delete         ,Key_LeftControl

                   ,Key_PageUp   ,Key_7 ,Key_8      ,Key_9 ,Key_Backspace
                   ,Key_PageDown ,Key_4 ,Key_5      ,Key_6 ,___
      ,Key_And     ,Key_Star     ,Key_1 ,Key_2      ,Key_3 ,Key_Plus
      ,Key_LeftAlt ,Key_Space    ,___   ,Key_Period ,Key_0 ,Key_Equals
  ),

  [UPPER] = KEYMAP_STACKED
  (
       Key_Insert            ,Key_Home                 ,Key_UpArrow   ,Key_End        ,Key_PageUp
      ,Key_Delete            ,Key_LeftArrow            ,Key_DownArrow ,Key_RightArrow ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,Consumer_VolumeIncrement ,XXX           ,XXX            ,___ ,___
      ,MoveToLayer(QWERTY)   ,Consumer_VolumeDecrement ,___           ,___            ,___ ,___

                ,Key_UpArrow   ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX           ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   )*/
)
/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(
  Qukeys,
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  SpaceCadet,
  OneShot,
  Macros,
  MouseKeys
);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_QWERTY:
    // This macro is currently unused, but is kept around for compatibility
    // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
    // longer do. We keep it so that if someone still has the old layout with
    // the macro in EEPROM, it will keep working after a firmware update.
    Layer.move(QWERTY);
    break;
  case MACRO_VERSION_INFO:
    if (keyToggledOn(keyState)) {
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
    }
    break;
  default:
    break;
  }

  return MACRO_NONE;
}

void setup() {
  QUKEYS(
/*
    kaleidoscope::plugin::Qukey(Qukeys.layer_wildcard, KeyAddr(2, 1), Key_LeftControl), // A
    kaleidoscope::plugin::Qukey(Qukeys.layer_wildcard, KeyAddr(2, 2), Key_LeftShift),   // S
    kaleidoscope::plugin::Qukey(Qukeys.layer_wildcard, KeyAddr(2, 3), Key_LeftGui),     // D
    kaleidoscope::plugin::Qukey(Qukeys.layer_wildcard, KeyAddr(2, 4), Key_LeftAlt),     // F

    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 0), Key_LeftControl),  // Z
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 1), Key_LeftShift),    // X
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 2), Key_LeftGui),      // C
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 3), Key_LeftAlt),      // V

    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 8), Key_RightAlt),      // M
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 9), Key_RightGui),      // ,
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 10), Key_RightShift),   // .
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_RightControl), // /
*/

    // kaleidoscope::plugin::Qukey(2, KeyAddr(2, 0), Key_LeftControl), // Z - not dual-use; set in Chrysalis
    kaleidoscope::plugin::Qukey(2, KeyAddr(2, 1), Key_LeftShift),    // X
    kaleidoscope::plugin::Qukey(2, KeyAddr(2, 2), Key_LeftGui),      // C
    kaleidoscope::plugin::Qukey(2, KeyAddr(2, 3), Key_LeftAlt)       // V
  )
  Qukeys.setHoldTimeout(150); // Default 250
  Qukeys.setOverlapThreshold(100); // Default 70
  Qukeys.setMinimumHoldTime(50); // Default 50
  Qukeys.setMinimumPriorInterval(75); // Default 75

  Kaleidoscope.setup();
  SpaceCadet.disable();
  EEPROMKeymap.setup(10);
}

void loop() {
  Kaleidoscope.loop();
}
