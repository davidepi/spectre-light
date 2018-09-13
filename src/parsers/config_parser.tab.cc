// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "config_parser.tab.cc" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "config_parser.tab.hh"

// User implementation prologue.

#line 51 "config_parser.tab.cc" // lalr1.cc:415
// Unqualified %code blocks.
#line 28 "config_parser.y" // lalr1.cc:416
 
    #include "parsers/config_driver.hpp"

#line 57 "config_parser.tab.cc" // lalr1.cc:416


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 152 "config_parser.tab.cc" // lalr1.cc:491

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ConfigParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  ConfigParser::ConfigParser (ConfigDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  ConfigParser::~ConfigParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  ConfigParser::by_state::by_state ()
    : state (empty_state)
  {}

  ConfigParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  ConfigParser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  ConfigParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  ConfigParser::by_state::by_state (state_type s)
    : state (s)
  {}

  ConfigParser::symbol_number_type
  ConfigParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  ConfigParser::stack_symbol_type::stack_symbol_type ()
  {}

  ConfigParser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 141: // channel
        value.copy< imgchannel_t > (that.value);
        break;

      case 143: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 142: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 112: // "floating point value"
      case 144: // number
        value.copy< float > (that.value);
        break;

      case 111: // "integer value"
      case 145: // integer
        value.copy< int > (that.value);
        break;

      case 138: // element
        value.copy< metal_t > (that.value);
        break;

      case 113: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 110: // "positive integer value"
        value.copy< unsigned int > (that.value);
        break;

      default:
        break;
    }

  }

  ConfigParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 141: // channel
        value.move< imgchannel_t > (that.value);
        break;

      case 143: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 142: // vector
        value.move< Vec3 > (that.value);
        break;

      case 112: // "floating point value"
      case 144: // number
        value.move< float > (that.value);
        break;

      case 111: // "integer value"
      case 145: // integer
        value.move< int > (that.value);
        break;

      case 138: // element
        value.move< metal_t > (that.value);
        break;

      case 113: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 110: // "positive integer value"
        value.move< unsigned int > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  ConfigParser::stack_symbol_type&
  ConfigParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 141: // channel
        value.copy< imgchannel_t > (that.value);
        break;

      case 143: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 142: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 112: // "floating point value"
      case 144: // number
        value.copy< float > (that.value);
        break;

      case 111: // "integer value"
      case 145: // integer
        value.copy< int > (that.value);
        break;

      case 138: // element
        value.copy< metal_t > (that.value);
        break;

      case 113: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 110: // "positive integer value"
        value.copy< unsigned int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  ConfigParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  ConfigParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  ConfigParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  ConfigParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  ConfigParser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ConfigParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ConfigParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ConfigParser::debug_level_type
  ConfigParser::debug_level () const
  {
    return yydebug_;
  }

  void
  ConfigParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  ConfigParser::state_type
  ConfigParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  ConfigParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  ConfigParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ConfigParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
    #line 22 "config_parser.y" // lalr1.cc:750
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 524 "config_parser.tab.cc" // lalr1.cc:750

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 141: // channel
        yylhs.value.build< imgchannel_t > ();
        break;

      case 143: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 142: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 112: // "floating point value"
      case 144: // number
        yylhs.value.build< float > ();
        break;

      case 111: // "integer value"
      case 145: // integer
        yylhs.value.build< int > ();
        break;

      case 138: // element
        yylhs.value.build< metal_t > ();
        break;

      case 113: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 110: // "positive integer value"
        yylhs.value.build< unsigned int > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 4:
#line 165 "config_parser.y" // lalr1.cc:870
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 674 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 7:
#line 168 "config_parser.y" // lalr1.cc:870
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 680 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 8:
#line 169 "config_parser.y" // lalr1.cc:870
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 686 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 9:
#line 170 "config_parser.y" // lalr1.cc:870
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 692 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 10:
#line 171 "config_parser.y" // lalr1.cc:870
    {/* path_trace is the only available and dflt */}
