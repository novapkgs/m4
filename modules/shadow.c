/* GNU m4 -- A simple macro processor
   Copyright 1999, 2000 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307  USA
*/

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <m4module.h>

#define LTDL_MODULE_NAME shadow

#define m4_builtin_table	shadow_LTX_m4_builtin_table
#define m4_macro_table		shadow_LTX_m4_macro_table

/*		function	macros	blind */
#define builtin_functions			\
	BUILTIN (shadow,	FALSE,	FALSE)	\
	BUILTIN (test,		FALSE,	FALSE)

#define BUILTIN(handler, macros,  blind)	M4BUILTIN(handler)
  builtin_functions
#undef BUILTIN

m4_builtin m4_builtin_table[] =
{
#define BUILTIN(handler, macros, blind)		\
	{ STR(handler), CONC(builtin_, handler), macros, blind },

  builtin_functions
#undef BUILTIN

  { 0, 0, FALSE, FALSE },
};

m4_macro m4_macro_table[] =
{
  /* name		text */
  { "__test__",		"`shadow'" },
  { 0,			0 },
};



M4INIT_HANDLER (shadow)
{
  const lt_dlinfo *info = 0;
  const char *s = "Shadow module loaded.";

  if (handle)
    info = lt_dlgetinfo (handle);
  
  /* Only display the message on first load.  */
  if (obs && info && (info->ref_count == 1))
    obstack_grow (obs, s, strlen(s));
}



/*---------.
| shadow() |
`---------*/
M4BUILTIN_HANDLER (shadow)
{
  char *s = "Shadow::`shadow' called.";
  obstack_grow (obs, s, strlen(s));
}

/*-------.
| test() |
`-------*/
M4BUILTIN_HANDLER (test)
{
  char *s = "Shadow::`test' called.";
  obstack_grow (obs, s, strlen(s));
}
