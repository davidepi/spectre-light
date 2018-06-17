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



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "config_parser.tab.hh"

// User implementation prologue.


// Unqualified %code blocks.

 
    #include "parsers/config_driver.hpp"




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
      case 123: // vector2
        value.move< Vec2 > (that.value);
        break;

      case 122: // vector
        value.move< Vec3 > (that.value);
        break;

      case 97: // "floating point value"
      case 124: // number
        value.move< float > (that.value);
        break;

      case 96: // "integer value"
      case 125: // integer
        value.move< int > (that.value);
        break;

      case 121: // element
        value.move< metal_t > (that.value);
        break;

      case 98: // "quoted string"
        value.move< std::string > (that.value);
        break;

      case 95: // "positive integer value"
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
      case 123: // vector2
        value.copy< Vec2 > (that.value);
        break;

      case 122: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 97: // "floating point value"
      case 124: // number
        value.copy< float > (that.value);
        break;

      case 96: // "integer value"
      case 125: // integer
        value.copy< int > (that.value);
        break;

      case 121: // element
        value.copy< metal_t > (that.value);
        break;

      case 98: // "quoted string"
        value.copy< std::string > (that.value);
        break;

      case 95: // "positive integer value"
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
    
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}



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
      case 123: // vector2
        yylhs.value.build< Vec2 > ();
        break;

      case 122: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 97: // "floating point value"
      case 124: // number
        yylhs.value.build< float > ();
        break;

      case 96: // "integer value"
      case 125: // integer
        yylhs.value.build< int > ();
        break;

      case 121: // element
        yylhs.value.build< metal_t > ();
        break;

      case 98: // "quoted string"
        yylhs.value.build< std::string > ();
        break;

      case 95: // "positive integer value"
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

    {driver.output = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 7:

    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}

    break;

  case 8:

    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}

    break;

  case 9:

    {driver.spp = yystack_[0].value.as< unsigned int > ();}

    break;

  case 10:

    {/* path_trace is the only available and dflt */}

    break;

  case 11:

    {/* camera depends on resolution */}

    break;

  case 12:

    {driver.deferred_shapes.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}

    break;

  case 13:

    {driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}

    break;

  case 14:

    {driver.cur_mesh.is_light=true;driver.deferred_meshes.push_back(driver.cur_mesh);driver.cur_mesh=MeshWorld();}

    break;

  case 16:

    {driver.children.push_back(yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2));}

    break;

  case 17:

    {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}

    break;

  case 21:

    {driver.width = yystack_[0].value.as< unsigned int > ();}

    break;

  case 22:

    {driver.height = yystack_[0].value.as< unsigned int > ();}

    break;

  case 26:

    {driver.filter_type = SPECTRE_FILTER_BOX;}

    break;

  case 27:

    {driver.filter_type = SPECTRE_FILTER_TENT;}

    break;

  case 28:

    {driver.filter_type = SPECTRE_FILTER_GAUSS;}

    break;

  case 29:

    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}

    break;

  case 30:

    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}

    break;

  case 31:

    {driver.value0 = yystack_[0].value.as< float > ();}

    break;

  case 32:

    {driver.value1 = yystack_[0].value.as< float > ();}

    break;

  case 33:

    {driver.tex_filter = UNFILTERED;}

    break;

  case 34:

    {driver.tex_filter = TRILINEAR;}

    break;

  case 35:

    {driver.tex_filter = EWA;}

    break;

  case 39:

    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}

    break;

  case 40:

    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}

    break;

  case 41:

    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}

    break;

  case 42:

    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}

    break;

  case 43:

    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}

    break;

  case 44:

    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}

    break;

  case 45:

    {driver.fov = yystack_[0].value.as< float > ();}

    break;

  case 51:

    {driver.cur_mesh.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 52:

    {driver.cur_mesh.position = yystack_[0].value.as< Vec3 > ();}

    break;

  case 53:

    {driver.cur_mesh.rotation = yystack_[0].value.as< Vec3 > ();}

    break;

  case 54:

    {driver.cur_mesh.scale = yystack_[0].value.as< Vec3 > ();}

    break;

  case 55:

    {driver.cur_mesh.scale = yystack_[0].value.as< float > ();}

    break;

  case 56:

    {driver.cur_mesh.material_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 64:

    {driver.cur_mesh.temperature = yystack_[0].value.as< unsigned int > ();}

    break;

  case 65:

    {driver.cur_mesh.color = yystack_[0].value.as< Vec3 > ();}

    break;

  case 66:

    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}

    break;

  case 67:

    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}

    break;

  case 68:

    {driver.tex_src=yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}

    break;

  case 69:

    {driver.tex_src=yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);driver.load_texture(driver.tex_src);}

    break;

  case 72:

    {driver.tex_name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 73:

    {driver.tex_scale = yystack_[0].value.as< Vec2 > ();}

    break;

  case 74:

    {driver.tex_scale = Vec2(yystack_[0].value.as< float > ());}

    break;

  case 75:

    {driver.tex_shift = yystack_[0].value.as< Vec2 > ();}

    break;

  case 77:

    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}

    break;

  case 78:

    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 79:

    {driver.cur_mat.name = yystack_[1].value.as< std::string > ().substr(1,yystack_[1].value.as< std::string > ().size()-2);}

    break;

  case 80:

    {driver.cur_mat.name = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 83:

    {driver.cur_mat.type = MATTE;}

    break;

  case 84:

    {driver.cur_mat.type = GLOSSY;}

    break;

  case 85:

    {driver.cur_mat.type = METAL;}

    break;

  case 86:

    {driver.cur_mat.type = GLASS;}

    break;

  case 87:

    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< float > (),0);}

    break;

  case 88:

    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec2 > ().x,yystack_[0].value.as< Vec2 > ().y);}

    break;

  case 89:

    {driver.cur_mat.ior = cauchy(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}

    break;

  case 90:

    {driver.cur_mat.ior = sellmeier(yystack_[1].value.as< Vec3 > ().x,yystack_[1].value.as< Vec3 > ().y,yystack_[1].value.as< Vec3 > ().z,yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}

    break;

  case 91:

    {driver.cur_mat.rough_x = yystack_[0].value.as< float > ();}

    break;

  case 92:

    {driver.cur_mat.rough_y = yystack_[0].value.as< float > ();}

    break;

  case 93:

    {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}

    break;

  case 94:

    {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}

    break;

  case 95:

    {driver.cur_mat.dist = SPECTRE_DIST_GGX;}

    break;

  case 96:

    {driver.cur_mat.diffuse = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 97:

    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.diffuse_uniform = driver.load_texture_uniform();}

    break;

  case 98:

    {driver.cur_mat.specular = yystack_[0].value.as< std::string > ().substr(1,yystack_[0].value.as< std::string > ().size()-2);}

    break;

  case 99:

    {driver.tex_color = yystack_[0].value.as< Vec3 > (); driver.cur_mat.specular_uniform = driver.load_texture_uniform();}

    break;

  case 100:

    {driver.cur_mat.elem = yystack_[0].value.as< metal_t > ();}

    break;

  case 102:

    {yylhs.value.as< metal_t > () = METAL_SILVER; }

    break;

  case 103:

    {yylhs.value.as< metal_t > () = METAL_ALUMINIUM; }

    break;

  case 104:

    {yylhs.value.as< metal_t > () = METAL_GOLD; }

    break;

  case 105:

    {yylhs.value.as< metal_t > () = METAL_COPPER; }

    break;

  case 106:

    {yylhs.value.as< metal_t > () = METAL_IRON; }

    break;

  case 107:

    {yylhs.value.as< metal_t > () = METAL_MERCURY; }

    break;

  case 108:

    {yylhs.value.as< metal_t > () = METAL_LEAD; }

    break;

  case 109:

    {yylhs.value.as< metal_t > () = METAL_PLATINUM; }

    break;

  case 110:

    {yylhs.value.as< metal_t > () = METAL_TUNGSTEN; }

    break;

  case 111:

    {yylhs.value.as< metal_t > () = METAL_BERYLLIUM; }

    break;

  case 112:

    {yylhs.value.as< metal_t > () = METAL_BISMUTH; }

    break;

  case 113:

    {yylhs.value.as< metal_t > () = METAL_COBALT; }

    break;

  case 114:

    {yylhs.value.as< metal_t > () = METAL_CHROMIUM; }

    break;

  case 115:

    {yylhs.value.as< metal_t > () = METAL_GERMANIUM; }

    break;

  case 116:

    {yylhs.value.as< metal_t > () = METAL_POTASSIUM; }

    break;

  case 117:

    {yylhs.value.as< metal_t > () = METAL_LITHIUM; }

    break;

  case 118:

    {yylhs.value.as< metal_t > () = METAL_MAGNESIUM; }

    break;

  case 119:

    {yylhs.value.as< metal_t > () = METAL_MANGANESE; }

    break;

  case 120:

    {yylhs.value.as< metal_t > () = METAL_MOLYBDENUM; }

    break;

  case 121:

    {yylhs.value.as< metal_t > () = METAL_SODIUM; }

    break;

  case 122:

    {yylhs.value.as< metal_t > () = METAL_NIOBIUM; }

    break;

  case 123:

    {yylhs.value.as< metal_t > () = METAL_NICKEL; }

    break;

  case 124:

    {yylhs.value.as< metal_t > () = METAL_PALLADIUM; }

    break;

  case 125:

    {yylhs.value.as< metal_t > () = METAL_RHODIUM; }

    break;

  case 126:

    {yylhs.value.as< metal_t > () = METAL_TANTALUM; }

    break;

  case 127:

    {yylhs.value.as< metal_t > () = METAL_TITANIUM; }

    break;

  case 128:

    {yylhs.value.as< metal_t > () = METAL_VANADIUM; }

    break;

  case 129:

    {yylhs.value.as< metal_t > () = METAL_ZINC; }

    break;

  case 130:

    {yylhs.value.as< metal_t > () = METAL_ZIRCONIUM; }

    break;

  case 131:

    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}

    break;

  case 132:

    { yylhs.value.as< Vec2 > () = Vec2(yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}

    break;

  case 133:

    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}

    break;

  case 134:

    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}

    break;

  case 135:

    { yylhs.value.as< int > () = yystack_[0].value.as< unsigned int > ();}

    break;

  case 136:

    { yylhs.value.as< int > () = yystack_[0].value.as< int > ();}

    break;



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


  const short int ConfigParser::yypact_ninf_ = -209;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
     178,  -209,    11,    16,    23,    35,    42,    47,    50,    52,
      58,    61,    74,    81,   167,  -209,   -85,   -40,    68,    21,
      -5,    90,   110,    30,   116,   125,     2,   135,  -209,  -209,
    -209,  -209,    19,  -209,  -209,  -209,   101,   187,  -209,   103,
     103,    29,  -209,    -1,  -209,   145,   147,    10,  -209,  -209,
     150,   152,   154,   158,    78,  -209,  -209,   165,   168,   177,
     188,   194,   249,  -209,   205,   163,   176,    13,   172,  -209,
     210,   218,   219,   221,   258,   259,   260,   261,   262,   183,
      71,  -209,  -209,   264,   265,   266,   267,   268,     7,  -209,
      80,   182,  -209,  -209,   171,    -2,    -2,   225,  -209,  -209,
     115,   273,   273,   273,    -2,  -209,  -209,   181,  -209,  -209,
     276,   277,   278,   279,   176,  -209,   280,   281,  -209,    13,
    -209,  -209,    83,   189,    -2,     0,    25,   162,     6,    -2,
       1,  -209,   282,  -209,   190,     9,   284,   192,  -209,   287,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
      -2,  -209,  -209,  -209,  -209,  -209,   273,   273,    12,   195,
    -209,   197,   273,  -209,  -209,  -209,  -209,  -209,  -209,   111,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,    -2,   273,  -209,  -209,
    -209,  -209,  -209,   196,  -209,    -2,  -209,  -209,  -209,   102,
     198,   286,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   111,
     288,  -209,   111,   289,   102,   102,    -2,    -2,   111,    -2,
     102,   290,    34,   294,    -2,  -209,   295,  -209
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
       0,     0,     0,    38,     0,     0,    48,    59,     0,   101,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,    76,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     5,    19,     0,     0,     0,     0,     6,    24,
       0,     0,     0,     0,     0,    11,    37,     0,    13,    57,
       0,     0,     0,     0,    47,    50,     0,     0,    63,    58,
      62,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    81,     0,     0,     0,     0,    15,     0,
      70,    21,    22,    26,    27,    28,    29,    30,   135,   136,
     133,    31,   134,    32,    33,    34,    35,    39,    40,    41,
       0,    42,    43,    44,    45,    51,     0,     0,     0,     0,
      49,     0,     0,    60,    61,    86,    84,    83,    85,    80,
      92,    96,    97,    94,    93,    95,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   100,     0,    89,    88,    87,
      91,    98,    99,     0,    72,     0,    73,    74,    75,    66,
       0,     0,    52,    53,    54,    55,    56,    64,    65,    77,
       0,    90,    78,     0,    67,    68,     0,     0,    79,     0,
      69,     0,     0,     0,     0,   132,     0,   131
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
    -209,  -209,   291,  -209,   255,  -209,   250,  -209,   241,  -209,
    -209,   269,   -55,  -209,  -209,   191,  -209,  -208,   -87,  -209,
    -172,   -80,  -209,   -99,   -23,   -94,  -209
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    14,    15,    47,    48,    54,    55,    62,    63,    65,
     114,    66,   115,    68,   119,   120,    87,    88,    89,    79,
      80,    81,   215,   161,   218,   151,   152
  };

  const unsigned short int
  ConfigParser::yytable_[] =
  {
     133,   140,   153,   162,   163,   160,   160,   239,    82,    41,
     164,   216,   118,    30,   225,    16,    82,   160,    92,    44,
      17,   244,   109,    45,    46,    31,   182,    18,    44,   217,
     180,   222,    45,    46,   219,   220,   110,   250,    69,    19,
     255,   227,    83,   254,    84,    85,    20,    70,    33,    34,
      83,    21,    84,    85,    22,   116,    23,   111,   112,   170,
     117,   113,    24,    86,   173,    25,   231,   232,   233,   234,
     248,   139,    71,   238,   235,    32,   183,   184,    26,    72,
      69,   185,    73,    74,    75,    27,    98,    49,    76,    70,
      35,    77,    78,   148,   149,   150,    50,    36,   181,   221,
      42,   148,   149,   150,   148,   149,   150,   148,   149,   150,
      49,    82,   226,   228,   132,    51,    52,    37,   241,    50,
      69,    72,   240,    39,    73,    74,    75,    53,    38,    70,
      76,   243,    40,    77,    78,   157,   158,   159,    51,    52,
     175,   176,    43,   177,   178,    83,    64,    84,    85,    90,
      53,    91,   251,   252,    94,   253,    95,   140,    96,   133,
     256,    72,    97,   140,    73,    74,    75,    28,   133,   100,
      76,   108,   101,    77,    78,   141,     1,     2,     3,     4,
     121,   102,     5,     6,     7,   109,     8,     1,     2,     3,
       4,   131,   103,     5,     6,     7,    56,     8,   104,   110,
     143,   144,   145,   146,   147,    57,     9,    10,    11,   107,
      58,    59,    60,    61,   122,    12,    13,     9,    10,    11,
     111,   112,   123,   124,   113,   125,    12,    13,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   105,    56,   154,
     155,   156,   126,   127,   128,   129,   130,    57,   134,   135,
     136,   137,    58,    59,    60,    61,   138,   142,   160,   165,
     166,   167,   168,   169,   171,   172,   223,   179,   224,   225,
     229,   230,   237,   236,   242,   246,   245,   247,   249,   254,
     255,   257,    93,   106,    99,    29,     0,     0,     0,    67,
     174
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      80,    88,    96,   102,   103,     5,     5,   179,     9,     7,
     104,     5,    67,    98,     5,     4,     9,     5,     8,     9,
       4,   229,     9,    13,    14,    65,   125,     4,     9,   128,
     124,   130,    13,    14,   128,   129,    23,   245,     9,     4,
       6,   135,    43,     9,    45,    46,     4,    18,    27,    28,
      43,     4,    45,    46,     4,    42,     4,    44,    45,   114,
      47,    48,     4,    64,   119,     4,   160,   166,   167,   168,
     242,    64,    43,   172,   168,     7,    51,    52,     4,    50,
       9,    56,    53,    54,    55,     4,     8,     9,    59,    18,
      95,    62,    63,    95,    96,    97,    18,     7,    98,    98,
      98,    95,    96,    97,    95,    96,    97,    95,    96,    97,
       9,     9,   135,   136,    43,    37,    38,     7,   217,    18,
       9,    50,   216,     7,    53,    54,    55,    49,    98,    18,
      59,   225,     7,    62,    63,    20,    21,    22,    37,    38,
      57,    58,     7,    60,    61,    43,    43,    45,    46,     4,
      49,     4,   246,   247,     4,   249,     4,   244,     4,   239,
     254,    50,     4,   250,    53,    54,    55,     0,   248,     4,
      59,     8,     4,    62,    63,    95,     9,    10,    11,    12,
       8,     4,    15,    16,    17,     9,    19,     9,    10,    11,
      12,     8,     4,    15,    16,    17,     9,    19,     4,    23,
      29,    30,    31,    32,    33,    18,    39,    40,    41,     4,
      23,    24,    25,    26,     4,    48,    49,    39,    40,    41,
      44,    45,     4,     4,    48,     4,    48,    49,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     8,     9,    34,
      35,    36,     4,     4,     4,     4,     4,    18,     4,     4,
       4,     4,    23,    24,    25,    26,     8,    95,     5,    98,
       4,     4,     4,     4,     4,     4,     4,    98,    98,     5,
      98,     4,    95,    98,    98,     9,    98,     9,     9,     9,
       6,     6,    47,    62,    54,    14,    -1,    -1,    -1,    40,
     119
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,   100,   101,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     0,   101,
      98,    65,     7,    27,    28,    95,     7,     7,    98,     7,
       7,     7,    98,     7,     9,    13,    14,   102,   103,     9,
      18,    37,    38,    49,   104,   105,     9,    18,    23,    24,
      25,    26,   106,   107,    43,   108,   110,   110,   112,     9,
      18,    43,    50,    53,    54,    55,    59,    62,    63,   118,
     119,   120,     9,    43,    45,    46,    64,   115,   116,   117,
       4,     4,     8,   103,     4,     4,     4,     4,     8,   105,
       4,     4,     4,     4,     4,     8,   107,     4,     8,     9,
      23,    44,    45,    48,   109,   111,    42,    47,   111,   113,
     114,     8,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     8,    43,   120,     4,     4,     4,     4,     8,    64,
     117,    95,    95,    29,    30,    31,    32,    33,    95,    96,
      97,   124,   125,   124,    34,    35,    36,    20,    21,    22,
       5,   122,   122,   122,   124,    98,     4,     4,     4,     4,
     111,     4,     4,   111,   114,    57,    58,    60,    61,    98,
     124,    98,   122,    51,    52,    56,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,   121,     5,   122,   123,   124,
     124,    98,   122,     4,    98,     5,   123,   124,   123,    98,
       4,   124,   122,   122,   122,   124,    98,    95,   122,   119,
     124,   122,    98,   124,   116,    98,     9,     9,   119,     9,
     116,   124,   124,   124,     9,     6,   124,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   102,
     102,   103,   103,   103,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   110,   111,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   113,   113,   114,   114,   115,   115,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   123,   124,   124,   125,   125
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
       2,     2,     1,     1,     3,     3,     3,     4,     4,     5,
       2,     1,     3,     3,     3,     3,     1,     4,     4,     5,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,   142,   142,   143,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   164,
     164,   166,   167,   168,   171,   171,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   186,   186,   188,
     189,   190,   191,   192,   193,   194,   195,   198,   198,   199,
     199,   200,   202,   203,   204,   205,   206,   207,   210,   210,
     211,   211,   211,   211,   213,   214,   218,   219,   220,   221,
     224,   224,   226,   227,   228,   229,   230,   235,   236,   237,
     238,   241,   241,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   300,   305,   309,   310,   314,   315
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




void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
