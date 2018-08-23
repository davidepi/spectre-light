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
#line 28 "config_parser.y" // lalr1.cc:413
 
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
      case 137: // channel
        value.move< ImageChannel > (that.value);
        break;

      case 139: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 138: // vector
        value.move< Vec3 > (that.value);
        break;

      case 107: // "floating point value"
      case 140: // number
        value.move< float > (that.value);
        break;

      case 106: // "integer value"
      case 141: // integer
        value.move< int > (that.value);
        break;

      case 134: // element
        value.move< metal_t > (that.value);
        break;

      case 108: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 105: // "positive integer value"
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
      case 137: // channel
        value.copy< ImageChannel > (that.value);
        break;

      case 139: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 138: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 107: // "floating point value"
      case 140: // number
        value.copy< float > (that.value);
        break;

      case 106: // "integer value"
      case 141: // integer
        value.copy< int > (that.value);
        break;

      case 134: // element
        value.copy< metal_t > (that.value);
        break;

      case 108: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 105: // "positive integer value"
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
    #line 22 "config_parser.y" // lalr1.cc:741
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 484 "config_parser.tab.cc" // lalr1.cc:741

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
      case 137: // channel
        yylhs.value.build< ImageChannel > ();
        break;

      case 139: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 138: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 107: // "floating point value"
      case 140: // number
        yylhs.value.build< float > ();
        break;

      case 106: // "integer value"
      case 141: // integer
        yylhs.value.build< int > ();
        break;

      case 134: // element
        yylhs.value.build< metal_t > ();
        break;

      case 108: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 105: // "positive integer value"
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
#line 159 "config_parser.y" // lalr1.cc:859
    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 628 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 162 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 634 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 163 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 640 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 164 "config_parser.y" // lalr1.cc:859
    {driver.spp = yystack_[0].value.as< unsigned int > ();}
#line 646 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 165 "config_parser.y" // lalr1.cc:859
    {/* path_trace is the only available and dflt */}
#line 652 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 166 "config_parser.y" // lalr1.cc:859
    {/* camera depends on resolution */}
#line 658 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 167 "config_parser.y" // lalr1.cc:859
    {driver.deferred_shapes.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 664 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 168 "config_parser.y" // lalr1.cc:859
    {driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 670 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 169 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.is_light=true;driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}
#line 676 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 171 "config_parser.y" // lalr1.cc:859
    {driver.children.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}
#line 682 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 172 "config_parser.y" // lalr1.cc:859
    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
#line 688 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 173 "config_parser.y" // lalr1.cc:859
    {driver.deferred_dualmats.push_back(driver.cur_dualmat);driver.cur_dualmat = ParsedDualMaterial();}
#line 694 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 179 "config_parser.y" // lalr1.cc:859
    {driver.width = yystack_[0].value.as< unsigned int > ();}
#line 700 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 180 "config_parser.y" // lalr1.cc:859
    {driver.height = yystack_[0].value.as< unsigned int > ();}
#line 706 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 186 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 712 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 187 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 718 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 188 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 724 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 189 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 730 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 190 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 736 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 191 "config_parser.y" // lalr1.cc:859
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 742 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 192 "config_parser.y" // lalr1.cc:859
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 748 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 193 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = UNFILTERED;}
#line 754 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 194 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = TRILINEAR;}
#line 760 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 195 "config_parser.y" // lalr1.cc:859
    {driver.tex_filter = EWA;}
#line 766 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 201 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 772 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 202 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 778 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 203 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 784 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 204 "config_parser.y" // lalr1.cc:859
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 790 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 205 "config_parser.y" // lalr1.cc:859
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 796 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 206 "config_parser.y" // lalr1.cc:859
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 802 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 207 "config_parser.y" // lalr1.cc:859
    {driver.fov = yystack_[0].value.as< float > ();}
#line 808 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 213 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 814 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 215 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.position = yystack_[0].value.as< Vec3 > ();}
#line 820 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 216 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.rotation = yystack_[0].value.as< Vec3 > ();}
#line 826 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 217 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.scale = yystack_[0].value.as< Vec3 > ();}
#line 832 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 218 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.scale = yystack_[0].value.as< float > ();}
#line 838 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 219 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.material_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 844 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 220 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_tex = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2); driver.cur_mesh.mask = driver.cur_mask;driver.cur_mask = ParsedMask();}
#line 850 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 221 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_tex = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.cur_mesh.mask = driver.cur_mask;driver.cur_mask = ParsedMask();}
#line 856 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 228 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.temperature = yystack_[0].value.as< unsigned int > ();}
#line 862 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 229 "config_parser.y" // lalr1.cc:859
    {driver.cur_mesh.color = yystack_[0].value.as< Vec3 > ();}
