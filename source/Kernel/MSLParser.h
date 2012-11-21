#ifndef YY_MSLParser_h_included
#define YY_MSLParser_h_included
#define YY_USE_CLASS

#line 1 "/usr/share/bison++/bison.h"
/* before anything */
#ifdef c_plusplus
 #ifndef __cplusplus
  #define __cplusplus
 #endif
#endif


 #line 8 "/usr/share/bison++/bison.h"
#define YY_MSLParser_LSP_NEEDED 
#define YY_MSLParser_MEMBERS \
	virtual ~MSLParser(){}\
	private:\
		yyFlexLexer lexer;\
		MAO* currentMAO;
#define YY_MSLParser_LEX_BODY  {return lexer.yylex();}
#define YY_MSLParser_ERROR_BODY  {std::cout <<std::endl<<"~ MSL Error Reporting ~"<<std::endl;\
					std::cout<< "-----------------------"<<std::endl;\
					std::cout<< "Error encountered at line: "<<lexer.lineno()<<std::endl;\
					std::cout<< "Last symbol parsed: "<<lexer.YYText()<<std::endl;\
					std::cout<< "Exiting..."<<std::endl;\
					exit(-1);\
					}
#line 22 "Kernel/MSLParser.y"

#include <cstdlib>
#include <FlexLexer.h>
#include <opencv/cv.h>
#include <btBulletDynamicsCommon.h>

#include <Kernel/MSLProperties.h>
#include <Factories/MAOFactory.h>
#include <Factories/MLBFactory.h>
#include <Kernel/Logger.h>


#line 39 "Kernel/MSLParser.y"
typedef union {
	int int_type;
	bool bool_type;
	float float_type;
	std::string* string_type;
	cv::Mat* pose_type;
	MSLProperties* param_type;
	btVector3* vector3_type;
	MAOValue* maovalue_type;
	MAOProperty* maoproperty_type;
	std::vector<std::string*>* vectorstr_type;
} yy_MSLParser_stype;
#define YY_MSLParser_STYPE yy_MSLParser_stype

#line 21 "/usr/share/bison++/bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_MSLParser_COMPATIBILITY
 #ifndef YY_USE_CLASS
  #define  YY_MSLParser_COMPATIBILITY 1
 #else
  #define  YY_MSLParser_COMPATIBILITY 0
 #endif
#endif

#if YY_MSLParser_COMPATIBILITY != 0
/* backward compatibility */
 #ifdef YYLTYPE
  #ifndef YY_MSLParser_LTYPE
   #define YY_MSLParser_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
  #endif
 #endif
/*#ifdef YYSTYPE*/
  #ifndef YY_MSLParser_STYPE
   #define YY_MSLParser_STYPE YYSTYPE
  /* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
   /* use %define STYPE */
  #endif
/*#endif*/
 #ifdef YYDEBUG
  #ifndef YY_MSLParser_DEBUG
   #define  YY_MSLParser_DEBUG YYDEBUG
   /* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
   /* use %define DEBUG */
  #endif
 #endif 
 /* use goto to be compatible */
 #ifndef YY_MSLParser_USE_GOTO
  #define YY_MSLParser_USE_GOTO 1
 #endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_MSLParser_USE_GOTO
 #define YY_MSLParser_USE_GOTO 0
#endif

#ifndef YY_MSLParser_PURE

 #line 65 "/usr/share/bison++/bison.h"

#line 65 "/usr/share/bison++/bison.h"
/* YY_MSLParser_PURE */
#endif


 #line 68 "/usr/share/bison++/bison.h"

#line 68 "/usr/share/bison++/bison.h"
/* prefix */

#ifndef YY_MSLParser_DEBUG

 #line 71 "/usr/share/bison++/bison.h"

#line 71 "/usr/share/bison++/bison.h"
/* YY_MSLParser_DEBUG */
#endif

#ifndef YY_MSLParser_LSP_NEEDED

 #line 75 "/usr/share/bison++/bison.h"

#line 75 "/usr/share/bison++/bison.h"
 /* YY_MSLParser_LSP_NEEDED*/
#endif

