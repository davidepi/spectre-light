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
      case 84: // vector
        value.move< Vec3 > (that.value);
        break;

      case 63: // "floating point value"
      case 85: // number
        value.move< float > (that.value);
        break;

      case 62: // "integer value"
        value.move< int > (that.value);
        break;

      case 64: // "quoted string"
        value.move< std::string > (that.value);
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
      case 84: // vector
        value.copy< Vec3 > (that.value);
        break;

      case 63: // "floating point value"
      case 85: // number
        value.copy< float > (that.value);
        break;

      case 62: // "integer value"
        value.copy< int > (that.value);
        break;

      case 64: // "quoted string"
        value.copy< std::string > (that.value);
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

#line 450 "config_parser.tab.cc" // lalr1.cc:745

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
      case 84: // vector
        yylhs.value.build< Vec3 > ();
        break;

      case 63: // "floating point value"
      case 85: // number
        yylhs.value.build< float > ();
        break;

      case 62: // "integer value"
        yylhs.value.build< int > ();
        break;

      case 64: // "quoted string"
        yylhs.value.build< std::string > ();
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
#line 108 "config_parser.y" // lalr1.cc:859
    {driver.output = yystack_[0].value.as< std::string > ();}
#line 577 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 110 "config_parser.y" // lalr1.cc:859
    {driver.build_filter();}