#line 868 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 233 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 874 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 234 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 880 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 235 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 886 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 236 "config_parser.y" // lalr1.cc:859
    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}
#line 892 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 241 "config_parser.y" // lalr1.cc:859
    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 898 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 242 "config_parser.y" // lalr1.cc:859
    {driver.tex_scale = yystack_[0].value.as< Vec2 > ();}
#line 904 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 243 "config_parser.y" // lalr1.cc:859
    {driver.tex_scale = Vec2(yystack_[0].value.as< float > ());}
#line 910 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 244 "config_parser.y" // lalr1.cc:859
    {driver.tex_shift = yystack_[0].value.as< Vec2 > ();}
#line 916 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 250 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 922 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 251 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 928 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 252 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 934 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 253 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 940 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 258 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = MATTE;}
#line 946 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 259 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLOSSY;}
#line 952 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 260 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = METAL;}
#line 958 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 261 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.type = GLASS;}
#line 964 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 262 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0);}
#line 970 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 263 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}
#line 976 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 264 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 982 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 265 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 988 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 266 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}
#line 994 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 267 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}
#line 1000 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 268 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
#line 1006 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 269 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
#line 1012 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 270 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
#line 1018 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 271 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1024 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 272 "config_parser.y" // lalr1.cc:859
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.diffuse_uniform = driver.load_texture_uniform();}
#line 1030 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 273 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1036 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 274 "config_parser.y" // lalr1.cc:859
    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.specular_uniform = driver.load_texture_uniform();}
#line 1042 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 275 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.bump = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1048 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 276 "config_parser.y" // lalr1.cc:859
    {driver.cur_mat.elem = yystack_[0].value.as< metal_t > ();}
#line 1054 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 281 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1060 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 282 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1066 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 283 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}
#line 1072 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 284 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1078 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 289 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.first = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1084 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 290 "config_parser.y" // lalr1.cc:859
    {driver.cur_dualmat.second = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}
#line 1090 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 291 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_tex = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.cur_dualmat.mask = driver.cur_mask; driver.cur_mask = ParsedMask();}
#line 1096 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 292 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_tex = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.cur_dualmat.mask = driver.cur_mask; driver.cur_mask = ParsedMask();}
#line 1102 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 300 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_SILVER; }
#line 1108 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 301 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ALUMINIUM; }
#line 1114 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 302 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_GOLD; }
#line 1120 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 120:
#line 303 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_COPPER; }
#line 1126 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 121:
#line 304 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_IRON; }
#line 1132 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 122:
#line 305 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MERCURY; }
#line 1138 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 123:
#line 306 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_LEAD; }
#line 1144 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 124:
#line 307 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_PLATINUM; }
#line 1150 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 125:
#line 308 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TUNGSTEN; }
#line 1156 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 126:
#line 309 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_BERYLLIUM; }
#line 1162 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 127:
#line 310 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_BISMUTH; }
#line 1168 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 128:
#line 311 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_COBALT; }
#line 1174 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 129:
#line 312 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_CHROMIUM; }
#line 1180 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 130:
#line 313 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_GERMANIUM; }
#line 1186 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 131:
#line 314 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_POTASSIUM; }
#line 1192 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 132:
#line 315 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_LITHIUM; }
#line 1198 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 133:
#line 316 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MAGNESIUM; }
#line 1204 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 134:
#line 317 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MANGANESE; }
#line 1210 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 135:
#line 318 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_MOLYBDENUM; }
#line 1216 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 136:
#line 319 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_SODIUM; }
#line 1222 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 137:
#line 320 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_NIOBIUM; }
#line 1228 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 138:
#line 321 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_NICKEL; }
#line 1234 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 139:
#line 322 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_PALLADIUM; }
#line 1240 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 140:
#line 323 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_RHODIUM; }
#line 1246 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 141:
#line 324 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TANTALUM; }
#line 1252 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 142:
#line 325 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_TITANIUM; }
#line 1258 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 143:
#line 326 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_VANADIUM; }
#line 1264 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 144:
#line 327 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ZINC; }
#line 1270 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 145:
#line 328 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< metal_t > () = METAL_ZIRCONIUM; }
#line 1276 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 148:
#line 334 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_chn = yystack_[0].value.as< ImageChannel > ();}
#line 1282 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 149:
#line 335 "config_parser.y" // lalr1.cc:859
    {driver.cur_mask.mask_inv = true;}
