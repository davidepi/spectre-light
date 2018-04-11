// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

#line 37 "config_parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "config_parser.tab.hh"

// User implementation prologue.

#line 51 "config_parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 26 "config_parser.y" // lalr1.cc:413
 
    #include "parsers/config_driver.hpp"

#line 57 "config_parser.tab.cc" // lalr1.cc:413


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
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "config_parser.tab.cc" // lalr1.cc:479

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
  inline
  ConfigParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  ConfigParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ConfigParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  ConfigParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  ConfigParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ConfigParser::symbol_number_type
  ConfigParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  ConfigParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ConfigParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 89: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 88: // vector
        value.move< Vec3 > (that.value);
        break;

      case 64: // "floating point value"
      case 90: // number
        value.move< float > (that.value);
        break;

      case 63: // "integer value"
      case 91: // integer
        value.move< int > (that.value);
        break;

      case 65: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 62: // "positive integer value"
        value.move< unsigned int > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  ConfigParser::stack_symbol_type&
  ConfigParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 89: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 88: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 64: // "floating point value"
      case 90: // number
        value.copy< float > (that.value);
        break;

      case 63: // "integer value"
      case 91: // integer
        value.copy< int > (that.value);
        break;

      case 65: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 62: // "positive integer value"
        value.copy< unsigned int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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

  inline
  void
  ConfigParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ConfigParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ConfigParser::yypop_ (unsigned int n)
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

  inline ConfigParser::state_type
  ConfigParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ConfigParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 20 "config_parser.y" // lalr1.cc:745
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 468 "config_parser.tab.cc" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

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
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 89: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 88: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 64: // "floating point value"
      case 90: // number
        yylhs.value.build< float > ();
        break;

      case 63: // "integer value"
      case 91: // integer
        yylhs.value.build< int > ();
        break;

      case 65: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 62: // "positive integer value"
        yylhs.value.build< unsigned int > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 4:
#line 112 "config_parser.y" // lalr1.cc:859
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 604 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 114 "config_parser.y" // lalr1.cc:859
    {driver.build_filter();}
#line 610 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 115 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 616 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 116 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 622 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 117 "config_parser.y" // lalr1.cc:859
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 628 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 118 "config_parser.y" // lalr1.cc:859
    {/* path_trace is the only available and dflt */}
#line 634 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 119 "config_parser.y" // lalr1.cc:859
    {/* camera depends on resolution */}
#line 640 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 123 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_folder();}
#line 646 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 125 "config_parser.y" // lalr1.cc:859
    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
#line 652 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 131 "config_parser.y" // lalr1.cc:859
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 658 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 132 "config_parser.y" // lalr1.cc:859
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 664 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 138 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 670 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 139 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 676 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 140 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 682 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 141 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 688 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 142 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 694 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 143 "config_parser.y" // lalr1.cc:859
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 700 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 144 "config_parser.y" // lalr1.cc:859
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 706 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 150 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 712 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 151 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 718 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 152 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 724 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 153 "config_parser.y" // lalr1.cc:859
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 730 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 154 "config_parser.y" // lalr1.cc:859
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 736 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 155 "config_parser.y" // lalr1.cc:859
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 742 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 156 "config_parser.y" // lalr1.cc:859
    {driver.fov = yystack_[0].value.as< float > ();}
#line 748 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 176 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 754 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 177 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 760 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 178 "config_parser.y" // lalr1.cc:859
    {driver.tex_src = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 766 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 179 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[1].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 772 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 180 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[0].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 778 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 181 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[0].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 784 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 186 "config_parser.y" // lalr1.cc:859
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 790 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 192 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ();}
#line 796 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 193 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ();}
#line 802 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 198 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = MATTE;}
#line 808 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 199 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLOSSY;}
#line 814 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 200 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = METAL;}
#line 820 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 201 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLASS;}
#line 826 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 202 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0,0);}
#line 832 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 203 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}
#line 838 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 204 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 844 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 205 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}
#line 850 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 206 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}
#line 856 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 207 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
#line 862 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 208 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
#line 868 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 209 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
#line 874 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 210 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ();}
#line 880 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 211 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ();}
#line 886 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 212 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.elem[0]=yystack_[0].value.as< std::string > ()[0];driver.cur_mat.elem[1]=yystack_[0].value.as< std::string > ()[1];}
#line 892 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 218 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 898 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 222 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 904 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 226 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 910 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 227 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 916 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 231 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 922 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 232 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 928 "config_parser.tab.cc" // lalr1.cc:859
    break;


