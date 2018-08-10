// A Bison parser, made by GNU Bison 3.0.5.

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

#line 37 "config_parser.tab.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "config_parser.tab.hh"

// User implementation prologue.

#line 51 "config_parser.tab.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 28 "config_parser.y" // lalr1.cc:415
 
    #include "parsers/config_driver.hpp"

#line 57 "config_parser.tab.cc" // lalr1.cc:415


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
#line 143 "config_parser.tab.cc" // lalr1.cc:481

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
      case 130: // channel
        value.copy< ImageChannel > (that.value);
        break;

      case 132: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 131: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 103: // "floating point value"
      case 133: // number
        value.copy< float > (that.value);
        break;

      case 102: // "integer value"
      case 134: // integer
        value.copy< int > (that.value);
        break;

      case 127: // element
        value.copy< metal_t > (that.value);
        break;

      case 104: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 101: // "positive integer value"
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
      case 130: // channel
        value.move< ImageChannel > (that.value);
        break;

      case 132: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 131: // vector
        value.move< Vec3 > (that.value);
        break;

      case 103: // "floating point value"
      case 133: // number
        value.move< float > (that.value);
        break;

      case 102: // "integer value"
      case 134: // integer
        value.move< int > (that.value);
        break;

      case 127: // element
        value.move< metal_t > (that.value);
        break;

      case 104: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 101: // "positive integer value"
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
      case 130: // channel
        value.copy< ImageChannel > (that.value);
        break;

      case 132: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 131: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 103: // "floating point value"
      case 133: // number
        value.copy< float > (that.value);
        break;

      case 102: // "integer value"
      case 134: // integer
        value.copy< int > (that.value);
        break;

      case 127: // element
        value.copy< metal_t > (that.value);
        break;

      case 104: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 101: // "positive integer value"
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
    #line 22 "config_parser.y" // lalr1.cc:741
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 515 "config_parser.tab.cc" // lalr1.cc:741

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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 130: // channel
        yylhs.value.build< ImageChannel > ();
        break;

      case 132: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 131: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 103: // "floating point value"
      case 133: // number
        yylhs.value.build< float > ();
        break;

      case 102: // "integer value"
      case 134: // integer
        yylhs.value.build< int > ();
        break;

      case 127: // element
        yylhs.value.build< metal_t > ();
        break;

      case 104: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 101: // "positive integer value"
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
      try
        {
          switch (yyn)
            {
  case 4:
#line 155 "config_parser.y" // lalr1.cc:856
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 660 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 7:
#line 158 "config_parser.y" // lalr1.cc:856
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 666 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 8:
#line 159 "config_parser.y" // lalr1.cc:856
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 672 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 9:
#line 160 "config_parser.y" // lalr1.cc:856
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 678 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 10:
#line 161 "config_parser.y" // lalr1.cc:856
    {/* path_trace is the only available and dflt */}
#line 684 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 11:
#line 162 "config_parser.y" // lalr1.cc:856
    {/* camera depends on resolution */}
#line 690 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 12:
#line 163 "config_parser.y" // lalr1.cc:856
    {driver.deferred_shapes.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 696 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 13:
#line 164 "config_parser.y" // lalr1.cc:856
    {driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 702 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 14:
#line 165 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.is_light=true;driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 708 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 16:
#line 167 "config_parser.y" // lalr1.cc:856
    {driver.children.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 714 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 17:
#line 168 "config_parser.y" // lalr1.cc:856
    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
#line 720 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 21:
#line 174 "config_parser.y" // lalr1.cc:856
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 726 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 22:
#line 175 "config_parser.y" // lalr1.cc:856
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 732 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 26:
#line 181 "config_parser.y" // lalr1.cc:856
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 738 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 27:
#line 182 "config_parser.y" // lalr1.cc:856
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 744 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 28:
#line 183 "config_parser.y" // lalr1.cc:856
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 750 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 29:
#line 184 "config_parser.y" // lalr1.cc:856
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 756 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 30:
#line 185 "config_parser.y" // lalr1.cc:856
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 762 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 31:
#line 186 "config_parser.y" // lalr1.cc:856
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 768 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 32:
#line 187 "config_parser.y" // lalr1.cc:856
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 774 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 33:
#line 188 "config_parser.y" // lalr1.cc:856
    {driver.tex_filter = UNFILTERED;}
#line 780 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 34:
#line 189 "config_parser.y" // lalr1.cc:856
    {driver.tex_filter = TRILINEAR;}
#line 786 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 35:
#line 190 "config_parser.y" // lalr1.cc:856
    {driver.tex_filter = EWA;}
#line 792 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 39:
#line 196 "config_parser.y" // lalr1.cc:856
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 798 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 40:
#line 197 "config_parser.y" // lalr1.cc:856
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 804 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 41:
#line 198 "config_parser.y" // lalr1.cc:856
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 810 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 42:
#line 199 "config_parser.y" // lalr1.cc:856
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 816 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 43:
#line 200 "config_parser.y" // lalr1.cc:856
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 822 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 44:
#line 201 "config_parser.y" // lalr1.cc:856
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 828 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 45:
#line 202 "config_parser.y" // lalr1.cc:856
    {driver.fov = yystack_[0].value.as< float > ();}
#line 834 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 51:
#line 208 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 840 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 52:
#line 210 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.position = yystack_[0].value.as< Vec3 > ();}
#line 846 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 53:
#line 211 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.rotation = yystack_[0].value.as< Vec3 > ();}
#line 852 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 54:
#line 212 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.scale = yystack_[0].value.as< Vec3 > ();}
#line 858 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 55:
#line 213 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.scale = yystack_[0].value.as< float > ();}
#line 864 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 56:
#line 214 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.material_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 870 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 57:
#line 215 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.mask_tex = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 876 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 58:
#line 216 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.mask_tex = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 882 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 66:
#line 223 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.temperature = yystack_[0].value.as< unsigned int > ();}
#line 888 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 67:
#line 224 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.color = yystack_[0].value.as< Vec3 > ();}
#line 894 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 68:
#line 228 "config_parser.y" // lalr1.cc:856
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 900 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 69:
#line 229 "config_parser.y" // lalr1.cc:856
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 906 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 70:
#line 230 "config_parser.y" // lalr1.cc:856
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 912 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 71:
#line 231 "config_parser.y" // lalr1.cc:856
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 918 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 74:
#line 236 "config_parser.y" // lalr1.cc:856
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 924 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 75:
#line 237 "config_parser.y" // lalr1.cc:856
    {driver.tex_scale = yystack_[0].value.as< Vec2 > ();}
#line 930 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 76:
#line 238 "config_parser.y" // lalr1.cc:856
    {driver.tex_scale = Vec2(yystack_[0].value.as< float > ());}
#line 936 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 77:
#line 239 "config_parser.y" // lalr1.cc:856
    {driver.tex_shift = yystack_[0].value.as< Vec2 > ();}
#line 942 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 79:
#line 245 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 948 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 80:
#line 246 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 954 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 81:
#line 247 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 960 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 82:
#line 248 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 966 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 85:
#line 253 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.type = MATTE;}
#line 972 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 86:
#line 254 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.type = GLOSSY;}
#line 978 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 87:
#line 255 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.type = METAL;}
#line 984 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 88:
#line 256 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.type = GLASS;}
#line 990 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 89:
#line 257 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0);}
#line 996 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 90:
#line 258 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}
#line 1002 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 91:
#line 259 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 1008 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 92:
#line 260 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 1014 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 93:
#line 261 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}
#line 1020 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 94:
#line 262 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}
#line 1026 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 95:
#line 263 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
#line 1032 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 96:
#line 264 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
#line 1038 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 97:
#line 265 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
#line 1044 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 98:
#line 266 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1050 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 99:
#line 267 "config_parser.y" // lalr1.cc:856
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.diffuse_uniform = driver.load_texture_uniform();}
#line 1056 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 100:
#line 268 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1062 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 101:
#line 269 "config_parser.y" // lalr1.cc:856
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.specular_uniform = driver.load_texture_uniform();}
#line 1068 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 102:
#line 270 "config_parser.y" // lalr1.cc:856
    {driver.cur_mat.elem = yystack_[0].value.as< metal_t > ();}
#line 1074 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 104:
#line 278 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_SILVER; }
#line 1080 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 105:
#line 279 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_ALUMINIUM; }
#line 1086 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 106:
#line 280 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_GOLD; }
#line 1092 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 107:
#line 281 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_COPPER; }
#line 1098 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 108:
#line 282 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_IRON; }
#line 1104 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 109:
#line 283 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_MERCURY; }
#line 1110 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 110:
#line 284 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_LEAD; }
#line 1116 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 111:
#line 285 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_PLATINUM; }
#line 1122 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 112:
#line 286 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_TUNGSTEN; }
#line 1128 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 113:
#line 287 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_BERYLLIUM; }
#line 1134 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 114:
#line 288 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_BISMUTH; }
#line 1140 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 115:
#line 289 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_COBALT; }
#line 1146 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 116:
#line 290 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_CHROMIUM; }
#line 1152 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 117:
#line 291 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_GERMANIUM; }
#line 1158 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 118:
#line 292 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_POTASSIUM; }
#line 1164 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 119:
#line 293 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_LITHIUM; }
#line 1170 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 120:
#line 294 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_MAGNESIUM; }
#line 1176 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 121:
#line 295 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_MANGANESE; }
#line 1182 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 122:
#line 296 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_MOLYBDENUM; }
#line 1188 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 123:
#line 297 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_SODIUM; }
#line 1194 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 124:
#line 298 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_NIOBIUM; }
#line 1200 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 125:
#line 299 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_NICKEL; }
#line 1206 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 126:
#line 300 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_PALLADIUM; }
#line 1212 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 127:
#line 301 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_RHODIUM; }
#line 1218 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 128:
#line 302 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_TANTALUM; }
#line 1224 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 129:
#line 303 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_TITANIUM; }
#line 1230 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 130:
#line 304 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_VANADIUM; }
#line 1236 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 131:
#line 305 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_ZINC; }
#line 1242 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 132:
#line 306 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< metal_t > () = METAL_ZIRCONIUM; }
#line 1248 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 135:
#line 312 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.mask_chn = yystack_[0].value.as< ImageChannel > ();}
#line 1254 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 136:
#line 313 "config_parser.y" // lalr1.cc:856
    {driver.cur_mesh.mask_inv = true;}
#line 1260 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 137:
#line 317 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< ImageChannel > () = RED;}
#line 1266 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 138:
#line 318 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< ImageChannel > () = GREEN;}
#line 1272 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 139:
#line 319 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< ImageChannel > () = BLUE;}
#line 1278 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 140:
#line 320 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< ImageChannel > () = ALPHA;}
#line 1284 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 141:
#line 325 "config_parser.y" // lalr1.cc:856
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1290 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 142:
#line 329 "config_parser.y" // lalr1.cc:856
    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1296 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 143:
#line 333 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 1302 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 144:
#line 334 "config_parser.y" // lalr1.cc:856
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 1308 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 145:
#line 338 "config_parser.y" // lalr1.cc:856
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 1314 "config_parser.tab.cc" // lalr1.cc:856
    break;

  case 146:
#line 339 "config_parser.y" // lalr1.cc:856
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 1320 "config_parser.tab.cc" // lalr1.cc:856
    break;


#line 1324 "config_parser.tab.cc" // lalr1.cc:856
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
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
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


  const short int ConfigParser::yypact_ninf_ = -206;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
     205,  -206,    11,    16,    21,    24,    40,    49,    52,    53,
      61,    62,    64,    79,   194,  -206,   -86,   -58,    72,    20,
     -12,    85,    88,    -5,    91,    94,    10,   109,  -206,  -206,
    -206,  -206,    67,  -206,  -206,  -206,   114,    15,  -206,    70,
      70,    75,  -206,    18,  -206,   113,   117,   135,  -206,  -206,
     122,   123,   131,   142,    82,  -206,  -206,   146,   149,   150,
     157,   161,   276,  -206,   163,   160,    14,     7,   175,  -206,
     165,   167,   174,   180,   181,   191,   192,   195,   198,   179,
     127,  -206,  -206,   203,   204,   208,   214,   211,    51,  -206,
      97,   129,  -206,  -206,   196,   -15,   -15,   106,  -206,  -206,
     137,   218,   218,   218,   -15,  -206,  -206,   128,  -206,  -206,
     227,   237,   245,   248,   282,    14,  -206,   283,   284,  -206,
       7,  -206,  -206,   190,   185,   -15,    -2,    -6,   183,     3,
     -15,    -1,  -206,   286,  -206,   187,     6,   287,   189,  -206,
     291,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,   -15,  -206,  -206,  -206,  -206,  -206,   218,   218,     9,
     193,   199,  -206,   197,   218,  -206,  -206,  -206,  -206,  -206,
    -206,   138,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   -15,   218,
    -206,  -206,  -206,  -206,  -206,   200,  -206,   -15,  -206,  -206,
    -206,   130,   201,   297,  -206,  -206,  -206,  -206,  -206,   170,
    -206,  -206,   138,   298,  -206,   138,   299,   130,   130,   -15,
    -206,  -206,  -206,  -206,  -206,   170,  -206,  -206,   -15,   138,
     -15,   130,   300,  -206,    13,   290,   -15,  -206,   304,  -206
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
       0,     0,     0,    38,     0,     0,    48,    61,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    84,    78,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     5,    19,     0,     0,     0,     0,     6,    24,
       0,     0,     0,     0,     0,    11,    37,     0,    13,    59,
       0,     0,     0,     0,     0,    47,    50,     0,     0,    65,
      60,    64,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    83,     0,     0,     0,     0,    15,
       0,    72,    21,    22,    26,    27,    28,    29,    30,   145,
     146,   143,    31,   144,    32,    33,    34,    35,    39,    40,
      41,     0,    42,    43,    44,    45,    51,     0,     0,     0,
       0,     0,    49,     0,     0,    62,    63,    88,    86,    85,
      87,    82,    94,    98,    99,    96,    95,    97,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   102,     0,    91,
      90,    89,    93,   100,   101,     0,    74,     0,    75,    76,
      77,    68,     0,     0,    52,    53,    54,    55,    56,    57,
      66,    67,    79,     0,    92,    80,     0,    69,    70,     0,
     137,   138,   139,   140,   136,    58,   134,   135,     0,    81,
       0,    71,     0,   133,     0,     0,     0,   142,     0,   141
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
    -206,  -206,   301,  -206,   264,  -206,   258,  -206,   251,  -206,
    -206,   274,   -46,  -206,  -206,   202,  -206,  -205,   -87,  -206,
    -172,   -80,  -206,  -206,    63,  -206,   -97,  -124,   -94,  -206
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    48,    54,    55,    62,    63,    65,
     115,    66,   116,    68,   120,   121,    87,    88,    89,    79,
      80,    81,   217,   255,   256,   257,   162,   220,   152,   153
  };

  const unsigned short int
  ConfigParser::yytable_[] =
  {
     134,   141,   154,   161,   161,   163,   164,    31,   218,   242,
     165,   227,   228,   230,   161,    16,   109,    41,    30,   267,
      17,   119,   266,   109,    56,    18,   247,    82,    19,   184,
     110,   182,   219,    57,   224,   221,   222,   110,    58,    59,
      60,    61,   229,   261,    20,   185,   186,    33,    34,   117,
     187,   111,   112,    21,   118,   113,    22,    23,   111,   112,
      82,    83,   113,    84,    85,    24,    25,   233,    26,   172,
     234,   235,   236,   259,   175,   237,    44,   241,   114,    32,
      45,    46,    86,    27,    69,   114,   149,   150,   151,    35,
      98,    49,    36,    70,    83,    37,    84,    85,    39,    38,
      50,    40,   183,   223,   149,   150,   151,   149,   150,   151,
     149,   150,   151,    64,    42,   140,    43,    90,    71,    51,
      52,    91,   244,    49,   243,    72,    94,    95,    73,    74,
      75,    53,    50,   246,    76,    96,    69,    77,    78,    82,
     155,   156,   157,    92,    44,    70,    97,    69,    45,    46,
     100,    51,    52,   101,   102,   262,    70,   158,   159,   160,
     141,   103,   134,    53,   264,   104,   265,   107,   108,   123,
     133,   124,   268,    83,   141,    84,    85,    72,   125,   134,
      73,    74,    75,   122,   126,   127,    76,   132,    72,    77,
      78,    73,    74,    75,    28,   128,   129,    76,   142,   130,
      77,    78,   131,     1,     2,     3,     4,   135,   136,     5,
       6,     7,   137,     8,     1,     2,     3,     4,   138,   139,
       5,     6,     7,   161,     8,   144,   145,   146,   147,   148,
     143,   167,   166,     9,    10,    11,   250,   251,   252,   253,
     254,   168,    12,    13,     9,    10,    11,   177,   178,   169,
     179,   180,   170,    12,    13,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   105,    56,   171,   173,   174,   181,
     225,   226,   227,   231,    57,   232,   267,   238,   240,    58,
      59,    60,    61,   239,   245,   248,   249,   258,   260,   266,
     269,    93,    99,   106,    67,    29,     0,     0,   263,     0,
       0,     0,   176
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      80,    88,    96,     5,     5,   102,   103,    65,     5,   181,
     104,     5,   136,   137,     5,     4,     9,     7,   104,     6,
       4,    67,     9,     9,     9,     4,   231,     9,     4,   126,
      23,   125,   129,    18,   131,   129,   130,    23,    23,    24,
      25,    26,   136,   248,     4,    51,    52,    27,    28,    42,
      56,    44,    45,     4,    47,    48,     4,     4,    44,    45,
       9,    43,    48,    45,    46,     4,     4,   161,     4,   115,
     167,   168,   169,   245,   120,   169,     9,   174,    71,     7,
      13,    14,    64,     4,     9,    71,   101,   102,   103,   101,
       8,     9,     7,    18,    43,     7,    45,    46,     7,   104,
      18,     7,   104,   104,   101,   102,   103,   101,   102,   103,
     101,   102,   103,    43,   104,    64,     7,     4,    43,    37,
      38,     4,   219,     9,   218,    50,     4,     4,    53,    54,
      55,    49,    18,   227,    59,     4,     9,    62,    63,     9,
      34,    35,    36,     8,     9,    18,     4,     9,    13,    14,
       4,    37,    38,     4,     4,   249,    18,    20,    21,    22,
     247,     4,   242,    49,   258,     4,   260,     4,     8,     4,
      43,     4,   266,    43,   261,    45,    46,    50,     4,   259,
      53,    54,    55,     8,     4,     4,    59,     8,    50,    62,
      63,    53,    54,    55,     0,     4,     4,    59,   101,     4,
      62,    63,     4,     9,    10,    11,    12,     4,     4,    15,
      16,    17,     4,    19,     9,    10,    11,    12,     4,     8,
      15,    16,    17,     5,    19,    29,    30,    31,    32,    33,
     101,     4,   104,    39,    40,    41,    66,    67,    68,    69,
      70,     4,    48,    49,    39,    40,    41,    57,    58,     4,
      60,    61,     4,    48,    49,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     8,     9,     4,     4,     4,   104,
       4,   104,     5,   104,    18,     4,     6,   104,   101,    23,
      24,    25,    26,   104,   104,   104,     9,     9,     9,     9,
       6,    47,    54,    62,    40,    14,    -1,    -1,   255,    -1,
      -1,    -1,   120
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,   106,   107,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     0,   107,
     104,    65,     7,    27,    28,   101,     7,     7,   104,     7,
       7,     7,   104,     7,     9,    13,    14,   108,   109,     9,
      18,    37,    38,    49,   110,   111,     9,    18,    23,    24,
      25,    26,   112,   113,    43,   114,   116,   116,   118,     9,
      18,    43,    50,    53,    54,    55,    59,    62,    63,   124,
     125,   126,     9,    43,    45,    46,    64,   121,   122,   123,
       4,     4,     8,   109,     4,     4,     4,     4,     8,   111,
       4,     4,     4,     4,     4,     8,   113,     4,     8,     9,
      23,    44,    45,    48,    71,   115,   117,    42,    47,   117,
     119,   120,     8,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     8,    43,   126,     4,     4,     4,     4,     8,
      64,   123,   101,   101,    29,    30,    31,    32,    33,   101,
     102,   103,   133,   134,   133,    34,    35,    36,    20,    21,
      22,     5,   131,   131,   131,   133,   104,     4,     4,     4,
       4,     4,   117,     4,     4,   117,   120,    57,    58,    60,
      61,   104,   133,   104,   131,    51,    52,    56,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   127,     5,   131,
     132,   133,   133,   104,   131,     4,   104,     5,   132,   133,
     132,   104,     4,   133,   131,   131,   131,   133,   104,   104,
     101,   131,   125,   133,   131,   104,   133,   122,   104,     9,
      66,    67,    68,    69,    70,   128,   129,   130,     9,   125,
       9,   122,   133,   129,   133,   133,     9,     6,   133,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,   105,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     108,   109,   109,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   113,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   119,   119,   120,   120,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   123,   123,   124,
     124,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   131,   132,   133,   133,   134,   134
  };

  const unsigned char
  ConfigParser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     5,     3,     5,     1,     2,
       1,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     4,     1,
       2,     1,     2,     2,     1,     1,     3,     3,     3,     4,
       4,     5,     2,     1,     3,     3,     3,     3,     1,     4,
       4,     5,     3,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
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
  "\"`color` keyword\"", "\"`material` keyword\"", "\"`texture` keyword\"",
  "\"`anisotropy` keyword\"", "\"`beckmann` keyword\"",
  "\"`blinn` keyword\"", "\"`diffuse` keyword\"",
  "\"`distribution` keyword\"", "\"`element` keyword\"",
  "\"`ggx` keyword\"", "\"`glass` keyword\"", "\"`glossy` keyword\"",
  "\"`ior` keyword\"", "\"`matte` keyword\"", "\"`metal keyword\"",
  "\"`roughness` keyword\"", "\"`specular` keyword\"", "\"`src` keyword\"",
  "\"`path` keyword\"", "\"Red channel attribute\"",
  "\"Green channel attribute\"", "\"Blue channel attribute\"",
  "\"Alpha channel attribute\"", "\"inverted attribute\"",
  "\"`mask` keyword\"", "\"`Ag`\"", "\"`Al`\"", "\"`Au`\"", "\"`Cu`\"",
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
  "material_stmt", "element", "attributes", "attribute", "channel",
  "vector", "vector2", "number", "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  ConfigParser::yyrline_[] =
  {
       0,   150,   150,   151,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   172,
     172,   174,   175,   176,   179,   179,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   194,   194,   196,
     197,   198,   199,   200,   201,   202,   203,   206,   206,   207,
     207,   208,   210,   211,   212,   213,   214,   215,   216,   217,
     220,   220,   221,   221,   221,   221,   223,   224,   228,   229,
     230,   231,   234,   234,   236,   237,   238,   239,   240,   245,
     246,   247,   248,   251,   251,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   309,   309,   312,   313,   317,   318,   319,
     320,   324,   329,   333,   334,   338,   339
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
#line 1911 "config_parser.tab.cc" // lalr1.cc:1163
#line 342 "config_parser.y" // lalr1.cc:1164


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
