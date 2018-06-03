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
#line 27 "config_parser.y" // lalr1.cc:413
 
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
      case 122: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 121: // vector
        value.move< Vec3 > (that.value);
        break;

      case 96: // "floating point value"
      case 123: // number
        value.move< float > (that.value);
        break;

      case 95: // "integer value"
      case 124: // integer
        value.move< int > (that.value);
        break;

      case 120: // element
        value.move< metal_t > (that.value);
        break;

      case 97: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 94: // "positive integer value"
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
      case 122: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 121: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 96: // "floating point value"
      case 123: // number
        value.copy< float > (that.value);
        break;

      case 95: // "integer value"
      case 124: // integer
        value.copy< int > (that.value);
        break;

      case 120: // element
        value.copy< metal_t > (that.value);
        break;

      case 97: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 94: // "positive integer value"
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
    #line 21 "config_parser.y" // lalr1.cc:741
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 476 "config_parser.tab.cc" // lalr1.cc:741

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
      case 122: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 121: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 96: // "floating point value"
      case 123: // number
        yylhs.value.build< float > ();
        break;

      case 95: // "integer value"
      case 124: // integer
        yylhs.value.build< int > ();
        break;

      case 120: // element
        yylhs.value.build< metal_t > ();
        break;

      case 97: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 94: // "positive integer value"
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
#line 146 "config_parser.y" // lalr1.cc:859
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 616 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 149 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 622 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 150 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 628 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 151 "config_parser.y" // lalr1.cc:859
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 634 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 152 "config_parser.y" // lalr1.cc:859
    {/* path_trace is the only available and dflt */}
#line 640 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 153 "config_parser.y" // lalr1.cc:859
    {/* camera depends on resolution */}
#line 646 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 154 "config_parser.y" // lalr1.cc:859
    {driver.deferred_shapes.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 652 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 155 "config_parser.y" // lalr1.cc:859
    {driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 658 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 156 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.is_light=true;driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 664 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 158 "config_parser.y" // lalr1.cc:859
    {driver.children.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 670 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 159 "config_parser.y" // lalr1.cc:859
    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
#line 676 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 165 "config_parser.y" // lalr1.cc:859
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 682 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 166 "config_parser.y" // lalr1.cc:859
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 688 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 172 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 694 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 173 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 700 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 174 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 706 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 175 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 712 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 176 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 718 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 177 "config_parser.y" // lalr1.cc:859
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 724 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 178 "config_parser.y" // lalr1.cc:859
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 730 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 179 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = UNFILTERED;}
#line 736 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 180 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = TRILINEAR;}
#line 742 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 181 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = EWA;}
#line 748 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 187 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 754 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 188 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 760 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 189 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 766 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 190 "config_parser.y" // lalr1.cc:859
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 772 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 191 "config_parser.y" // lalr1.cc:859
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 778 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 192 "config_parser.y" // lalr1.cc:859
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 784 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 193 "config_parser.y" // lalr1.cc:859
    {driver.fov = yystack_[0].value.as< float > ();}
#line 790 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 199 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 796 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 201 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.position = yystack_[0].value.as< Vec3 > ();}
#line 802 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 202 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.rotation = yystack_[0].value.as< Vec3 > ();}
#line 808 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 203 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.scale = yystack_[0].value.as< Vec3 > ();}
#line 814 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 204 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.scale = yystack_[0].value.as< float > ();}
#line 820 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 205 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.material_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 826 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 212 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.temperature = yystack_[0].value.as< unsigned int > ();}
#line 832 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 213 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.color = yystack_[0].value.as< Vec3 > ();}
#line 838 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 217 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 844 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 218 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 850 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 223 "config_parser.y" // lalr1.cc:859
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 856 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 224 "config_parser.y" // lalr1.cc:859
    {driver.tex_scale = yystack_[0].value.as< Vec2 > ();}
#line 862 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 230 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 868 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 231 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 874 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 232 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 880 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 233 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 886 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 238 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = MATTE;}
#line 892 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 239 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLOSSY;}
#line 898 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 240 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = METAL;}
#line 904 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 241 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLASS;}
#line 910 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 242 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0);}
#line 916 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 243 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}
#line 922 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 244 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 928 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 245 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 934 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 246 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}
#line 940 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 247 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}
#line 946 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 248 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
#line 952 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 249 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
#line 958 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 250 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
#line 964 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 251 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 970 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 252 "config_parser.y" // lalr1.cc:859
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.diffuse_uniform = driver.load_texture_uniform();}
#line 976 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 253 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 982 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 254 "config_parser.y" // lalr1.cc:859
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.specular_uniform = driver.load_texture_uniform();}
#line 988 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 255 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.elem = yystack_[0].value.as< metal_t > ();}
#line 994 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 263 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_SILVER; }
#line 1000 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 264 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ALUMINIUM; }
#line 1006 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 265 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_GOLD; }
#line 1012 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 266 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_COPPER; }
#line 1018 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 267 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_IRON; }
#line 1024 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 268 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MERCURY; }
#line 1030 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 269 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_LEAD; }
#line 1036 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 270 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_PLATINUM; }
#line 1042 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 271 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TUNGSTEN; }
#line 1048 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 272 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_BERYLLIUM; }
#line 1054 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 273 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_BISMUTH; }
#line 1060 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 274 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_COBALT; }
#line 1066 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 275 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_CHROMIUM; }
#line 1072 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 111:
#line 276 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_GERMANIUM; }
#line 1078 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 277 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_POTASSIUM; }
#line 1084 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 278 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_LITHIUM; }
#line 1090 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 279 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MAGNESIUM; }
#line 1096 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 280 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MANGANESE; }
#line 1102 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 116:
#line 281 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MOLYBDENUM; }
#line 1108 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 282 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_SODIUM; }
#line 1114 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 283 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_NIOBIUM; }
#line 1120 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 284 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_NICKEL; }
#line 1126 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 120:
#line 285 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_PALLADIUM; }
#line 1132 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 121:
#line 286 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_RHODIUM; }
#line 1138 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 122:
#line 287 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TANTALUM; }
#line 1144 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 123:
#line 288 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TITANIUM; }
#line 1150 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 124:
#line 289 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_VANADIUM; }
#line 1156 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 125:
#line 290 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ZINC; }
#line 1162 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 126:
#line 291 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ZIRCONIUM; }
#line 1168 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 127:
#line 296 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1174 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 128:
#line 300 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1180 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 129:
#line 304 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 1186 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 130:
#line 305 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 1192 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 131:
#line 309 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 1198 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 132:
#line 310 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 1204 "config_parser.tab.cc" // lalr1.cc:859
    break;


