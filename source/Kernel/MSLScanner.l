%option c++
%option noyywrap

%{
#include <Kernel/MSLParser.h>
using namespace std;
%}

%x COMMENT

DIGIT [0-9]
ID [A-Za-z][A-Za-z0-9_]*
SIGN {-|+}

%%

"MAOWorld"						{return MSLParser::MAOWORLD;}
"MAOMark" 						{return MSLParser::MAOMARK;}
"MAOMarksGroup" 				{return MSLParser::MAOMARKSGROUP;}
"MAORenderable2DImage" 			{return MSLParser::MAORENDERABLE2DIMAGE;}
"MAORenderable2DText" 			{return MSLParser::MAORENDERABLE2DTEXT;}
"MAORenderable3DLine" 			{return MSLParser::MAORENDERABLE3DLINE;}
"MAORenderable3DModel" 			{return MSLParser::MAORENDERABLE3DMODEL;}
"MAORenderable3DPath" 			{return MSLParser::MAORENDERABLE3DPATH;}

"MLBActuatorAddDynamicObject" 	{return MSLParser::MLBACTUATORADDDYNAMICOBJECT;}
"MLBActuatorAng" 				{return MSLParser::MLBACTUATORANG;}
"MLBActuatorChangePose" 		{return MSLParser::MLBACTUATORCHANGEPOSE;}
"MLBActuatorDistance" 			{return MSLParser::MLBACTUATORDISTANCE;}
"MLBActuatorPathAddPoint" 		{return MSLParser::MLBACTUATORPATHADDPOINT;}
"MLBActuatorPathRemovePoints"	{return MSLParser::MLBACTUATORPATHREMOVEPOINTS;}
"MLBActuatorProperty" 			{return MSLParser::MLBACTUATORPROPERTY;}
"MLBActuatorQuitApp" 			{return MSLParser::MLBACTUATORQUITAPP;}
"MLBActuatorRandom" 			{return MSLParser::MLBACTUATORRANDOM;}
"MLBActuatorRelativePose" 		{return MSLParser::MLBACTUATORRELATIVEPOSE;}
"MLBActuatorSound" 				{return MSLParser::MLBACTUATORSOUND;}
"MLBActuatorVisibility" 		{return MSLParser::MLBACTUATORVISIBILITY;}
"MLBActuatorAnim" 				{return MSLParser::MLBACTUATORANIM;}

"MLBControllerAND" 				{return MSLParser::MLBCONTROLLERAND;}
"MLBControllerNAND" 			{return MSLParser::MLBCONTROLLERNAND;}
"MLBControllerNOR" 				{return MSLParser::MLBCONTROLLERNOR;}
"MLBControllerOR" 				{return MSLParser::MLBCONTROLLEROR;}
"MLBControllerScript"			{return MSLParser::MLBCONTROLLERSCRIPT;}

"MLBSensorActuator" 			{return MSLParser::MLBSENSORACTUATOR;}
"MLBSensorAlways" 				{return MSLParser::MLBSENSORALWAYS;}
"MLBSensorCollision"			{return MSLParser::MLBSENSORCOLLISION;}
"MLBSensorDelay" 				{return MSLParser::MLBSENSORDELAY;}
"MLBSensorKeyboard" 			{return MSLParser::MLBSENSORKEYBOARD;}
"MLBSensorNear"					{return MSLParser::MLBSENSORNEAR;}
"MLBSensorProperty" 			{return MSLParser::MLBSENSORPROPERTY;}
"MLBSensorRandom" 				{return MSLParser::MLBSENSORRANDOM;}

"Ground"						{return MSLParser::GROUND;}
"DynamicObject"					{return MSLParser::DYNAMICOBJECT;}
"StaticObject"					{return MSLParser::STATICOBJECT;}


"name" 							{return MSLParser::PARAM_NAME;}
"path"							{return MSLParser::PARAM_PATH;}
"size"							{return MSLParser::PARAM_SIZE;}
"marks"							{return MSLParser::PARAM_MARKS;}
"pos"							{return MSLParser::PARAM_POS;}
"color"							{return MSLParser::PARAM_COLOR;}
"width"							{return MSLParser::PARAM_WIDTH;}
"height"						{return MSLParser::PARAM_HEIGHT;}
"text"							{return MSLParser::PARAM_TEXT;}
"anim_type"						{return MSLParser::PARAM_ANIM_TYPE;}
"reference"						{return MSLParser::PARAM_REFERENCE;}
"mao"							{return MSLParser::PARAM_MAO;}
"time"							{return MSLParser::PARAM_TIME;}
"offset"						{return MSLParser::PARAM_OFFSET;}
"impulse"						{return MSLParser::PARAM_IMPULSE;}
"ang_axis"						{return MSLParser::PARAM_ANG_AXIS;}
"property"						{return MSLParser::PARAM_PROPERTY;}
"rot_type"						{return MSLParser::PARAM_ROT_TYPE;}
"rotation"						{return MSLParser::PARAM_ROTATION;}
"loc_type"						{return MSLParser::PARAM_LOC_TYPE;}
"location"						{return MSLParser::PARAM_LOCATION;}
"type"							{return MSLParser::PARAM_TYPE;}
"value"							{return MSLParser::PARAM_VALUE;}
"value1"						{return MSLParser::PARAM_VALUE1;}
"value2"						{return MSLParser::PARAM_VALUE2;}
"actuator"						{return MSLParser::PARAM_ACTUATOR;}
"key"							{return MSLParser::PARAM_KEY;}
"distance"						{return MSLParser::PARAM_DISTANCE;}
"probability"					{return MSLParser::PARAM_PROBABILITY;}
"inverse"						{return MSLParser::PARAM_INVERSE;}
"gravity"						{return MSLParser::PARAM_GRAVITY;}
"axis"							{return MSLParser::PARAM_AXIS;}
"mass"							{return MSLParser::PARAM_MASS;}
"shape"							{return MSLParser::PARAM_SHAPE;}
"shadows"						{return MSLParser::PARAM_SHADOWS;}
"sun"							{return MSLParser::PARAM_SUN;}

"int"							{return MSLParser::T_INTEGER;}
"float"							{return MSLParser::T_FLOAT;}
"bool"							{return MSLParser::T_BOOL;}
"string"						{return MSLParser::T_STRING;}
"pose"							{return MSLParser::T_POSE;}

"/*"							{BEGIN(COMMENT);}
<COMMENT>"*/"					{BEGIN(INITIAL);}
<COMMENT>[\t ]*				{}
<COMMENT>\n                                       {yylineno++;}
<COMMENT>.						{}

"->"							{return MSLParser::ARROW;}
"."								{return MSLParser::DOT;}
\"[^\n\t]*\"					{return MSLParser::STRING;}
"-"?{DIGIT}*"."{DIGIT}*		{return MSLParser::FLOAT;}
"-"?{DIGIT}*					{return MSLParser::INTEGER;}
"False"		 					{return MSLParser::BOOL;}
"True"							{return MSLParser::BOOL;}
{ID} 							{return MSLParser::IDENTIFIER;}
\n                                                      {yylineno++;}
[ \t]							{/*Ignore every blank space*/}
.								{/*Any other literal, just return it! */ return yytext[0];}
<<EOF>>							{yyterminate();}

%%