#line 1288 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 150:
#line 339 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< ImageChannel > () = RED;}
#line 1294 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 151:
#line 340 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< ImageChannel > () = GREEN;}
#line 1300 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 152:
#line 341 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< ImageChannel > () = BLUE;}
#line 1306 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 153:
#line 342 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< ImageChannel > () = ALPHA;}
#line 1312 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 154:
#line 347 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1318 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 155:
#line 351 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 1324 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 156:
#line 355 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 1330 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 157:
#line 356 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 1336 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 158:
#line 360 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}
#line 1342 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 159:
#line 361 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 1348 "config_parser.tab.cc" // lalr1.cc:859
    break;


#line 1352 "config_parser.tab.cc" // lalr1.cc:859
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


  const short int ConfigParser::yypact_ninf_ = -260;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
     127,  -260,    27,    34,    36,    40,    46,    48,    51,    79,
      98,   118,   119,   122,   124,   226,  -260,   -45,    62,   125,
      71,    29,   128,   133,    37,   134,   140,    11,   144,   164,
    -260,  -260,  -260,  -260,    59,  -260,  -260,  -260,    16,   235,
    -260,   136,   136,   109,  -260,    14,    19,  -260,   179,   184,
     145,  -260,  -260,   196,   197,   198,   205,   112,  -260,  -260,
     206,   207,   209,   210,   214,   231,  -260,   215,   213,    52,
       1,   219,  -260,   218,   224,   227,   242,   243,   244,   246,
     247,   248,   258,   222,   152,  -260,  -260,   259,   260,   269,
     307,   304,    17,  -260,  -260,   309,   310,   311,   312,   313,
      58,  -260,   100,   212,  -260,  -260,   239,    50,    50,    35,
    -260,  -260,   176,   314,   314,   314,    50,  -260,  -260,   216,
    -260,  -260,   316,   318,   319,   321,   322,    52,  -260,   323,
     324,  -260,     1,  -260,  -260,   131,   221,    50,    -1,   -36,
     201,     4,    50,     0,   223,  -260,   326,  -260,   225,   228,
     229,   230,  -260,   328,  -260,   232,     7,   329,   233,  -260,
     331,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,    50,  -260,  -260,  -260,  -260,  -260,   314,   314,    10,
     234,   236,  -260,   240,   314,  -260,  -260,  -260,  -260,  -260,
    -260,   169,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,    50,   314,
    -260,  -260,  -260,  -260,  -260,  -260,   241,    20,   238,  -260,
    -260,   245,  -260,    50,  -260,  -260,  -260,    13,   249,   330,
    -260,  -260,  -260,  -260,  -260,   238,  -260,  -260,   169,   334,
    -260,   169,    20,  -260,  -260,  -260,  -260,  -260,   238,  -260,
    -260,    20,   337,    13,    13,    50,   238,    50,   169,  -260,
      20,    50,    13,   338,    33,   342,    50,  -260,   344,  -260
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
      62,     0,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,   116,     0,     0,     0,
       0,     0,     0,   111,    79,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     5,    20,     0,     0,     0,     0,
       6,    25,     0,     0,     0,     0,     0,    11,    38,     0,
      13,    60,     0,     0,     0,     0,     0,    48,    51,     0,
       0,    66,    61,    65,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    84,     0,     0,
       0,     0,    18,     0,   110,     0,     0,     0,     0,    15,
       0,    73,    22,    23,    27,    28,    29,    30,    31,   158,
     159,   156,    32,   157,    33,    34,    35,    36,    40,    41,
      42,     0,    43,    44,    45,    46,    52,     0,     0,     0,
       0,     0,    50,     0,     0,    63,    64,    89,    87,    86,
      88,    83,    95,    99,   100,    97,    96,    98,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   104,     0,    92,
      91,    90,    94,   101,   102,   103,     0,   109,   114,   112,
     113,     0,    75,     0,    76,    77,    78,    69,     0,     0,
      53,    54,    55,    56,    57,    58,    67,    68,    80,     0,
      93,    81,   106,   150,   151,   152,   153,   149,   115,   147,
     148,   107,     0,    70,    71,     0,    59,     0,    82,   146,
     108,     0,    72,     0,     0,     0,     0,   155,     0,   154
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
    -260,  -260,   303,  -260,   301,  -260,   295,  -260,   289,  -260,
    -260,   317,   -50,  -260,  -260,   237,  -260,  -243,   -98,  -260,
    -193,   -84,  -260,  -234,   -91,  -260,    90,  -259,  -260,  -108,
     -51,  -105,  -260
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    15,    16,    50,    51,    57,    58,    65,    66,    68,
     127,    69,   128,    71,   132,   133,    99,   100,   101,    83,
      84,    85,    91,    92,    93,   237,   278,   279,   280,   182,
     240,   172,   173
  };

  const unsigned short int
  ConfigParser::yytable_[] =
  {
     147,   154,   161,   174,   181,   181,   183,   184,   268,   238,
     121,   185,   253,   272,   283,   181,   205,   206,    43,   289,
     131,   207,    94,    86,   122,    52,    86,   289,    94,    86,
     204,    17,   202,   239,    53,   244,   241,   242,    18,   297,
      19,   292,   296,   129,    20,   123,   124,   290,   130,   125,
      21,   255,    22,    54,    55,    23,    95,    87,    96,    97,
     153,   121,    95,    32,    96,    97,    56,    94,    47,   175,
     176,   177,    48,    49,   126,   122,   259,   192,   288,   260,
     261,   262,   195,    24,   263,    98,   267,    88,    89,    90,
      88,    89,    90,    88,    89,    90,   123,   124,    35,    36,
     125,    95,    25,    96,    97,   254,   256,   203,   243,   169,
     170,   171,   169,   170,   171,   169,   170,   171,    72,    44,
     110,    52,    26,    27,   160,   126,    28,    73,    29,    33,
      53,   270,    34,   269,    37,    38,     1,     2,     3,     4,
      39,    41,     5,     6,     7,    40,     8,    42,   282,    54,
      55,    45,    74,   104,    47,   169,   170,   171,    48,    49,
      75,    72,    56,    76,    77,    78,     9,    10,    11,    79,
      73,    46,    80,    81,    82,    12,    13,    14,    72,    67,
     293,   154,   294,   102,   147,   161,   295,    73,   103,   197,
     198,   298,   199,   200,   161,   146,   178,   179,   180,   154,
     106,   107,   108,    75,   147,   162,    76,    77,    78,   109,
     112,   113,    79,   114,   115,    80,    81,    82,   116,   119,
      75,   120,   135,    76,    77,    78,    30,   134,   136,    79,
     145,   137,    80,    81,    82,     1,     2,     3,     4,   117,
      59,     5,     6,     7,    59,     8,   138,   139,   140,    60,
     141,   142,   143,    60,    61,    62,    63,    64,    61,    62,
      63,    64,   144,   148,   149,     9,    10,    11,   164,   165,
     166,   167,   168,   150,    12,    13,    14,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   273,   274,   275,   276,
     277,   151,   152,   155,   156,   157,   158,   163,    31,   181,
     187,   159,   188,   189,   186,   190,   191,   193,   194,   201,
     246,   245,   251,   247,   253,   258,   248,   249,   250,   285,
     252,   257,   264,   287,   265,   266,   291,   296,   297,   271,
     299,   105,   111,   281,   118,   286,     0,   284,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      84,    92,   100,   108,     5,     5,   114,   115,   201,     5,
       9,   116,     5,   247,   257,     5,    52,    53,     7,   278,
      70,    57,     9,     9,    23,     9,     9,   286,     9,     9,
     138,     4,   137,   141,    18,   143,   141,   142,     4,     6,
       4,   284,     9,    42,     4,    44,    45,   281,    47,    48,
       4,   156,     4,    37,    38,     4,    43,    43,    45,    46,
      43,     9,    43,   108,    45,    46,    50,     9,     9,    34,
      35,    36,    13,    14,    73,    23,   181,   127,   271,   187,
     188,   189,   132,     4,   189,    66,   194,    73,    74,    75,
      73,    74,    75,    73,    74,    75,    44,    45,    27,    28,
      48,    43,     4,    45,    46,   156,   157,   108,   108,   105,
     106,   107,   105,   106,   107,   105,   106,   107,     9,   108,
       8,     9,     4,     4,    66,    73,     4,    18,     4,    67,
      18,   239,     7,   238,   105,     7,     9,    10,    11,    12,
       7,     7,    15,    16,    17,   108,    19,     7,   253,    37,
      38,     7,    43,     8,     9,   105,   106,   107,    13,    14,
      51,     9,    50,    54,    55,    56,    39,    40,    41,    60,
      18,     7,    63,    64,    65,    48,    49,    50,     9,    43,
     285,   272,   287,     4,   268,   283,   291,    18,     4,    58,
      59,   296,    61,    62,   292,    43,    20,    21,    22,   290,
       4,     4,     4,    51,   288,   105,    54,    55,    56,     4,
       4,     4,    60,     4,     4,    63,    64,    65,     4,     4,
      51,     8,     4,    54,    55,    56,     0,     8,     4,    60,
       8,     4,    63,    64,    65,     9,    10,    11,    12,     8,
       9,    15,    16,    17,     9,    19,     4,     4,     4,    18,
       4,     4,     4,    18,    23,    24,    25,    26,    23,    24,
      25,    26,     4,     4,     4,    39,    40,    41,    29,    30,
      31,    32,    33,     4,    48,    49,    50,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,    68,    69,    70,    71,
      72,     4,     8,     4,     4,     4,     4,   105,    15,     5,
       4,     8,     4,     4,   108,     4,     4,     4,     4,   108,
       4,   108,     4,   108,     5,     4,   108,   108,   108,     9,
     108,   108,   108,     9,   108,   105,     9,     9,     6,   108,
       6,    50,    57,   108,    65,   265,    -1,   108,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,    50,   110,   111,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       0,   111,   108,    67,     7,    27,    28,   105,     7,     7,
     108,     7,     7,     7,   108,     7,     7,     9,    13,    14,
     112,   113,     9,    18,    37,    38,    50,   114,   115,     9,
      18,    23,    24,    25,    26,   116,   117,    43,   118,   120,
     120,   122,     9,    18,    43,    51,    54,    55,    56,    60,
      63,    64,    65,   128,   129,   130,     9,    43,    73,    74,
      75,   131,   132,   133,     9,    43,    45,    46,    66,   125,
     126,   127,     4,     4,     8,   113,     4,     4,     4,     4,
       8,   115,     4,     4,     4,     4,     4,     8,   117,     4,
       8,     9,    23,    44,    45,    48,    73,   119,   121,    42,
      47,   121,   123,   124,     8,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     8,    43,   130,     4,     4,
       4,     4,     8,    43,   133,     4,     4,     4,     4,     8,
      66,   127,   105,   105,    29,    30,    31,    32,    33,   105,
     106,   107,   140,   141,   140,    34,    35,    36,    20,    21,
      22,     5,   138,   138,   138,   140,   108,     4,     4,     4,
       4,     4,   121,     4,     4,   121,   124,    58,    59,    61,
      62,   108,   140,   108,   138,    52,    53,    57,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   134,     5,   138,
     139,   140,   140,   108,   138,   108,     4,   108,   108,   108,
     108,     4,   108,     5,   139,   140,   139,   108,     4,   140,
     138,   138,   138,   140,   108,   108,   105,   138,   129,   140,
     138,   108,   132,    68,    69,    70,    71,    72,   135,   136,
     137,   108,   140,   126,   108,     9,   135,     9,   129,   136,
     132,     9,   126,   140,   140,   140,     9,     6,   140,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,   109,   110,   110,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   113,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   119,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     128,   128,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   135,   136,   136,
     137,   137,   137,   137,   138,   139,   140,   140,   141,   141
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
       1,     2,     1,     2,     2,     1,     1,     3,     3,     3,
       4,     4,     5,     2,     1,     3,     3,     3,     3,     1,
       4,     4,     5,     3,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     4,     5,     3,
       2,     1,     3,     3,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     7,     5,     1,     1,     1,     1
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
  "\"`bump` keyword\"", "\"`src` keyword\"", "\"`path` keyword\"",
  "\"Red channel attribute\"", "\"Green channel attribute\"",
  "\"Blue channel attribute\"", "\"Alpha channel attribute\"",
  "\"inverted attribute\"", "\"`mask` keyword\"", "\"`first` keyword\"",
  "\"`second` keyword\"", "\"`Ag`\"", "\"`Al`\"", "\"`Au`\"", "\"`Cu`\"",
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
  "material_stmt", "dualmaterial_obj", "dualmaterial_rec",
  "dualmaterial_stmt", "element", "attributes", "attribute", "channel",
  "vector", "vector2", "number", "integer", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  ConfigParser::yyrline_[] =
  {
       0,   154,   154,   155,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     177,   177,   179,   180,   181,   184,   184,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   199,   199,
     201,   202,   203,   204,   205,   206,   207,   208,   211,   211,
     212,   212,   213,   215,   216,   217,   218,   219,   220,   221,
     222,   225,   225,   226,   226,   226,   226,   228,   229,   233,
     234,   235,   236,   239,   239,   241,   242,   243,   244,   245,
     250,   251,   252,   253,   256,   256,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   281,   282,   283,   284,
     287,   287,   289,   290,   291,   292,   293,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   331,   331,   334,   335,
     339,   340,   341,   342,   346,   351,   355,   356,   360,   361
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
#line 1965 "config_parser.tab.cc" // lalr1.cc:1167
#line 364 "config_parser.y" // lalr1.cc:1168


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