#line 1208 "config_parser.tab.cc" // lalr1.cc:859
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


  const short int ConfigParser::yypact_ninf_ = -165;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
      98,  -165,    23,    38,    40,    42,    46,    51,    60,    67,
      71,    80,    86,    92,   169,  -165,   -83,   -39,    66,    32,
     -17,    94,    97,     9,   105,   113,     5,   117,  -165,  -165,
    -165,  -165,    21,  -165,  -165,  -165,    15,    69,  -165,    68,
      68,    27,  -165,    -2,  -165,    99,   124,   188,  -165,  -165,
     125,   132,   138,   140,    10,  -165,  -165,   143,   144,   149,
     161,   166,    14,  -165,   170,   165,    96,   148,   174,  -165,
     173,   179,   183,   185,   187,   201,   210,   211,   246,   243,
      73,  -165,  -165,   248,   249,   250,   247,     6,  -165,    39,
      57,  -165,  -165,   129,   104,   104,   177,  -165,  -165,   227,
     251,   251,   251,   104,  -165,  -165,   160,  -165,  -165,   254,
     255,   256,   257,    96,  -165,   258,   259,  -165,   148,  -165,
    -165,   147,   167,   171,     0,   -34,   153,     3,   172,     1,
    -165,   261,  -165,   175,   264,   176,  -165,   262,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   104,  -165,
    -165,  -165,  -165,  -165,   251,   251,     4,   178,  -165,   180,
     251,  -165,  -165,  -165,  -165,  -165,  -165,   114,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   104,  -165,   251,  -165,  -165,  -165,
    -165,   181,  -165,   104,  -165,    11,   182,   267,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,   114,   268,  -165,   114,   271,
      11,  -165,   104,   104,   114,   104,   272,    77,   265,   104,
    -165,   276,  -165
  };

  const unsigned char
  ConfigParser::yydefact_[] =
  {
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       4,    10,     0,     7,     8,     9,     0,     0,    12,     0,
       0,     0,    16,     0,    23,     0,     0,     0,    20,    36,
       0,     0,     0,     0,     0,    25,    46,     0,     0,     0,
       0,     0,     0,    38,     0,     0,    48,    59,     0,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    72,     0,     0,     0,     0,     0,    69,     0,
       0,     5,    19,     0,     0,     0,     0,     6,    24,     0,
       0,     0,     0,     0,    11,    37,     0,    13,    57,     0,
       0,     0,     0,    47,    50,     0,     0,    63,    58,    62,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    77,     0,     0,     0,    15,     0,    68,    21,
      22,    26,    27,    28,    29,    30,   131,   132,   129,    31,
     130,    32,    33,    34,    35,    39,    40,    41,     0,    42,
      43,    44,    45,    51,     0,     0,     0,     0,    49,     0,
       0,    60,    61,    82,    80,    79,    81,    76,    88,    92,
      93,    90,    89,    91,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    96,     0,    83,    85,    84,    87,    94,
      95,     0,    70,     0,    71,     0,     0,     0,    52,    53,
      55,    54,    56,    64,    65,    73,     0,    86,    74,     0,
      66,    67,     0,     0,    75,     0,     0,     0,     0,     0,
     128,     0,   127
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
    -165,  -165,   269,  -165,   223,  -165,   230,  -165,   224,  -165,
    -165,   245,   -56,  -165,  -165,   184,  -165,    62,   -86,  -165,
    -164,   -80,  -165,   -98,   154,   -93,  -165
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    48,    54,    55,    62,    63,    65,
     113,    66,   114,    68,   118,   119,    86,    87,    88,    79,
      80,    81,   213,   159,   217,   149,   150
  };

  const unsigned char
  ConfigParser::yytable_[] =
  {
     132,   138,   151,   160,   161,   158,   158,    82,   214,   158,
     162,   117,    41,   235,    30,    82,   181,   182,    97,    49,
      82,   183,   104,    56,    49,    31,   180,    16,    50,   216,
      44,   220,    57,    50,    45,    46,    69,    58,    59,    60,
      61,    83,    17,    84,    18,    70,    19,    51,    52,    83,
      20,    84,    51,    52,    83,    21,    84,   168,    53,    33,
      34,    85,   171,    53,    22,   227,   228,   229,   231,   137,
      71,    23,   234,    32,   244,    24,    72,    35,    56,    73,
      74,    75,    69,   250,    25,    76,   249,    57,    77,    78,
      26,    70,    58,    59,    60,    61,    27,   179,   219,   215,
     230,    36,    42,    89,    37,   108,    38,     1,     2,     3,
       4,    64,    39,     5,     6,     7,   131,     8,   237,   109,
      40,   236,    72,    69,    43,    73,    74,    75,    90,    93,
     239,    76,    70,   139,    77,    78,    94,     9,    10,    11,
     110,   111,    95,   112,    96,    12,    13,    99,   100,   246,
     247,   140,   248,   101,   138,   132,   251,   108,   141,   142,
     143,   144,   145,    72,   132,   102,    73,    74,    75,    28,
     103,   109,    76,   107,   106,    77,    78,   121,     1,     2,
       3,     4,   120,   122,     5,     6,     7,   123,     8,   124,
     115,   125,   110,   111,   116,   112,    91,    44,   146,   147,
     148,    45,    46,   173,   174,   126,   175,   176,     9,    10,
      11,   152,   153,   154,   127,   128,    12,    13,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   155,   156,   157,
     129,   130,   133,   134,   135,   136,   158,   163,   164,   165,
     166,   167,   169,   170,   177,   221,   226,   178,   218,   223,
      92,   250,   222,   225,   233,   232,   242,   243,   238,   241,
     245,   249,   252,    29,    98,    67,   105,   240,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   172
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      80,    87,    95,   101,   102,     5,     5,     9,     5,     5,
     103,    67,     7,   177,    97,     9,    50,    51,     8,     9,
       9,    55,     8,     9,     9,    64,   124,     4,    18,   127,
       9,   129,    18,    18,    13,    14,     9,    23,    24,    25,
      26,    43,     4,    45,     4,    18,     4,    37,    38,    43,
       4,    45,    37,    38,    43,     4,    45,   113,    48,    27,
      28,    63,   118,    48,     4,   158,   164,   165,   166,    63,
      43,     4,   170,     7,   238,     4,    49,    94,     9,    52,
      53,    54,     9,     6,     4,    58,     9,    18,    61,    62,
       4,    18,    23,    24,    25,    26,     4,    97,    97,    96,
      96,     7,    97,     4,     7,     9,    97,     9,    10,    11,
      12,    43,     7,    15,    16,    17,    43,    19,   216,    23,
       7,   214,    49,     9,     7,    52,    53,    54,     4,     4,
     223,    58,    18,    94,    61,    62,     4,    39,    40,    41,
      44,    45,     4,    47,     4,    47,    48,     4,     4,   242,
     243,    94,   245,     4,   240,   235,   249,     9,    29,    30,
      31,    32,    33,    49,   244,     4,    52,    53,    54,     0,
       4,    23,    58,     8,     4,    61,    62,     4,     9,    10,
      11,    12,     8,     4,    15,    16,    17,     4,    19,     4,
      42,     4,    44,    45,    46,    47,     8,     9,    94,    95,
      96,    13,    14,    56,    57,     4,    59,    60,    39,    40,
      41,    34,    35,    36,     4,     4,    47,    48,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    20,    21,    22,
       4,     8,     4,     4,     4,     8,     5,    97,     4,     4,
       4,     4,     4,     4,    97,     4,     4,    96,    96,     5,
      47,     6,    97,    97,    94,    97,     9,     9,    97,    97,
       9,     9,     6,    14,    54,    40,    62,   225,   134,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    47,    48,    99,   100,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     0,   100,
      97,    64,     7,    27,    28,    94,     7,     7,    97,     7,
       7,     7,    97,     7,     9,    13,    14,   101,   102,     9,
      18,    37,    38,    48,   103,   104,     9,    18,    23,    24,
      25,    26,   105,   106,    43,   107,   109,   109,   111,     9,
      18,    43,    49,    52,    53,    54,    58,    61,    62,   117,
     118,   119,     9,    43,    45,    63,   114,   115,   116,     4,
       4,     8,   102,     4,     4,     4,     4,     8,   104,     4,
       4,     4,     4,     4,     8,   106,     4,     8,     9,    23,
      44,    45,    47,   108,   110,    42,    46,   110,   112,   113,
       8,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       8,    43,   119,     4,     4,     4,     8,    63,   116,    94,
      94,    29,    30,    31,    32,    33,    94,    95,    96,   123,
     124,   123,    34,    35,    36,    20,    21,    22,     5,   121,
     121,   121,   123,    97,     4,     4,     4,     4,   110,     4,
       4,   110,   113,    56,    57,    59,    60,    97,    96,    97,
     121,    50,    51,    55,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,   120,     5,    96,   121,   122,    96,    97,
     121,     4,    97,     5,   122,    97,     4,   123,   121,   121,
      96,   121,    97,    94,   121,   118,   123,   121,    97,   123,
     115,    97,     9,     9,   118,     9,   123,   123,   123,     9,
       6,   123,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   107,   108,
     108,   109,   110,   110,   110,   110,   110,   110,   111,   111,
     112,   112,   112,   112,   113,   113,   114,   114,   115,   115,
     116,   116,   116,   117,   117,   117,   117,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   121,   122,   123,
     123,   124,   124
  };

  const unsigned char
  ConfigParser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     5,     3,     5,     1,     2,
       1,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     1,     2,     1,
       2,     2,     1,     1,     3,     3,     4,     4,     2,     1,
       3,     3,     1,     4,     4,     5,     3,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     5,     1,
       1,     1,     1
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
  "\"`rotation` keyword\"", "\"`scale` keyword\"", "\"`color` keyword\"",
  "\"`material` keyword\"", "\"`texture` keyword\"",
  "\"`anisotropy` keyword\"", "\"`beckmann` keyword\"",
  "\"`blinn` keyword\"", "\"`diffuse` keyword\"",
  "\"`distribution` keyword\"", "\"`element` keyword\"",
  "\"`ggx` keyword\"", "\"`glass` keyword\"", "\"`glossy` keyword\"",
  "\"`ior` keyword\"", "\"`matte` keyword\"", "\"`metal keyword\"",
  "\"`roughness` keyword\"", "\"`specular` keyword\"", "\"`src` keyword\"",
  "\"`path` keyword\"", "\"`Ag`\"", "\"`Al`\"", "\"`Au`\"", "\"`Cu`\"",
  "\"`Fe`\"", "\"`Hg`\"", "\"`Pb`\"", "\"`Pt`\"", "\"`W`\"", "\"`Be`\"",
  "\"`Bi`\"", "\"`Co`\"", "\"`Cr`\"", "\"`Ge`\"", "\"`K`\"", "\"`Li`\"",
  "\"`Mg`\"", "\"`Mn`\"", "\"`Mo`\"", "\"`Na`\"", "\"`Nb`\"", "\"`Ni`\"",
  "\"`Pd`\"", "\"`Rh`\"", "\"`Ta`\"", "\"`Ti`\"", "\"`V`\"", "\"`Zn`\"",
  "\"`Zr`\"", "\"positive integer value\"", "\"integer value\"",
  "\"floating point value\"", "\"quoted string\"", "$accept", "file",
  "stmt", "resolution_obj", "resolution_stmt", "filter_obj", "filter_stmt",
  "camera_obj", "camera_stmt", "world_obj", "world_rec", "world_name",
  "world_stmt", "light_obj", "light_rec", "light_stmt", "texture_obj",
  "texture_rec", "texture_stmt", "material_obj", "material_rec",
  "material_stmt", "element", "vector", "vector2", "number", "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  ConfigParser::yyrline_[] =
  {
       0,   141,   141,   142,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   163,
     163,   165,   166,   167,   170,   170,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   185,   185,   187,
     188,   189,   190,   191,   192,   193,   194,   197,   197,   198,
     198,   199,   201,   202,   203,   204,   205,   206,   209,   209,
     210,   210,   210,   210,   212,   213,   217,   218,   221,   221,
     223,   224,   225,   230,   231,   232,   233,   236,   236,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   295,   300,   304,
     305,   309,   310
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
#line 1782 "config_parser.tab.cc" // lalr1.cc:1167
#line 313 "config_parser.y" // lalr1.cc:1168


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