/* DEFAULT LTYPE*/
#ifdef YY_MSLParser_LSP_NEEDED
 #ifndef YY_MSLParser_LTYPE
  #ifndef BISON_YYLTYPE_ISDECLARED
   #define BISON_YYLTYPE_ISDECLARED
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;
  #endif

  #define YY_MSLParser_LTYPE yyltype
 #endif
#endif

/* DEFAULT STYPE*/
#ifndef YY_MSLParser_STYPE
 #define YY_MSLParser_STYPE int
#endif

/* DEFAULT MISCELANEOUS */
#ifndef YY_MSLParser_PARSE
 #define YY_MSLParser_PARSE yyparse
#endif

#ifndef YY_MSLParser_LEX
 #define YY_MSLParser_LEX yylex
#endif

#ifndef YY_MSLParser_LVAL
 #define YY_MSLParser_LVAL yylval
#endif

#ifndef YY_MSLParser_LLOC
 #define YY_MSLParser_LLOC yylloc
#endif

#ifndef YY_MSLParser_CHAR
 #define YY_MSLParser_CHAR yychar
#endif

#ifndef YY_MSLParser_NERRS
 #define YY_MSLParser_NERRS yynerrs
#endif

#ifndef YY_MSLParser_DEBUG_FLAG
 #define YY_MSLParser_DEBUG_FLAG yydebug
#endif

#ifndef YY_MSLParser_ERROR
 #define YY_MSLParser_ERROR yyerror
#endif

#ifndef YY_MSLParser_PARSE_PARAM
 #ifndef __STDC__
  #ifndef __cplusplus
   #ifndef YY_USE_CLASS
    #define YY_MSLParser_PARSE_PARAM
    #ifndef YY_MSLParser_PARSE_PARAM_DEF
     #define YY_MSLParser_PARSE_PARAM_DEF
    #endif
   #endif
  #endif
 #endif
 #ifndef YY_MSLParser_PARSE_PARAM
  #define YY_MSLParser_PARSE_PARAM void
 #endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

 #ifndef YY_MSLParser_PURE
  #ifndef yylval
   extern YY_MSLParser_STYPE YY_MSLParser_LVAL;
  #else
   #if yylval != YY_MSLParser_LVAL
    extern YY_MSLParser_STYPE YY_MSLParser_LVAL;
   #else
    #warning "Namespace conflict, disabling some functionality (bison++ only)"
   #endif
  #endif
 #endif


 #line 169 "/usr/share/bison++/bison.h"
#define	INTEGER	258
#define	T_INTEGER	259
#define	FLOAT	260
#define	T_FLOAT	261
#define	STRING	262
#define	T_STRING	263
#define	BOOL	264
#define	T_BOOL	265
#define	T_POSE	266
#define	IDENTIFIER	267
#define	ARROW	268
#define	DOT	269
#define	PARAM_NAME	270
#define	PARAM_PATH	271
#define	PARAM_SIZE	272
#define	PARAM_MARKS	273
#define	PARAM_POS	274
#define	PARAM_COLOR	275
#define	PARAM_WIDTH	276
#define	PARAM_HEIGHT	277
#define	PARAM_TEXT	278
#define	PARAM_PATH_ORJ	279
#define	PARAM_PATH_TEX	280
#define	PARAM_ANIM_TYPE	281
#define	PARAM_REFERENCE	282
#define	PARAM_MAO	283
#define	PARAM_TIME	284
#define	PARAM_OFFSET	285
#define	PARAM_IMPULSE	286
#define	PARAM_ANG_AXIS	287
#define	PARAM_PROPERTY	288
#define	PARAM_ROT_TYPE	289
#define	PARAM_LOC_TYPE	290
#define	PARAM_ROTATION	291
#define	PARAM_LOCATION	292
#define	PARAM_TYPE	293
#define	PARAM_VALUE	294
#define	PARAM_VALUE1	295
#define	PARAM_VALUE2	296
#define	PARAM_ACTUATOR	297
#define	PARAM_KEY	298
#define	PARAM_DISTANCE	299
#define	PARAM_PROBABILITY	300
#define	PARAM_INVERSE	301
#define	PARAM_GRAVITY	302
#define	PARAM_AXIS	303
#define	PARAM_MASS	304
#define	PARAM_SHAPE	305
#define	PARAM_SHADOWS	306
#define	PARAM_SUN	307
#define	MAOWORLD	308
#define	MAOMARK	309
#define	MAOMARKSGROUP	310
#define	MAORENDERABLE2DIMAGE	311
#define	MAORENDERABLE2DTEXT	312
#define	MAORENDERABLE3DLINE	313
#define	MAORENDERABLE3DORJ	314
#define	MAORENDERABLE3DPATH	315
#define	MAORENDERABLE3DTEAPOT	316
#define	MLBACTUATORADDDYNAMICOBJECT	317
#define	MLBACTUATORANG	318
#define	MLBACTUATORCHANGEPOSE	319
#define	MLBACTUATORDISTANCE	320
#define	MLBACTUATORPATHADDPOINT	321
#define	MLBACTUATORPATHREMOVEPOINTS	322
#define	MLBACTUATORPROPERTY	323
#define	MLBACTUATORQUITAPP	324
#define	MLBACTUATORRANDOM	325
#define	MLBACTUATORRELATIVEPOSE	326
#define	MLBACTUATORSOUND	327
#define	MLBACTUATORVISIBILITY	328
#define	MLBACTUATORANIMOREJ	329
#define	MLBCONTROLLERAND	330
#define	MLBCONTROLLERNAND	331
#define	MLBCONTROLLERNOR	332
#define	MLBCONTROLLEROR	333
#define	MLBCONTROLLERSCRIPT	334
#define	MLBSENSORACTUATOR	335
#define	MLBSENSORALWAYS	336
#define	MLBSENSORCOLLISION	337
#define	MLBSENSORDELAY	338
#define	MLBSENSORKEYBOARD	339
#define	MLBSENSORNEAR	340
#define	MLBSENSORPROPERTY	341
#define	MLBSENSORRANDOM	342
#define	GROUND	343
#define	DYNAMICOBJECT	344
#define	STATICOBJECT	345