#line 698 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 11:
#line 172 "config_parser.y" // lalr1.cc:870
    {/* camera depends on resolution */}
#line 704 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 12:
#line 173 "config_parser.y" // lalr1.cc:870
    {driver.deferred_shapes.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 710 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 13:
#line 174 "config_parser.y" // lalr1.cc:870
    {driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 716 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 14:
#line 175 "config_parser.y" // lalr1.cc:870
    {driver.deferred_lights.push_back(driver.cur_light);driver.cur_light=ParsedLight();}
#line 722 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 16:
#line 177 "config_parser.y" // lalr1.cc:870
    {driver.children.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 728 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 17:
#line 178 "config_parser.y" // lalr1.cc:870
    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
#line 734 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 18:
#line 179 "config_parser.y" // lalr1.cc:870
    {driver.deferred_dualmats.push_back(driver.cur_dualmat);driver.cur_dualmat = ParsedDualMaterial();}
#line 740 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 22:
#line 185 "config_parser.y" // lalr1.cc:870
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 746 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 23:
#line 186 "config_parser.y" // lalr1.cc:870
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 752 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 27:
#line 192 "config_parser.y" // lalr1.cc:870
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 758 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 28:
#line 193 "config_parser.y" // lalr1.cc:870
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 764 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 29:
#line 194 "config_parser.y" // lalr1.cc:870
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 770 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 30:
#line 195 "config_parser.y" // lalr1.cc:870
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 776 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 31:
#line 196 "config_parser.y" // lalr1.cc:870
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 782 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 32:
#line 197 "config_parser.y" // lalr1.cc:870
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 788 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 33:
#line 198 "config_parser.y" // lalr1.cc:870
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 794 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 34:
#line 199 "config_parser.y" // lalr1.cc:870
    {driver.tex_filter = UNFILTERED;}
#line 800 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 35:
#line 200 "config_parser.y" // lalr1.cc:870
    {driver.tex_filter = TRILINEAR;}
#line 806 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 36:
#line 201 "config_parser.y" // lalr1.cc:870
    {driver.tex_filter = EWA;}
#line 812 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 40:
#line 207 "config_parser.y" // lalr1.cc:870
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 818 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 41:
#line 208 "config_parser.y" // lalr1.cc:870
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 824 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 42:
#line 209 "config_parser.y" // lalr1.cc:870
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 830 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 43:
#line 210 "config_parser.y" // lalr1.cc:870
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 836 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 44:
#line 211 "config_parser.y" // lalr1.cc:870
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 842 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 45:
#line 212 "config_parser.y" // lalr1.cc:870
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 848 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 46:
#line 213 "config_parser.y" // lalr1.cc:870
    {driver.fov = yystack_[0].value.as< float > ();}
#line 854 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 52:
#line 219 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 860 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 53:
#line 221 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.position = yystack_[0].value.as< Vec3 > ();}
#line 866 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 54:
#line 222 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.rotation = yystack_[0].value.as< Vec3 > ();}
#line 872 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 55:
#line 223 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.scale = yystack_[0].value.as< Vec3 > ();}
#line 878 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 56:
#line 224 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.scale = yystack_[0].value.as< float > ();}
#line 884 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 57:
#line 225 "config_parser.y" // lalr1.cc:870
    {driver.cur_mesh.material_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 890 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 58:
#line 226 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_tex = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2); driver.cur_mesh.mask = driver.cur_mask;driver.cur_mask = ParsedMask();}
#line 896 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 59:
#line 227 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_tex = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.cur_mesh.mask = driver.cur_mask;driver.cur_mask = ParsedMask();}
#line 902 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 63:
#line 233 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 908 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 64:
#line 234 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.temperature = yystack_[0].value.as< unsigned int > ();}
#line 914 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 65:
#line 235 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.color = yystack_[0].value.as< Vec3 > ();}
#line 920 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 66:
#line 236 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.type = AREA;}
#line 926 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 67:
#line 237 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.type = OMNI;}
#line 932 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 68:
#line 238 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.type = SPOT;}
#line 938 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 69:
#line 239 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.position = yystack_[0].value.as< Vec3 > ();}
#line 944 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 70:
#line 240 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.rotation = yystack_[0].value.as< Vec3 > ();}
#line 950 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 71:
#line 241 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.scale = yystack_[0].value.as< Vec3 > ();}
#line 956 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 72:
#line 242 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.scale = yystack_[0].value.as< float > ();}
#line 962 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 73:
#line 243 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.radius = yystack_[0].value.as< float > ();}
#line 968 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 74:
#line 244 "config_parser.y" // lalr1.cc:870
    {driver.cur_light.falloff = yystack_[0].value.as< float > ();}
#line 974 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 76:
#line 249 "config_parser.y" // lalr1.cc:870
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 980 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 77:
#line 250 "config_parser.y" // lalr1.cc:870
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 986 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 78:
#line 251 "config_parser.y" // lalr1.cc:870
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 992 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 79:
#line 252 "config_parser.y" // lalr1.cc:870
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 998 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 82:
#line 257 "config_parser.y" // lalr1.cc:870
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1004 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 83:
#line 258 "config_parser.y" // lalr1.cc:870
    {driver.tex_scale = yystack_[0].value.as< Vec2 > ();}
#line 1010 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 84:
#line 259 "config_parser.y" // lalr1.cc:870
    {driver.tex_scale = Vec2(yystack_[0].value.as< float > ());}
#line 1016 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 85:
#line 260 "config_parser.y" // lalr1.cc:870
    {driver.tex_shift = yystack_[0].value.as< Vec2 > ();}
#line 1022 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 87:
#line 266 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1028 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 88:
#line 267 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1034 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 89:
#line 268 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1040 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 90:
#line 269 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1046 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 93:
#line 274 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.type = MATTE;}
#line 1052 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 94:
#line 275 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.type = GLOSSY;}
#line 1058 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 95:
#line 276 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.type = METAL;}
#line 1064 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 96:
#line 277 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.type = GLASS;}
#line 1070 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 97:
#line 278 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0);}
#line 1076 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 98:
#line 279 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}
#line 1082 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 99:
#line 280 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 1088 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 100:
#line 281 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 1094 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 101:
#line 282 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}
#line 1100 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 102:
#line 283 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}
#line 1106 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 103:
#line 284 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
#line 1112 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 104:
#line 285 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
#line 1118 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 105:
#line 286 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
#line 1124 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 106:
#line 287 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1130 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 107:
#line 288 "config_parser.y" // lalr1.cc:870
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.diffuse_uniform = driver.load_texture_uniform();}
#line 1136 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 108:
#line 289 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1142 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 109:
#line 290 "config_parser.y" // lalr1.cc:870
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.specular_uniform = driver.load_texture_uniform();}
#line 1148 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 110:
#line 292 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.bump = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2); /* driver.cur_mat.bump_is_normal = true; */}
#line 1154 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 111:
#line 293 "config_parser.y" // lalr1.cc:870
    {driver.cur_mat.elem = yystack_[0].value.as< metal_t > ();}
#line 1160 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 113:
#line 298 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1166 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 114:
#line 299 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1172 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 115:
#line 300 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1178 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 116:
#line 301 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1184 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 119:
#line 306 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.first = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1190 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 120:
#line 307 "config_parser.y" // lalr1.cc:870
    {driver.cur_dualmat.second = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1196 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 121:
#line 308 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_tex = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.cur_dualmat.mask = driver.cur_mask; driver.cur_mask = ParsedMask();}
#line 1202 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 122:
#line 309 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_tex = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.cur_dualmat.mask = driver.cur_mask; driver.cur_mask = ParsedMask();}
#line 1208 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 124:
#line 317 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_SILVER; }
#line 1214 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 125:
#line 318 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_ALUMINIUM; }
#line 1220 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 126:
#line 319 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_GOLD; }
#line 1226 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 127:
#line 320 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_COPPER; }
#line 1232 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 128:
#line 321 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_IRON; }
#line 1238 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 129:
#line 322 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_MERCURY; }
#line 1244 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 130:
#line 323 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_LEAD; }
#line 1250 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 131:
#line 324 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_PLATINUM; }
#line 1256 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 132:
#line 325 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_TUNGSTEN; }
#line 1262 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 133:
#line 326 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_BERYLLIUM; }
#line 1268 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 134:
#line 327 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_BISMUTH; }
#line 1274 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 135:
#line 328 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_COBALT; }
#line 1280 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 136:
#line 329 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_CHROMIUM; }
#line 1286 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 137:
#line 330 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_GERMANIUM; }
#line 1292 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 138:
#line 331 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_POTASSIUM; }
#line 1298 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 139:
#line 332 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_LITHIUM; }
#line 1304 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 140:
#line 333 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_MAGNESIUM; }
#line 1310 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 141:
#line 334 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_MANGANESE; }
#line 1316 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 142:
#line 335 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_MOLYBDENUM; }
#line 1322 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 143:
#line 336 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_SODIUM; }
#line 1328 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 144:
#line 337 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_NIOBIUM; }
#line 1334 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 145:
#line 338 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_NICKEL; }
#line 1340 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 146:
#line 339 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_PALLADIUM; }
#line 1346 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 147:
#line 340 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_RHODIUM; }
#line 1352 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 148:
#line 341 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_TANTALUM; }
#line 1358 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 149:
#line 342 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_TITANIUM; }
#line 1364 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 150:
#line 343 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_VANADIUM; }
#line 1370 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 151:
#line 344 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_ZINC; }
#line 1376 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 152:
#line 345 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< metal_t > () = METAL_ZIRCONIUM; }
#line 1382 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 155:
#line 351 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_chn = yystack_[0].value.as< imgchannel_t > ();}
#line 1388 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 156:
#line 352 "config_parser.y" // lalr1.cc:870
    {driver.cur_mask.mask_inv = true;}
#line 1394 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 157:
#line 356 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< imgchannel_t > () = RED;}
#line 1400 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 158:
#line 357 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< imgchannel_t > () = GREEN;}
#line 1406 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 159:
#line 358 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< imgchannel_t > () = BLUE;}
#line 1412 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 160:
#line 359 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< imgchannel_t > () = ALPHA;}
#line 1418 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 161:
#line 364 "config_parser.y" // lalr1.cc:870
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1424 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 162:
#line 368 "config_parser.y" // lalr1.cc:870
    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1430 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 163:
#line 372 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 1436 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 164:
#line 373 "config_parser.y" // lalr1.cc:870
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 1442 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 165:
#line 377 "config_parser.y" // lalr1.cc:870
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 1448 "config_parser.tab.cc" // lalr1.cc:870
    break;

  case 166:
#line 378 "config_parser.y" // lalr1.cc:870
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 1454 "config_parser.tab.cc" // lalr1.cc:870
    break;


#line 1458 "config_parser.tab.cc" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  ConfigParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  ConfigParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short ConfigParser::yypact_ninf_ = -273;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short
  ConfigParser::yypact_[] =
  {
     228,  -273,    18,    24,    28,    40,    48,    50,    55,    57,
      64,    67,    93,    97,   105,   211,  -273,   -25,    59,   121,
     -11,    33,   138,   146,    46,   156,   157,     3,   168,   169,
    -273,  -273,  -273,  -273,   141,  -273,  -273,  -273,   237,   239,
    -273,   117,    30,    84,  -273,    12,     4,  -273,   180,   181,
      49,  -273,  -273,   185,   186,   190,   197,   216,  -273,  -273,
     199,   202,   208,   210,   215,    87,  -273,   225,   223,    85,
    -273,   229,   231,   232,   238,   245,   252,   254,   266,   318,
      22,  -273,  -273,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   224,   123,  -273,  -273,   329,   330,   331,
     332,   233,    17,  -273,  -273,   333,   334,   335,   336,   337,
      91,  -273,   234,   236,  -273,  -273,   250,    70,    70,   164,
    -273,  -273,   251,   338,   338,   338,    70,  -273,  -273,   235,
    -273,  -273,   343,   345,   346,   347,   348,    85,  -273,   206,
     338,   243,   241,   338,     7,   338,   230,   244,  -273,  -273,
     111,   242,    70,     1,    99,   207,    10,    70,     2,   246,
    -273,   353,  -273,   247,   248,   253,   255,  -273,   354,  -273,
     256,    13,   357,   257,  -273,   359,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,    70,  -273,  -273,  -273,
    -273,  -273,   338,   338,     7,   258,   259,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,   153,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,    70,   338,  -273,  -273,  -273,  -273,  -273,  -273,   260,
       5,   249,  -273,  -273,   261,  -273,    70,  -273,  -273,  -273,
     122,   262,   355,  -273,  -273,  -273,  -273,  -273,   249,   153,
     356,  -273,   153,     5,  -273,  -273,  -273,  -273,  -273,   249,
    -273,  -273,     5,   358,   122,   122,    70,   249,    70,   153,
    -273,     5,    70,   122,   367,    37,   371,    70,  -273,   372,
    -273
  };

  const unsigned char
  ConfigParser::yydefact_[] =
  {
       0,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     4,    10,     0,     7,     8,     9,     0,     0,
      12,     0,     0,     0,    16,     0,     0,    24,     0,     0,
       0,    21,    37,     0,     0,     0,     0,     0,    26,    47,
       0,     0,     0,     0,     0,     0,    39,     0,     0,    49,
      75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,   123,     0,     0,     0,
       0,     0,     0,   118,    86,     0,     0,     0,     0,     0,
       0,    81,     0,     0,     5,    20,     0,     0,     0,     0,
       6,    25,     0,     0,     0,     0,     0,    11,    38,     0,
      13,    60,     0,     0,     0,     0,     0,    48,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    91,     0,     0,     0,     0,    18,     0,   117,
       0,     0,     0,     0,    15,     0,    80,    22,    23,    27,
      28,    29,    30,    31,   165,   166,   163,    32,   164,    33,
      34,    35,    36,    40,    41,    42,     0,    43,    44,    45,
      46,    52,     0,     0,     0,     0,     0,    50,    67,    68,
      66,    69,    64,    63,    70,    71,    72,    65,    73,    74,
      96,    94,    93,    95,    90,   102,   106,   107,   104,   103,
     105,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     111,     0,    99,    98,    97,   101,   108,   109,   110,     0,
     116,   121,   119,   120,     0,    82,     0,    83,    84,    85,
      76,     0,     0,    53,    54,    55,    56,    57,    58,    87,
       0,   100,    88,   113,   157,   158,   159,   160,   156,   122,
     154,   155,   114,     0,    77,    78,     0,    59,     0,    89,
     153,   115,     0,    79,     0,     0,     0,     0,   162,     0,
     161
  };

  const short
  ConfigParser::yypgoto_[] =
  {
    -273,  -273,   364,  -273,   291,  -273,   339,  -273,   315,  -273,
    -273,  -273,   263,  -273,   301,  -273,  -271,  -108,  -273,  -216,
     -94,  -273,  -251,  -101,  -273,    94,  -272,  -273,  -120,   -68,
    -115,  -273
  };

  const short
  ConfigParser::yydefgoto_[] =
  {
      -1,    15,    16,    50,    51,    57,    58,    65,    66,    68,
     137,    69,   138,    80,    81,   109,   110,   111,    93,    94,
      95,   101,   102,   103,   260,   299,   300,   301,   197,   263,
     187,   188
  };

  const unsigned short
  ConfigParser::yytable_[] =
  {
     162,   169,   176,   189,   198,   199,   196,   196,   289,   304,
      43,   200,   196,   104,    96,   261,    35,    36,   276,   293,
     211,    96,    17,   214,   215,   217,    96,   310,    18,   216,
     148,    70,    19,   227,   313,   310,   262,   225,   267,    70,
      71,   264,   265,   318,    20,    72,   317,   105,    71,   106,
     107,   311,    21,    72,    22,    97,   278,   114,    47,    23,
     168,    24,    48,    49,    73,    74,    75,    76,    25,    77,
     108,    26,    73,    74,    75,    76,   309,    77,    98,    99,
     100,   282,   283,   284,   285,    98,    99,   100,    32,   286,
      98,    99,   100,    82,   131,   127,    59,    27,    78,    79,
     104,    28,    83,   277,   279,    60,    78,    79,   132,    29,
      61,    62,    63,    64,   226,   266,    44,   184,   185,   186,
     184,   185,   186,   184,   185,   186,    33,    84,    34,   133,
     134,   104,    82,   135,   105,    85,   106,   107,    86,    87,
      88,    83,   291,    37,    89,    38,   290,    90,    91,    92,
      47,   228,   229,    39,    48,    49,   230,   175,   136,    40,
      67,   303,    82,    41,    42,   105,   161,   106,   107,   220,
     221,    83,   222,   223,    85,    45,    46,    86,    87,    88,
     184,   185,   186,    89,   112,   113,    90,    91,    92,   116,
     117,   314,   169,   315,   118,   162,   176,   316,   190,   191,
     192,   119,   319,   122,    85,   176,   123,    86,    87,    88,
     169,    30,   124,    89,   125,   162,    90,    91,    92,   126,
       1,     2,     3,     4,   120,    52,     5,     6,     7,   129,
       8,   130,   160,   139,    53,   140,   141,     1,     2,     3,
       4,   167,   142,     5,     6,     7,    52,     8,    59,   143,
       9,    10,    11,    54,    55,    53,   144,    60,   145,    12,
      13,    14,    61,    62,    63,    64,    56,     9,    10,    11,
     146,   193,   194,   195,    54,    55,    12,    13,    14,   179,
     180,   181,   182,   183,   208,   209,   210,    56,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   294,   295,   296,
     297,   298,   147,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   163,   164,   165,   166,   170,   171,   172,
     173,   115,   218,   196,   177,   174,   178,   202,   201,   203,
     204,   205,   206,   212,   213,   224,   219,   269,   274,   268,
     270,   271,   276,   281,   306,   308,   272,   312,   273,   275,
     280,   287,   288,   292,   302,   305,   317,   318,   320,    31,
     128,   149,   307,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,     0,     0,     0,
     207
  };

  const short
  ConfigParser::yycheck_[] =
  {
      94,   102,   110,   118,   124,   125,     5,     5,   224,   280,
       7,   126,     5,     9,     9,     5,    27,    28,     5,   270,
     140,     9,     4,   143,   144,   145,     9,   299,     4,   144,
       8,     9,     4,   153,   305,   307,   156,   152,   158,     9,
      18,   156,   157,     6,     4,    23,     9,    43,    18,    45,
      46,   302,     4,    23,     4,    43,   171,     8,     9,     4,
      43,     4,    13,    14,    42,    43,    44,    45,     4,    47,
      66,     4,    42,    43,    44,    45,   292,    47,    73,    74,
      75,   196,   202,   203,   204,    73,    74,    75,   113,   204,
      73,    74,    75,     9,     9,     8,     9,     4,    76,    77,
       9,     4,    18,   171,   172,    18,    76,    77,    23,     4,
      23,    24,    25,    26,   113,   113,   113,   110,   111,   112,
     110,   111,   112,   110,   111,   112,    67,    43,     7,    44,
      45,     9,     9,    48,    43,    51,    45,    46,    54,    55,
      56,    18,   262,   110,    60,     7,   261,    63,    64,    65,
       9,    52,    53,     7,    13,    14,    57,    66,    73,   113,
      43,   276,     9,     7,     7,    43,    43,    45,    46,    58,
      59,    18,    61,    62,    51,     7,     7,    54,    55,    56,
     110,   111,   112,    60,     4,     4,    63,    64,    65,     4,
       4,   306,   293,   308,     4,   289,   304,   312,    34,    35,
      36,     4,   317,     4,    51,   313,     4,    54,    55,    56,
     311,     0,     4,    60,     4,   309,    63,    64,    65,     4,
       9,    10,    11,    12,     8,     9,    15,    16,    17,     4,
      19,     8,     8,     4,    18,     4,     4,     9,    10,    11,
      12,     8,     4,    15,    16,    17,     9,    19,     9,     4,
      39,    40,    41,    37,    38,    18,     4,    18,     4,    48,
      49,    50,    23,    24,    25,    26,    50,    39,    40,    41,
       4,    20,    21,    22,    37,    38,    48,    49,    50,    29,
      30,    31,    32,    33,    78,    79,    80,    50,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    68,    69,    70,
      71,    72,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    50,   112,     5,   110,     8,   110,     4,   113,     4,
       4,     4,     4,   110,   113,   113,   112,     4,     4,   113,
     113,   113,     5,     4,     9,     9,   113,     9,   113,   113,
     113,   113,   113,   113,   113,   113,     9,     6,     6,    15,
      65,    80,   288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
     137
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,    50,   115,   116,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       0,   116,   113,    67,     7,    27,    28,   110,     7,     7,
     113,     7,     7,     7,   113,     7,     7,     9,    13,    14,
     117,   118,     9,    18,    37,    38,    50,   119,   120,     9,
      18,    23,    24,    25,    26,   121,   122,    43,   123,   125,
       9,    18,    23,    42,    43,    44,    45,    47,    76,    77,
     127,   128,     9,    18,    43,    51,    54,    55,    56,    60,
      63,    64,    65,   132,   133,   134,     9,    43,    73,    74,
      75,   135,   136,   137,     9,    43,    45,    46,    66,   129,
     130,   131,     4,     4,     8,   118,     4,     4,     4,     4,
       8,   120,     4,     4,     4,     4,     4,     8,   122,     4,
       8,     9,    23,    44,    45,    48,    73,   124,   126,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     8,   128,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       8,    43,   134,     4,     4,     4,     4,     8,    43,   137,
       4,     4,     4,     4,     8,    66,   131,   110,   110,    29,
      30,    31,    32,    33,   110,   111,   112,   144,   145,   144,
      34,    35,    36,    20,    21,    22,     5,   142,   142,   142,
     144,   113,     4,     4,     4,     4,     4,   126,    78,    79,
      80,   142,   110,   113,   142,   142,   144,   142,   112,   112,
      58,    59,    61,    62,   113,   144,   113,   142,    52,    53,
      57,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     138,     5,   142,   143,   144,   144,   113,   142,   113,     4,
     113,   113,   113,   113,     4,   113,     5,   143,   144,   143,
     113,     4,   144,   142,   142,   142,   144,   113,   113,   133,
     144,   142,   113,   136,    68,    69,    70,    71,    72,   139,
     140,   141,   113,   144,   130,   113,     9,   139,     9,   133,
     140,   136,     9,   130,   144,   144,   144,     9,     6,   144,
       6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   129,   129,   129,   129,
     130,   130,   131,   131,   131,   131,   131,   132,   132,   132,
     132,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   135,   135,   136,   136,   137,
     137,   137,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   140,   140,   141,   141,   141,
     141,   142,   143,   144,   144,   145,   145
  };

  const unsigned char
  ConfigParser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     5,     3,     5,     5,     1,
       2,     1,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     1,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     4,
       1,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     4,     4,     5,
       2,     1,     3,     3,     3,     3,     1,     4,     4,     5,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     4,     4,     5,     3,     2,     1,     3,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     7,     5,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ConfigParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"invalid character\"",
  "\":\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\",\"",
  "\"`out` keywork\"", "\"`integrator` keyword\"",
  "\"`resolution` keyword\"", "\"`width` keyword\"",
  "\"`height` keyword\"", "\"``sampler` keyword\"", "\"`spp` keyword\"",
  "\"`filter` keyword\"", "\"`type` keyword\"", "\"`camera` keyword\"",
  "\"`orthographic` keyword\"", "\"`perspective` keyword\"",
  "\"`panorama` keyword\"", "\"`position` keyword\"",
  "\"`target` keyword\"", "\"`up` keyword\"", "\"`fov` keyword\"",
  "\"`random` keyword\"", "\"`stratified` keyword\"", "\"`box` keyword\"",
  "\"`tent` keyword\"", "\"`gauss` keyword\"", "\"`mitchell` keyword\"",
  "\"`lanczos` keyword\"", "\"`unfiltered` keyword\"",
  "\"`trilinear` keyword\"", "\"`ewa` keyword\"", "\"`value0` keyword\"",
  "\"`value1` keyword\"", "\"`shape` keyword\"", "\"`world` keyword\"",
  "\"`light` keyword\"", "\"`temperature` keyword\"", "\"`name` keyword\"",
  "\"`rotation` keyword\"", "\"`scale` keyword\"", "\"`shift` keyword\"",
  "\"`color` keyword\"", "\"`material` keyword\"",
  "\"`dualmaterial` keyword\"", "\"`texture` keyword\"",
  "\"`anisotropy` keyword\"", "\"`beckmann` keyword\"",
  "\"`blinn` keyword\"", "\"`diffuse` keyword\"",
  "\"`distribution` keyword\"", "\"`element` keyword\"",
  "\"`ggx` keyword\"", "\"`glass` keyword\"", "\"`glossy` keyword\"",
  "\"`ior` keyword\"", "\"`matte` keyword\"", "\"`metal keyword\"",
  "\"`roughness` keyword\"", "\"`specular` keyword\"",
  "\"`normal` keyword\"", "\"`src` keyword\"", "\"`path` keyword\"",
  "\"Red channel attribute\"", "\"Green channel attribute\"",
  "\"Blue channel attribute\"", "\"Alpha channel attribute\"",
  "\"inverted attribute\"", "\"`mask` keyword\"", "\"`first` keyword\"",
  "\"`second` keyword\"", "\"`radius` keyword\"", "\"`falloff` keyword\"",
  "\"`omni` keyword\"", "\"`spot` keyword\"", "\"`area` keyword\"",
  "\"`Ag`\"", "\"`Al`\"", "\"`Au`\"", "\"`Cu`\"", "\"`Fe`\"", "\"`Hg`\"",
  "\"`Pb`\"", "\"`Pt`\"", "\"`W`\"", "\"`Be`\"", "\"`Bi`\"", "\"`Co`\"",
  "\"`Cr`\"", "\"`Ge`\"", "\"`K`\"", "\"`Li`\"", "\"`Mg`\"", "\"`Mn`\"",
  "\"`Mo`\"", "\"`Na`\"", "\"`Nb`\"", "\"`Ni`\"", "\"`Pd`\"", "\"`Rh`\"",
  "\"`Ta`\"", "\"`Ti`\"", "\"`V`\"", "\"`Zn`\"", "\"`Zr`\"",
  "\"positive integer value\"", "\"integer value\"",
  "\"floating point value\"", "\"quoted string\"", "$accept", "file",
  "stmt", "resolution_obj", "resolution_stmt", "filter_obj", "filter_stmt",
  "camera_obj", "camera_stmt", "world_obj", "world_rec", "world_name",
  "world_stmt", "light_obj", "light_stmt", "texture_obj", "texture_rec",
  "texture_stmt", "material_obj", "material_rec", "material_stmt",
  "dualmaterial_obj", "dualmaterial_rec", "dualmaterial_stmt", "element",
  "attributes", "attribute", "channel", "vector", "vector2", "number",
  "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  ConfigParser::yyrline_[] =
  {
       0,   160,   160,   161,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     183,   183,   185,   186,   187,   190,   190,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   205,   205,
     207,   208,   209,   210,   211,   212,   213,   214,   217,   217,
     218,   218,   219,   221,   222,   223,   224,   225,   226,   227,
     228,   231,   231,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   249,   250,   251,   252,
     255,   255,   257,   258,   259,   260,   261,   266,   267,   268,
     269,   272,   272,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     292,   293,   294,   298,   299,   300,   301,   304,   304,   306,
     307,   308,   309,   310,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   348,   348,   351,   352,   356,   357,   358,
     359,   363,   368,   372,   373,   377,   378
  };

  // Print the state stack on the debug stream.
  void
  ConfigParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ConfigParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2096 "config_parser.tab.cc" // lalr1.cc:1181
#line 381 "config_parser.y" // lalr1.cc:1182


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
