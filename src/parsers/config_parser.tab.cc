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
#line 25 "config_parser.y" // lalr1.cc:413
 
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
      case 87: // vector
        value.move< Vec3 > (that.value);
        break;

      case 64: // "floating point value"
      case 88: // number
        value.move< float > (that.value);
        break;

      case 63: // "integer value"
      case 89: // integer
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
      case 87: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 64: // "floating point value"
      case 88: // number
        value.copy< float > (that.value);
        break;

      case 63: // "integer value"
      case 89: // integer
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
    #line 19 "config_parser.y" // lalr1.cc:745
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 460 "config_parser.tab.cc" // lalr1.cc:745

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
      case 87: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 64: // "floating point value"
      case 88: // number
        yylhs.value.build< float > ();
        break;

      case 63: // "integer value"
      case 89: // integer
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
#line 110 "config_parser.y" // lalr1.cc:859
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 592 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 112 "config_parser.y" // lalr1.cc:859
    {driver.build_filter();}
#line 598 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 113 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 604 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 114 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 610 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 115 "config_parser.y" // lalr1.cc:859
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 616 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 116 "config_parser.y" // lalr1.cc:859
    {/* path_trace is the only available and dflt */}
#line 622 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 117 "config_parser.y" // lalr1.cc:859
    {/* camera depends on resolution */}
#line 628 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 121 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_folder();}
#line 634 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 129 "config_parser.y" // lalr1.cc:859
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 640 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 130 "config_parser.y" // lalr1.cc:859
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 646 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 136 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 652 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 137 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 658 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 138 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 664 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 139 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 670 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 140 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 676 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 141 "config_parser.y" // lalr1.cc:859
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 682 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 142 "config_parser.y" // lalr1.cc:859
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 688 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 148 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 694 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 149 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 700 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 150 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 706 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 151 "config_parser.y" // lalr1.cc:859
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 712 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 152 "config_parser.y" // lalr1.cc:859
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 718 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 153 "config_parser.y" // lalr1.cc:859
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 724 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 154 "config_parser.y" // lalr1.cc:859
    {driver.fov = yystack_[0].value.as< float > ();}
#line 730 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 174 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 736 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 175 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 742 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 176 "config_parser.y" // lalr1.cc:859
    {driver.tex_src = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture_single();}
#line 748 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 177 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[1].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 754 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 178 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[0].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 760 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 179 "config_parser.y" // lalr1.cc:859
    {driver.tex_color=yystack_[0].value.as< Vec3 > ();driver.load_texture_uniform();}
#line 766 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 184 "config_parser.y" // lalr1.cc:859
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 772 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 211 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 778 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 215 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 784 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 216 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 790 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 220 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 796 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 221 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 802 "config_parser.tab.cc" // lalr1.cc:859
    break;