#line 169 "/usr/share/bison++/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
 #ifndef YY_MSLParser_CLASS
  #define YY_MSLParser_CLASS MSLParser
 #endif

 #ifndef YY_MSLParser_INHERIT
  #define YY_MSLParser_INHERIT
 #endif

 #ifndef YY_MSLParser_MEMBERS
  #define YY_MSLParser_MEMBERS 
 #endif

 #ifndef YY_MSLParser_LEX_BODY
  #define YY_MSLParser_LEX_BODY  
 #endif

 #ifndef YY_MSLParser_ERROR_BODY
  #define YY_MSLParser_ERROR_BODY  
 #endif

 #ifndef YY_MSLParser_CONSTRUCTOR_PARAM
  #define YY_MSLParser_CONSTRUCTOR_PARAM
 #endif
 /* choose between enum and const */
 #ifndef YY_MSLParser_USE_CONST_TOKEN
  #define YY_MSLParser_USE_CONST_TOKEN 0
  /* yes enum is more compatible with flex,  */
  /* so by default we use it */ 
 #endif
 #if YY_MSLParser_USE_CONST_TOKEN != 0
  #ifndef YY_MSLParser_ENUM_TOKEN
   #define YY_MSLParser_ENUM_TOKEN yy_MSLParser_enum_token
  #endif
 #endif

class YY_MSLParser_CLASS YY_MSLParser_INHERIT
{
public: 
 #if YY_MSLParser_USE_CONST_TOKEN != 0
  /* static const int token ... */
  