#line 932 "config_parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  ConfigParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short int ConfigParser::yypact_ninf_ = -151;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
     154,  -151,    20,    27,    65,    67,    75,    78,    88,    94,
      99,   108,   110,   112,   143,  -151,   -56,   -44,    35,    83,
      -7,    87,   115,    79,   138,   140,   141,     3,  -151,  -151,
    -151,  -151,     7,  -151,  -151,  -151,    90,   159,  -151,   111,
     111,    38,    -2,  -151,  -151,   152,   153,   125,  -151,  -151,
     157,   163,   168,    72,  -151,  -151,   170,   171,   172,   174,
     182,     4,  -151,   185,   192,     2,   -20,   193,  -151,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,    77,
    -151,  -151,   208,   209,   210,   211,     6,  -151,   149,   155,
    -151,  -151,   164,    13,    13,  -151,  -151,   109,   213,   213,
     213,    13,  -151,  -151,   151,  -151,  -151,   216,   217,   218,
       9,  -151,   219,   220,    31,  -151,  -151,    48,   160,   162,
     165,   -13,   166,     0,   169,   167,  -151,   223,  -151,   173,
     213,   175,  -151,   224,   225,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,    13,  -151,  -151,  -151,  -151,  -151,   213,   213,
       1,   230,  -151,   177,   213,  -151,  -151,  -151,  -151,  -151,
    -151,    91,  -151,  -151,  -151,  -151,  -151,  -151,    13,  -151,
     213,  -151,  -151,  -151,   176,  -151,     5,     5,   213,   178,
     226,  -151,  -151,  -151,  -151,   179,  -151,  -151,    91,   227,
    -151,  -151,     5,     5,  -151,  -151,    13,  -151,    13,   228,
      51,    13,  -151,   236,  -151
  };

  const unsigned char
  ConfigParser::yydefact_[] =
  {
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       4,    10,     0,     7,     8,     9,     0,     0,    12,     0,
       0,     0,     0,    15,    23,     0,     0,     0,    20,    33,
       0,     0,     0,     0,    25,    43,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    69,     0,     0,     0,     0,     0,    67,     0,     0,
       5,    19,     0,     0,     0,     6,    24,     0,     0,     0,
       0,     0,    11,    34,     0,    13,    53,     0,     0,     0,
      44,    47,     0,     0,    54,    57,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    72,     0,
       0,     0,    16,     0,     0,    66,    21,    22,    26,    27,
      28,    29,    30,    94,    95,    92,    31,    93,    32,    36,
      37,    38,     0,    39,    40,    41,    42,    48,     0,     0,
       0,     0,    45,     0,     0,    55,    56,    77,    75,    74,
      76,     0,    82,    86,    84,    83,    85,    88,     0,    78,
       0,    79,    81,    87,     0,    68,    65,    62,     0,     0,
       0,    49,    50,    52,    51,     0,    58,    59,    70,     0,
      80,    71,    63,    60,    64,    61,     0,    46,     0,     0,
       0,     0,    91,     0,    90
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
    -151,  -151,   231,  -151,   212,  -151,   194,  -151,   187,  -151,
    -151,   214,   -62,  -151,  -151,   132,  -151,  -150,   -82,  -151,
      80,   -79,   -97,  -151,   -93,  -151
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    48,    53,    54,    61,    62,    64,
     110,    65,   111,    67,   114,   115,    85,    86,    87,    78,
      79,    80,   153,   181,   146,   147
  };

  const unsigned char
  ConfigParser::yytable_[] =
  {
     128,   148,   154,   155,   135,   178,   152,    81,   156,    30,
      42,   106,   102,    55,    81,    81,    44,    31,   106,   112,
      45,    46,    56,   113,    16,   107,   180,    57,    58,    59,
      60,    17,   107,   186,   174,   175,   202,   203,    82,   176,
     106,    83,    32,   108,   109,    82,    82,    68,   162,   133,
     108,   109,   165,   161,   107,    35,    69,   212,    84,   190,
     211,   191,   192,   194,   179,   193,   134,   197,    43,    18,
     112,    19,   108,   109,   113,   143,   144,   145,    70,    20,
      95,    49,    21,   200,    71,   199,    68,    72,    73,    74,
      50,   204,    22,    75,    36,    69,    76,    77,    23,    49,
      68,   167,   168,    24,   169,   170,    51,    52,    50,    69,
      33,    34,    25,   209,    26,   210,    27,   127,   213,   128,
     135,   135,    37,    71,    51,    52,    72,    73,    74,   149,
     150,   151,    75,    90,    44,    76,    77,    71,    45,    46,
      72,    73,    74,    28,    38,    39,    75,    40,    41,    76,
      77,    63,     1,     2,     3,     4,    88,    89,     5,     6,
       7,    92,     8,     1,     2,     3,     4,    93,    55,     5,
       6,     7,    94,     8,    97,    98,    99,    56,   100,     9,
      10,    11,    57,    58,    59,    60,   101,    12,    13,   104,
       9,    10,    11,   138,   139,   140,   141,   142,    12,    13,
     105,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   136,   129,   130,   131,   126,   157,   137,   152,   132,
     158,   159,   160,   163,   164,   171,   172,   184,   188,   189,
     173,   177,   183,   182,   195,   206,   208,   211,   185,   196,
     187,   201,   214,   205,   207,    29,   166,    96,   103,     0,
       0,   198,     0,     0,    66,     0,     0,     0,     0,    91
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      79,    94,    99,   100,    86,     5,     5,     9,   101,    65,
       7,     9,     8,     9,     9,     9,     9,    61,     9,    39,
      13,    14,    18,    43,     4,    23,   123,    23,    24,    25,
      26,     4,    23,   130,    47,    48,   186,   187,    40,    52,
       9,    43,     7,    41,    42,    40,    40,     9,   110,    43,
      41,    42,   114,    44,    23,    62,    18,     6,    60,   152,
       9,   158,   159,   160,    64,    64,    60,   164,    65,     4,
      39,     4,    41,    42,    43,    62,    63,    64,    40,     4,
       8,     9,     4,   180,    46,   178,     9,    49,    50,    51,
      18,   188,     4,    55,     7,    18,    58,    59,     4,     9,
       9,    53,    54,     4,    56,    57,    34,    35,    18,    18,
      27,    28,     4,   206,     4,   208,     4,    40,   211,   198,
     202,   203,     7,    46,    34,    35,    49,    50,    51,    20,
      21,    22,    55,     8,     9,    58,    59,    46,    13,    14,
      49,    50,    51,     0,    65,     7,    55,     7,     7,    58,
      59,    40,     9,    10,    11,    12,     4,     4,    15,    16,
      17,     4,    19,     9,    10,    11,    12,     4,     9,    15,
      16,    17,     4,    19,     4,     4,     4,    18,     4,    36,
      37,    38,    23,    24,    25,    26,     4,    44,    45,     4,
      36,    37,    38,    29,    30,    31,    32,    33,    44,    45,
       8,     8,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    62,     4,     4,     4,     8,    65,    62,     5,     8,
       4,     4,     4,     4,     4,    65,    64,     4,     4,     4,
      65,    65,    65,    64,     4,     9,     9,     9,    65,    62,
      65,    65,     6,    65,    65,    14,   114,    53,    61,    -1,
      -1,   171,    -1,    -1,    40,    -1,    -1,    -1,    -1,    47
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    36,
      37,    38,    44,    45,    67,    68,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     0,    68,
      65,    61,     7,    27,    28,    62,     7,     7,    65,     7,
       7,     7,     7,    65,     9,    13,    14,    69,    70,     9,
      18,    34,    35,    71,    72,     9,    18,    23,    24,    25,
      26,    73,    74,    40,    75,    77,    77,    79,     9,    18,
      40,    46,    49,    50,    51,    55,    58,    59,    85,    86,
      87,     9,    40,    43,    60,    82,    83,    84,     4,     4,
       8,    70,     4,     4,     4,     8,    72,     4,     4,     4,
       4,     4,     8,    74,     4,     8,     9,    23,    41,    42,
      76,    78,    39,    43,    80,    81,     8,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     8,    40,    87,     4,
       4,     4,     8,    43,    60,    84,    62,    62,    29,    30,
      31,    32,    33,    62,    63,    64,    90,    91,    90,    20,
      21,    22,     5,    88,    88,    88,    90,    65,     4,     4,
       4,    44,    78,     4,     4,    78,    81,    53,    54,    56,
      57,    65,    64,    65,    47,    48,    52,    65,     5,    64,
      88,    89,    64,    65,     4,    65,    88,    65,     4,     4,
      90,    88,    88,    64,    88,     4,    62,    88,    86,    90,
      88,    65,    83,    83,    88,    65,     9,    65,     9,    90,
      90,     9,     6,    90,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    70,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    76,    76,    76,    77,    78,
      78,    78,    78,    78,    79,    80,    80,    80,    81,    81,
      82,    82,    82,    82,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      88,    89,    90,    90,    91,    91
  };

  const unsigned char
  ConfigParser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     3,     5,     5,     1,     2,
       1,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     2,     4,     1,     3,     3,
       3,     3,     3,     1,     2,     2,     2,     1,     3,     3,
       4,     4,     3,     4,     4,     3,     2,     1,     3,     1,
       4,     4,     2,     1,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       7,     5,     1,     1,     1,     1
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
  "\"`lanczos` keyword\"", "\"`value0` keyword\"", "\"`value1` keyword\"",
  "\"`shape` keyword\"", "\"`world` keyword\"", "\"`light` keyword\"",
  "\"`temperature` keyword\"", "\"`name` keyword\"",
  "\"`rotation` keyword\"", "\"`scale` keyword\"", "\"`color` keyword\"",
  "\"`material` keyword\"", "\"`texture` keyword\"",
  "\"`anisotropy` keyword\"", "\"`beckmann` keyword\"",
  "\"`blinn` keyword\"", "\"`diffuse` keyword\"",
  "\"`distribution` keyword\"", "\"`element` keyword\"",
  "\"`ggx` keyword\"", "\"`glass` keyword\"", "\"`glossy` keyword\"",
  "\"`ior` keyword\"", "\"`matte` keyword\"", "\"`metal keyword\"",
  "\"`roughness` keyword\"", "\"`specular` keyword\"", "\"`src` keyword\"",
  "\"`pt` keyword\"", "\"positive integer value\"", "\"integer value\"",
  "\"floating point value\"", "\"quoted string\"", "$accept", "file",
  "stmt", "resolution_obj", "resolution_stmt", "filter_obj", "filter_stmt",
  "camera_obj", "camera_stmt", "world_obj", "world_rec", "world_name",
  "world_stmt", "light_obj", "light_rec", "light_stmt", "texture_obj",
  "texture_rec", "texture_stmt", "material_obj", "material_rec",
  "material_stmt", "vector", "vector2", "number", "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  ConfigParser::yyrline_[] =
  {
       0,   107,   107,   108,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   129,
     129,   131,   132,   133,   136,   136,   138,   139,   140,   141,
     142,   143,   144,   145,   148,   148,   150,   151,   152,   153,
     154,   155,   156,   157,   160,   161,   161,   161,   162,   164,
     165,   166,   167,   168,   171,   172,   172,   172,   173,   173,
     176,   177,   178,   179,   180,   181,   184,   184,   186,   187,
     192,   193,   196,   196,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     217,   222,   226,   227,   231,   232
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
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ConfigParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1466 "config_parser.tab.cc" // lalr1.cc:1167
#line 235 "config_parser.y" // lalr1.cc:1168


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