#line 806 "config_parser.tab.cc" // lalr1.cc:859
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


  const signed char ConfigParser::yypact_ninf_ = -95;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
      83,   -95,    28,    42,    48,    51,    82,    85,    87,    99,
     102,   108,   120,   125,    12,   -95,   -56,   -26,   136,    69,
      70,   143,   144,    89,   145,   155,   160,     0,   -95,   -95,
     -95,   -95,    30,   -95,   -95,   -95,   126,   150,   -95,   107,
     107,    67,    -7,   -95,   -95,   165,   166,     5,   -95,   -95,
     167,   168,   175,    96,   -95,   -95,   178,   179,   180,   181,
     182,   140,   -95,   183,   184,    17,    31,   185,   -95,   186,
     187,   190,   191,   192,   193,   194,   195,   196,    29,   -95,
     -95,   197,   198,   199,   200,    11,   -95,   127,   142,   -95,
     -95,   109,   -47,   -47,   -95,   -95,    61,   201,   201,   201,
     -47,   -95,   -95,   123,   -95,   -95,   203,   205,   206,    92,
     -95,   207,   208,   114,   -95,   -95,   124,   148,   141,    -4,
      25,   149,   151,   152,     1,   -95,   -95,   153,   201,   154,
     -95,   213,   216,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -47,   -95,   -95,   -95,   -95,   -95,   201,   201,     3,   217,
     -95,   161,   201,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,     2,     2,   201,   157,   215,   -95,   -95,   -95,
     -95,   162,   -95,   -95,     2,     2,   -95,   -95,   -47,   -95,
     219,   -47,   220,   -95
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
       0,     0,    35,     0,     0,     0,     0,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
      69,     0,     0,     0,     0,     0,    67,     0,     0,     5,
      19,     0,     0,     0,     6,    24,     0,     0,     0,     0,
       0,    11,    34,     0,    13,    53,     0,     0,     0,    44,
      47,     0,     0,    54,    57,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    70,     0,     0,     0,
      16,     0,     0,    66,    21,    22,    26,    27,    28,    29,
      30,    92,    93,    90,    31,    91,    32,    36,    37,    38,
       0,    39,    40,    41,    42,    48,     0,     0,     0,     0,
      45,     0,     0,    55,    56,    76,    74,    73,    75,    72,
      80,    85,    84,    82,    81,    83,    78,    77,    79,    87,
      86,    68,    65,    62,     0,     0,     0,    49,    50,    52,
      51,     0,    58,    59,    63,    60,    64,    61,     0,    46,
       0,     0,     0,    89
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
     -95,   -95,   211,   -95,   188,   -95,   176,   -95,   169,   -95,
     -95,   202,   -68,   -95,   -95,   118,   -95,   -37,   -85,   -95,
     156,   -94,   -90,   -95
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    48,    53,    54,    61,    62,    64,
     109,    65,   110,    67,   113,   114,    84,    85,    86,    78,
      79,   151,   144,   145
  };

  const unsigned char
  ConfigParser::yytable_[] =
  {
     133,   150,    80,   146,   152,   153,   150,    42,   150,    30,
     154,    80,    28,    89,    44,   141,   142,   143,    45,    46,
      80,     1,     2,     3,     4,   172,   105,     5,     6,     7,
     180,     8,    16,    81,   182,    31,    82,   125,    68,    44,
     106,   160,    81,    45,    46,   163,    17,    69,     9,    10,
      11,    81,    18,    83,   131,    19,    12,    13,   107,   108,
     186,   171,   187,   188,   190,    43,   179,   189,   193,    70,
     111,   132,   173,   174,   112,    71,    68,   175,    72,    73,
      74,   147,   148,   149,    75,    69,    20,    76,    77,    21,
     196,    22,     1,     2,     3,     4,    33,    34,     5,     6,
       7,   105,     8,    23,    94,    49,    24,    70,   200,   133,
     133,   202,    25,    71,    50,   106,    72,    73,    74,     9,
      10,    11,    75,   105,    26,    76,    77,    12,    13,    27,
      51,    52,    35,   107,   108,    49,   159,   106,   136,   137,
     138,   139,   140,    32,    50,   194,   195,    63,   101,    55,
      36,    37,    39,   111,    38,   107,   108,   112,    56,    55,
      51,    52,    40,    57,    58,    59,    60,    41,    56,    87,
      88,    91,    92,    57,    58,    59,    60,   165,   166,    93,
     167,   168,    96,    97,    98,    99,   100,   103,   155,   134,
     116,   117,   104,   115,   118,   119,   120,   121,   122,   123,
     124,   127,   128,   129,   135,   170,   150,   156,   130,   157,
     158,   161,   162,   169,   176,   177,   178,   184,   181,   183,
     185,   191,   197,   192,   198,    29,   203,   199,   201,    95,
     102,   164,     0,     0,   126,    90,     0,     0,     0,     0,
       0,     0,    66
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      85,     5,     9,    93,    98,    99,     5,     7,     5,    65,
     100,     9,     0,     8,     9,    62,    63,    64,    13,    14,
       9,     9,    10,    11,    12,   119,     9,    15,    16,    17,
     124,    19,     4,    40,   128,    61,    43,     8,     9,     9,
      23,   109,    40,    13,    14,   113,     4,    18,    36,    37,
      38,    40,     4,    60,    43,     4,    44,    45,    41,    42,
     150,    65,   156,   157,   158,    65,    65,    64,   162,    40,
      39,    60,    47,    48,    43,    46,     9,    52,    49,    50,
      51,    20,    21,    22,    55,    18,     4,    58,    59,     4,
     184,     4,     9,    10,    11,    12,    27,    28,    15,    16,
      17,     9,    19,     4,     8,     9,     4,    40,   198,   194,
     195,   201,     4,    46,    18,    23,    49,    50,    51,    36,
      37,    38,    55,     9,     4,    58,    59,    44,    45,     4,
      34,    35,    62,    41,    42,     9,    44,    23,    29,    30,
      31,    32,    33,     7,    18,   182,   183,    40,     8,     9,
       7,     7,     7,    39,    65,    41,    42,    43,    18,     9,
      34,    35,     7,    23,    24,    25,    26,     7,    18,     4,
       4,     4,     4,    23,    24,    25,    26,    53,    54,     4,
      56,    57,     4,     4,     4,     4,     4,     4,    65,    62,
       4,     4,     8,     8,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,    62,    64,     5,     4,     8,     4,
       4,     4,     4,    65,    65,    64,    64,     4,    65,    65,
       4,     4,    65,    62,     9,    14,     6,    65,     9,    53,
      61,   113,    -1,    -1,    78,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    40
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
       9,    40,    43,    60,    82,    83,    84,     4,     4,     8,
      70,     4,     4,     4,     8,    72,     4,     4,     4,     4,
       4,     8,    74,     4,     8,     9,    23,    41,    42,    76,
      78,    39,    43,    80,    81,     8,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     8,    86,     4,     4,     4,
       8,    43,    60,    84,    62,    62,    29,    30,    31,    32,
      33,    62,    63,    64,    88,    89,    88,    20,    21,    22,
       5,    87,    87,    87,    88,    65,     4,     4,     4,    44,
      78,     4,     4,    78,    81,    53,    54,    56,    57,    65,
      64,    65,    87,    47,    48,    52,    65,    64,    64,    65,
      87,    65,    87,    65,     4,     4,    88,    87,    87,    64,
      87,     4,    62,    87,    83,    83,    87,    65,     9,    65,
      88,     9,    88,     6
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
      85,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    87,
      88,    88,    89,    89
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
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     7,
       1,     1,     1,     1
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
  "texture_rec", "texture_stmt", "material_obj", "material_stmt", "vector",
  "number", "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  ConfigParser::yyrline_[] =
  {
       0,   105,   105,   106,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   127,
     127,   129,   130,   131,   134,   134,   136,   137,   138,   139,
     140,   141,   142,   143,   146,   146,   148,   149,   150,   151,
     152,   153,   154,   155,   158,   159,   159,   159,   160,   162,
     163,   164,   165,   166,   169,   170,   170,   170,   171,   171,
     174,   175,   176,   177,   178,   179,   182,   182,   184,   185,
     188,   188,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   210,
     215,   216,   220,   221
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
#line 1335 "config_parser.tab.cc" // lalr1.cc:1167
#line 224 "config_parser.y" // lalr1.cc:1168


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