 #line 212 "/usr/share/bison++/bison.h"
static const int INTEGER;
static const int T_INTEGER;
static const int FLOAT;
static const int T_FLOAT;
static const int STRING;
static const int T_STRING;
static const int BOOL;
static const int T_BOOL;
static const int T_POSE;
static const int IDENTIFIER;
static const int ARROW;
static const int DOT;
static const int PARAM_NAME;
static const int PARAM_PATH;
static const int PARAM_SIZE;
static const int PARAM_MARKS;
static const int PARAM_POS;
static const int PARAM_COLOR;
static const int PARAM_WIDTH;
static const int PARAM_HEIGHT;
static const int PARAM_TEXT;
static const int PARAM_PATH_ORJ;
static const int PARAM_PATH_TEX;
static const int PARAM_ANIM_TYPE;
static const int PARAM_REFERENCE;
static const int PARAM_MAO;
static const int PARAM_TIME;
static const int PARAM_OFFSET;
static const int PARAM_IMPULSE;
static const int PARAM_ANG_AXIS;
static const int PARAM_PROPERTY;
static const int PARAM_ROT_TYPE;
static const int PARAM_LOC_TYPE;
static const int PARAM_ROTATION;
static const int PARAM_LOCATION;
static const int PARAM_TYPE;
static const int PARAM_VALUE;
static const int PARAM_VALUE1;
static const int PARAM_VALUE2;
static const int PARAM_ACTUATOR;
static const int PARAM_KEY;
static const int PARAM_DISTANCE;
static const int PARAM_PROBABILITY;
static const int PARAM_INVERSE;
static const int PARAM_GRAVITY;
static const int PARAM_AXIS;
static const int PARAM_MASS;
static const int PARAM_SHAPE;
static const int PARAM_SHADOWS;
static const int PARAM_SUN;
static const int MAOWORLD;
static const int MAOMARK;
static const int MAOMARKSGROUP;
static const int MAORENDERABLE2DIMAGE;
static const int MAORENDERABLE2DTEXT;
static const int MAORENDERABLE3DLINE;
static const int MAORENDERABLE3DORJ;
static const int MAORENDERABLE3DPATH;
static const int MAORENDERABLE3DTEAPOT;
static const int MLBACTUATORADDDYNAMICOBJECT;
static const int MLBACTUATORANG;
static const int MLBACTUATORCHANGEPOSE;
static const int MLBACTUATORDISTANCE;
static const int MLBACTUATORPATHADDPOINT;
static const int MLBACTUATORPATHREMOVEPOINTS;
static const int MLBACTUATORPROPERTY;
static const int MLBACTUATORQUITAPP;
static const int MLBACTUATORRANDOM;
static const int MLBACTUATORRELATIVEPOSE;
static const int MLBACTUATORSOUND;
static const int MLBACTUATORVISIBILITY;
static const int MLBACTUATORANIMOREJ;
static const int MLBCONTROLLERAND;
static const int MLBCONTROLLERNAND;
static const int MLBCONTROLLERNOR;
static const int MLBCONTROLLEROR;
static const int MLBCONTROLLERSCRIPT;
static const int MLBSENSORACTUATOR;
static const int MLBSENSORALWAYS;
static const int MLBSENSORCOLLISION;
static const int MLBSENSORDELAY;
static const int MLBSENSORKEYBOARD;
static const int MLBSENSORNEAR;
static const int MLBSENSORPROPERTY;
static const int MLBSENSORRANDOM;
static const int GROUND;
static const int DYNAMICOBJECT;
static const int STATICOBJECT;


#line 212 "/usr/share/bison++/bison.h"
 /* decl const */
 #else
  enum YY_MSLParser_ENUM_TOKEN { YY_MSLParser_NULL_TOKEN=0
  