#line 583 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 111 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
#line 589 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 112 "config_parser.y" // lalr1.cc:859
    {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
#line 595 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 113 "config_parser.y" // lalr1.cc:859
    {driver.spp = yystack_[0].value.as< int > ();}
#line 601 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 114 "config_parser.y" // lalr1.cc:859
    {/* path_trace is the only available and dflt */}
#line 607 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 115 "config_parser.y" // lalr1.cc:859
    {/* camera depends on resolution */}
#line 613 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 126 "config_parser.y" // lalr1.cc:859
    {driver.resolution[0] = yystack_[0].value.as< int > ();}
#line 619 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 127 "config_parser.y" // lalr1.cc:859
    {driver.resolution[1] = yystack_[0].value.as< int > ();}
#line 625 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 132 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_BOX;}
#line 631 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 133 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_TENT;}
#line 637 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 134 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_GAUSS;}
#line 643 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 135 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
#line 649 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 136 "config_parser.y" // lalr1.cc:859
    {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
#line 655 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 137 "config_parser.y" // lalr1.cc:859
    {driver.value0 = yystack_[0].value.as< float > ();}
#line 661 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 138 "config_parser.y" // lalr1.cc:859
    {driver.value1 = yystack_[0].value.as< float > ();}
#line 667 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 143 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
#line 673 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 144 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
#line 679 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 145 "config_parser.y" // lalr1.cc:859
    {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
#line 685 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 146 "config_parser.y" // lalr1.cc:859
    {driver.camera_pos = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 691 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 147 "config_parser.y" // lalr1.cc:859
    {driver.camera_tar = Point3(yystack_[0].value.as< Vec3 > ().x,yystack_[0].value.as< Vec3 > ().y,yystack_[0].value.as< Vec3 > ().z);}
#line 697 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 148 "config_parser.y" // lalr1.cc:859
    {driver.camera_up = yystack_[0].value.as< Vec3 > ();}
#line 703 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 149 "config_parser.y" // lalr1.cc:859
    {driver.fov = yystack_[0].value.as< float > ();}
#line 709 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 194 "config_parser.y" // lalr1.cc:859
    { yylhs.value.as< Vec3 > () = Vec3(yystack_[5].value.as< float > (),yystack_[3].value.as< float > (),yystack_[1].value.as< float > ());}
#line 715 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 199 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 721 "config_parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 200 "config_parser.y" // lalr1.cc:859
    {yylhs.value.as< float > () = (float)yystack_[0].value.as< int > ();}
#line 727 "config_parser.tab.cc" // lalr1.cc:859
    break;


#line 731 "config_parser.tab.cc" // lalr1.cc:859
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


  const signed char ConfigParser::yypact_ninf_ = -85;

  const signed char ConfigParser::yytable_ninf_ = -1;

  const short int
  ConfigParser::yypact_[] =
  {
      98,    26,    32,    42,    49,    52,    65,    68,    74,    92,
     100,   112,   116,     3,   -85,   -36,    34,    95,    40,    50,
     115,   117,    59,   118,   123,   124,     1,   -85,   -85,   -85,
     -85,    73,   -85,   -85,   -85,    20,    66,   -85,    93,    93,
      48,   -31,   -85,   128,   142,    63,   -85,   145,   146,   147,
       9,   -85,   148,   149,   150,   151,   152,   103,   -85,   153,
     154,    10,     6,   155,   156,   157,   160,   161,   162,   163,
     164,   165,   166,    24,   -85,   167,   168,   169,    96,    97,
     -85,   -85,   108,    56,    56,   -85,   -85,   -10,   170,   170,
     170,   110,   -85,   -85,   114,   -85,   172,   175,   176,    -7,
     -85,   177,   178,   -18,   -85,   -85,    91,   119,   111,    -4,
      33,   120,   122,   125,    -3,   -85,   -85,   126,   127,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,    56,   -85,   -85,   -85,   -85,   -85,
     170,   170,    -1,   182,   -85,   130,   170,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   129,   158,   184,   -85,   -85,
     -85,   -85,   131,   -85,   -85,   183,   190,    56,   -85,   132,
     133,   191,   -85,   -85,    56,   193,   -85
  };

  const unsigned char
  ConfigParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     4,
      10,     0,     7,     8,     9,     0,     0,    12,     0,     0,
       0,     0,    15,     0,     0,     0,    19,     0,     0,     0,
       0,    23,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       5,    18,     0,     0,     0,     6,    22,     0,     0,     0,
       0,     0,    11,    31,     0,    13,     0,     0,     0,    40,
      43,     0,     0,    49,    52,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    58,     0,     0,    16,
      20,    21,    24,    25,    26,    27,    28,    78,    77,    29,
      30,    33,    34,    35,     0,    36,    37,    38,    39,    44,
       0,     0,     0,     0,    41,     0,     0,    50,    51,    64,
      62,    61,    63,    60,    68,    73,    72,    70,    69,    71,
      66,    65,    67,    75,    74,     0,    55,     0,    45,    46,
      48,    47,     0,    53,    54,     0,     0,     0,    42,     0,
       0,     0,    56,    57,     0,     0,    76
  };

  const short int
  ConfigParser::yypgoto_[] =
  {
     -85,   -85,   188,   -85,   159,   -85,   171,   -85,   173,   -85,
     -85,   174,     2,   -85,   -85,    99,   -85,   -85,   134,   -83,
     -84
  };

  const short int
  ConfigParser::yydefgoto_[] =
  {
      -1,    13,    14,    45,    46,    50,    51,    57,    58,    60,
      99,    61,   100,    63,   103,   104,    77,    73,    74,   135,
     129
  };

  const unsigned char
  ConfigParser::yytable_[] =
  {
     130,   134,   134,    27,   134,    96,   136,   137,    41,    75,
     131,   132,   133,     1,     2,     3,    96,    85,     4,     5,
       6,   101,     7,    97,    98,   102,   156,    47,    29,    76,
      15,   164,   115,    96,    97,    98,    16,   143,    47,     8,
       9,    10,    64,    48,    49,   101,    17,    11,    12,   102,
     167,    97,    98,    18,    48,    49,    19,   168,   169,   171,
     155,   163,   170,   174,    65,    42,    64,    32,    33,    20,
      66,    80,    21,    67,    68,    69,    43,    44,    22,    70,
     157,   158,    71,    72,    52,   159,    43,    44,    65,    53,
      54,    55,    56,   181,    66,    30,    23,    67,    68,    69,
     185,   144,    31,    70,    24,   147,    71,    72,     1,     2,
       3,    92,    34,     4,     5,     6,    25,     7,   127,   128,
      26,    52,    35,    37,    36,    38,    53,    54,    55,    56,
      39,    40,    78,    59,     8,     9,    10,   122,   123,   124,
     125,   126,    11,    12,   149,   150,    79,   151,   152,    82,
      83,    84,    87,    88,    89,    90,    91,    94,   120,   121,
     106,   107,    95,   105,   108,   109,   110,   111,   112,   113,
     114,   117,   118,   138,   154,   134,   140,   119,   139,   141,
     142,   145,   146,   153,   160,   161,   172,   179,   162,   175,
     165,   166,   173,   177,   180,   178,   182,   183,   176,   186,
     184,    28,   148,     0,    81,     0,     0,   116,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,     0,
       0,    86,     0,     0,     0,     0,     0,     0,     0,     0,
      93
  };

  const short int
  ConfigParser::yycheck_[] =
  {
      84,     5,     5,     0,     5,    23,    89,    90,     7,    40,
      20,    21,    22,    10,    11,    12,    23,     8,    15,    16,
      17,    39,    19,    41,    42,    43,   109,    18,    64,    60,
       4,   114,     8,    23,    41,    42,     4,    44,    18,    36,
      37,    38,    18,    34,    35,    39,     4,    44,    45,    43,
     134,    41,    42,     4,    34,    35,     4,   140,   141,   142,
      64,    64,    63,   146,    40,    64,    18,    27,    28,     4,
      46,     8,     4,    49,    50,    51,    13,    14,     4,    55,
      47,    48,    58,    59,    18,    52,    13,    14,    40,    23,
      24,    25,    26,   177,    46,    61,     4,    49,    50,    51,
     184,    99,     7,    55,     4,   103,    58,    59,    10,    11,
      12,     8,    62,    15,    16,    17,     4,    19,    62,    63,
       4,    18,     7,    64,     7,     7,    23,    24,    25,    26,
       7,     7,     4,    40,    36,    37,    38,    29,    30,    31,
      32,    33,    44,    45,    53,    54,     4,    56,    57,     4,
       4,     4,     4,     4,     4,     4,     4,     4,    62,    62,
       4,     4,     8,     8,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    63,    63,     5,     4,     8,    64,     4,
       4,     4,     4,    64,    64,    63,     4,     4,    63,    60,
      64,    64,    62,     9,     4,    64,    64,    64,    40,     6,
       9,    13,   103,    -1,    45,    -1,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57
  };

  const unsigned char
  ConfigParser::yystos_[] =
  {
       0,    10,    11,    12,    15,    16,    17,    19,    36,    37,
      38,    44,    45,    66,    67,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     0,    67,    64,
      61,     7,    27,    28,    62,     7,     7,    64,     7,     7,
       7,     7,    64,    13,    14,    68,    69,    18,    34,    35,
      70,    71,    18,    23,    24,    25,    26,    72,    73,    40,
      74,    76,    76,    78,    18,    40,    46,    49,    50,    51,
      55,    58,    59,    82,    83,    40,    60,    81,     4,     4,
       8,    69,     4,     4,     4,     8,    71,     4,     4,     4,
       4,     4,     8,    73,     4,     8,    23,    41,    42,    75,
      77,    39,    43,    79,    80,     8,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     8,    83,     4,     4,     8,
      62,    62,    29,    30,    31,    32,    33,    62,    63,    85,
      85,    20,    21,    22,     5,    84,    84,    84,    63,    64,
       4,     4,     4,    44,    77,     4,     4,    77,    80,    53,
      54,    56,    57,    64,    63,    64,    84,    47,    48,    52,
      64,    63,    63,    64,    84,    64,    64,    85,    84,    84,
      63,    84,     4,    62,    84,    60,    40,     9,    64,     4,
       4,    85,    64,    64,     9,    85,     6
  };

  const unsigned char
  ConfigParser::yyr1_[] =
  {
       0,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      74,    75,    75,    75,    76,    77,    77,    77,    77,    78,
      79,    79,    79,    80,    80,    81,    81,    81,    82,    82,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    85,    85
  };

  const unsigned char
  ConfigParser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     3,     5,     5,     2,     1,
       3,     3,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     1,     3,     3,     3,     3,     3,     2,
       2,     2,     1,     3,     3,     3,     6,     6,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     7,     1,     1
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
  "\"`pt` keyword\"", "\"integer value\"", "\"floating point value\"",
  "\"quoted string\"", "$accept", "file", "stmt", "resolution_obj",
  "resolution_stmt", "filter_obj", "filter_stmt", "camera_obj",
  "camera_stmt", "world_obj", "world_rec", "world_name", "world_stmt",
  "light_obj", "light_rec", "light_stmt", "texture_obj", "material_obj",
  "material_stmt", "vector", "number", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  ConfigParser::yyrline_[] =
  {
       0,   103,   103,   104,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   124,   124,
     126,   127,   130,   130,   132,   133,   134,   135,   136,   137,
     138,   141,   141,   143,   144,   145,   146,   147,   148,   149,
     152,   153,   153,   153,   154,   156,   157,   158,   159,   162,
     163,   163,   163,   164,   164,   167,   168,   169,   172,   172,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   193,   199,   200
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
#line 1245 "config_parser.tab.cc" // lalr1.cc:1167
#line 203 "config_parser.y" // lalr1.cc:1168


void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
