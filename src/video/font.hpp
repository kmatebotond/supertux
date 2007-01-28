//  $Id$
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef SUPERTUX_FONT_H
#define SUPERTUX_FONT_H

#include <string>
#include <stdint.h>

#include "video/surface.hpp"
#include "math/vector.hpp"
#include "math/rect.hpp"

enum FontAlignment {
  LEFT_ALLIGN,
  CENTER_ALLIGN,
  RIGHT_ALLIGN
};

class Font
{
public:
  /** Construct a fixed-width font 
   * 
   *  @param file image file containing the characters
   *  @param shadowfile image file containing the characters shadows
   *  @param w width of a character
   *  @param h height of a character
   */
  Font(const std::string& file, const std::string& shadowfile,
       int w, int h, int shadowsize = 2);

  /** Construct a variable-width font 
   * 
   *  @param file image file containing the characters
   */
  Font(const std::string& file, int char_width, int char_height);

  ~Font();

  /** returns the width of a given text. (Note that I won't add a normal
   * get_width function here, as we might switch to variable width fonts in the
   * future.)
   * Supports breaklines.
   */
  float get_text_width(const std::string& text) const;

  /** returns the height of a given text. This function supports breaklines.
   * In case, you are positive that your text doesn't use break lines, you can
   * just use get_height().
   */
  float get_text_height(const std::string& text) const;

  /**
   * returns the height of the font.
   */
  float get_height() const;

  /**
   * returns the given string, truncated (preferrably at whitespace) to be at most max_chars characters long
   */
  static std::string wrap_to_chars(const std::string& text, int max_chars, std::string* overflow);

  /** Draws the given text to the screen. Also needs the position.
   * Type of alignment, drawing effect and alpha are optional. */
  void draw(const std::string& text, const Vector& pos,
            FontAlignment allignment = LEFT_ALLIGN,
            DrawingEffect drawing_effect = NO_EFFECT,
            float alpha = 1.0f) const;

private:
  friend class DrawingContext;

  void draw_text(const std::string& text, const Vector& pos,
                 DrawingEffect drawing_effect = NO_EFFECT,
                 float alpha = 1.0f) const;

  void draw_chars(Surface* pchars, const std::string& text,
                  const Vector& position, DrawingEffect drawing_effect,
                  float alpha) const;

  Surface* glyph_surface;
  Surface* shadow_chars;
  int char_width;
  int char_height;
  int shadowsize;

  /// the number of the first character that is represented in the font
  uint32_t first_char;
  /// the number of the last character that is represented in the font
  uint32_t char_count;
  
  /** Location of the characters inside the surface */
  std::vector<Rect> glyphs;
};

#endif