 #line 215 "/usr/share/bison++/bison.h"
	,INTEGER=258
	,T_INTEGER=259
	,FLOAT=260
	,T_FLOAT=261
	,STRING=262
	,T_STRING=263
	,BOOL=264
	,T_BOOL=265
	,T_POSE=266
	,IDENTIFIER=267
	,ARROW=268
	,DOT=269
	,PARAM_NAME=270
	,PARAM_PATH=271
	,PARAM_SIZE=272
	,PARAM_MARKS=273
	,PARAM_POS=274
	,PARAM_COLOR=275
	,PARAM_WIDTH=276
	,PARAM_HEIGHT=277
	,PARAM_TEXT=278
	,PARAM_PATH_ORJ=279
	,PARAM_PATH_TEX=280
	,PARAM_ANIM_TYPE=281
	,PARAM_REFERENCE=282
	,PARAM_MAO=283
	,PARAM_TIME=284
	,PARAM_OFFSET=285
	,PARAM_IMPULSE=286
	,PARAM_ANG_AXIS=287
	,PARAM_PROPERTY=288
	,PARAM_ROT_TYPE=289
	,PARAM_LOC_TYPE=290
	,PARAM_ROTATION=291
	,PARAM_LOCATION=292
	,PARAM_TYPE=293
	,PARAM_VALUE=294
	,PARAM_VALUE1=295
	,PARAM_VALUE2=296
	,PARAM_ACTUATOR=297
	,PARAM_KEY=298
	,PARAM_DISTANCE=299
	,PARAM_PROBABILITY=300
	,PARAM_INVERSE=301
	,PARAM_GRAVITY=302
	,PARAM_AXIS=303
	,PARAM_MASS=304
	,PARAM_SHAPE=305
	,PARAM_SHADOWS=306
	,PARAM_SUN=307
	,MAOWORLD=308
	,MAOMARK=309
	,MAOMARKSGROUP=310
	,MAORENDERABLE2DIMAGE=311
	,MAORENDERABLE2DTEXT=312
	,MAORENDERABLE3DLINE=313
	,MAORENDERABLE3DORJ=314
	,MAORENDERABLE3DPATH=315
	,MAORENDERABLE3DTEAPOT=316
	,MLBACTUATORADDDYNAMICOBJECT=317
	,MLBACTUATORANG=318
	,MLBACTUATORCHANGEPOSE=319
	,MLBACTUATORDISTANCE=320
	,MLBACTUATORPATHADDPOINT=321
	,MLBACTUATORPATHREMOVEPOINTS=322
	,MLBACTUATORPROPERTY=323
	,MLBACTUATORQUITAPP=324
	,MLBACTUATORRANDOM=325
	,MLBACTUATORRELATIVEPOSE=326
	,MLBACTUATORSOUND=327
	,MLBACTUATORVISIBILITY=328
	,MLBACTUATORANIMOREJ=329
	,MLBCONTROLLERAND=330
	,MLBCONTROLLERNAND=331
	,MLBCONTROLLERNOR=332
	,MLBCONTROLLEROR=333
	,MLBCONTROLLERSCRIPT=334
	,MLBSENSORACTUATOR=335
	,MLBSENSORALWAYS=336
	,MLBSENSORCOLLISION=337
	,MLBSENSORDELAY=338
	,MLBSENSORKEYBOARD=339
	,MLBSENSORNEAR=340
	,MLBSENSORPROPERTY=341
	,MLBSENSORRANDOM=342
	,GROUND=343
	,DYNAMICOBJECT=344
	,STATICOBJECT=345


#line 215 "/usr/share/bison++/bison.h"
 /* enum token */
     }; /* end of enum declaration */
 #endif
public:
 int YY_MSLParser_PARSE(YY_MSLParser_PARSE_PARAM);
 virtual void YY_MSLParser_ERROR(char *msg) YY_MSLParser_ERROR_BODY;
 #ifdef YY_MSLParser_PURE
  #ifdef YY_MSLParser_LSP_NEEDED
   virtual int  YY_MSLParser_LEX(YY_MSLParser_STYPE *YY_MSLParser_LVAL,YY_MSLParser_LTYPE *YY_MSLParser_LLOC) YY_MSLParser_LEX_BODY;
  #else
   virtual int  YY_MSLParser_LEX(YY_MSLParser_STYPE *YY_MSLParser_LVAL) YY_MSLParser_LEX_BODY;
  #endif
 #else
  virtual int YY_MSLParser_LEX() YY_MSLParser_LEX_BODY;
  YY_MSLParser_STYPE YY_MSLParser_LVAL;
  #ifdef YY_MSLParser_LSP_NEEDED
   YY_MSLParser_LTYPE YY_MSLParser_LLOC;
  #endif
  int YY_MSLParser_NERRS;
  int YY_MSLParser_CHAR;
 #endif
 #if YY_MSLParser_DEBUG != 0
  public:
   int YY_MSLParser_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
 #endif
public:
 YY_MSLParser_CLASS(YY_MSLParser_CONSTRUCTOR_PARAM);
public:
 YY_MSLParser_MEMBERS 
};
/* other declare folow */
#endif


#if YY_MSLParser_COMPATIBILITY != 0
 /* backward compatibility */
 /* Removed due to bison problems
 /#ifndef YYSTYPE
 / #define YYSTYPE YY_MSLParser_STYPE
 /#endif*/

 #ifndef YYLTYPE
  #define YYLTYPE YY_MSLParser_LTYPE
 #endif
 #ifndef YYDEBUG
  #ifdef YY_MSLParser_DEBUG 
   #define YYDEBUG YY_MSLParser_DEBUG
  #endif
 #endif

#endif
/* END */

 #line 267 "/usr/share/bison++/bison.h"
#endif
