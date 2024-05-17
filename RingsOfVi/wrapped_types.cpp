#include "pch.h"
#include <sstream>
#include "wrapped_types.h"

CAction::CAction(Action* action) {
    this->action = action;
}

std::vector<CParameter> CAction::GetParams() {
    std::vector<CParameter> params;
    Parameter* curr = (Parameter*)((uintptr_t)action + sizeof(Action));

    for (int i = 0; i < action->numParams; i++) {
        CParameter cCurr = CParameter(curr);
        params.push_back(cCurr);
        curr = cCurr.Next().param;
    }

    return params;
}

CCondition::CCondition(Condition* condition) {
    this->condition = condition;
}

std::vector<CParameter> CCondition::GetParams() {
    std::vector<CParameter> params;
    Parameter* curr = (Parameter*)((uintptr_t)condition + sizeof(Condition));

    for (int i = 0; i < condition->numParams; i++) {
        CParameter cCurr = CParameter(curr);
        params.push_back(cCurr);
        curr = cCurr.Next().param;
    }

    return params;
}

CParameter::CParameter(Parameter* param) {
    this->param = param;
}

CParameter CParameter::Next() {
    Parameter* nextParam = (Parameter*)((uintptr_t)param + param->evpSize);
    return CParameter(nextParam);
}

std::string CParameter::Name() {
    switch (param->evpCode) {
    case 1:
        return "ParamObject";
    case 2:
    case 42:
        return "Time";
    case 3:
    case 4:
    case 10:
    case 11:
    case 12:
    case 17:
    case 26:
    case 31:
    case 43:
    case 57:
    case 58:
    case 60:
    case 61:
        return "Short";
    case 6:
    case 7:
    case 35:
    case 36:
        return "Sample";
    case 9:
    case 21:
        return "Create";
    case 13:
        return "Every";
    case 14:
    case 44:
        return "KeyParameter";
    case 15:
    case 22:
    case 23:
    case 27:
    case 28:
    case 45:
    case 46:
    case 52:
    case 53:
    case 54:
    case 59:
    case 62:
        return "ExpressionParameter";
    case 16:
        return "Position";
    case 18:
        return "Shoot";
    case 19:
        return "Zone";
    case 24:
        return "Color";
    case 40:
        return "Filename";
    case 50:
        return "AlterableValue";
    case 32:
        return "Click";
    case 33:
        return "Program";
    case 55:
        return "ExtensionParameter";
    case 38:
        return "Group";
    case 39:
        return "GroupPointer";
    case 49:
        return "GlobalValue";
    case 41:
    case 64:
        return "StringParam";
    case 47:
    case 51:
        return "TwoShorts";
    case 67:
    case 70:
        return "IntParam";
    case 68:
        return "MultipleVariables";
    case 69:
        return "ChildEvent";
    default:
        return "unknown";
    };
}

CRunObject::CRunObject(RunObject* ro) {
    this->ro = ro;
}

CExpression::CExpression(Expression* expr) {
    this->expr = expr;
}

CExpression CExpression::Next() {
    Expression* nextExpr = (Expression*)((uintptr_t)expr + expr->size);
    return CExpression(nextExpr);
}

bool CExpression::IsEnd() {
    return expr->type == 0 && expr->num == 0;
}

std::string CExpression::Name() {
    int c = *(int*)expr;
    std::string exp;
    switch (c) {
        case 0x00000000:  // EXPL_END
            exp = "END";
            break;

        case 0x00020000:  // EXPL_PLUS:
            exp = "PLUS";
            break;

        case 0x00040000:  // EXPL_MOINS:
            exp = "MINUS";
            break;

        case 0x00060000:  // EXPL_MULT:
            exp = "MULT";
            break;

        case 0x00080000:  // EXPL_DIV:
            exp = "DIV";
            break;

        case 0x000A0000:  // EXPL_MOD
            exp = "MOD";
            break;

        case 0x000C0000:  // EXPL_POW
            exp = "POW";
            break;

        case 0x000E0000:  // EXPL_AND
            exp = "AND";
            break;

        case 0x00100000:  // EXPL_OR
            exp = "OR";
            break;

        case 0x00120000:  // EXPL_XOR
            exp = "XOR";
            break;

        case ((0 << 16) | 0xFFFF):  // EXP_LONG
            exp = "LONG";
            break;

        case ((1 << 16) | 0xFFFF):  // EXP_RANDOM
            exp = "RANDOM";
            break;

        case ((2 << 16) | 0xFFFF):  // EXP_VARGLO
            exp = "VARGLO";
            break;

        case ((3 << 16) | 0xFFFF):  // EXP_STRING
            exp = "STRING";
            break;

        case ((4 << 16) | 0xFFFF):  // EXP_STR
            exp = "STR";
            break;

        case ((5 << 16) | 0xFFFF):  // EXP_VAL
            exp = "VAL";
            break;

        case ((6 << 16) | 0xFFFF):  // EXP_DRIVE
            exp = "PATH";
            break;

        case ((7 << 16) | 0xFFFF):  // EXP_DIR
            exp = "PATH";
            break;

        case ((8 << 16) | 0xFFFF):  // EXP_PATH
            exp = "PATH";
            break;

        case ((10 << 16) | 0xFFFF):  // EXP_SIN
            exp = "SIN";
            break;

        case ((11 << 16) | 0xFFFF):  // EXP_COS
            exp = "COS";
            break;

        case ((12 << 16) | 0xFFFF):  // EXP_TAN
            exp = "TAN";
            break;

        case ((13 << 16) | 0xFFFF):  // EXP_SQR
            exp = "SQR";
            break;

        case ((14 << 16) | 0xFFFF):  // EXP_LOG
            exp = "LOG";
            break;

        case ((15 << 16) | 0xFFFF):  // EXP_LN
            exp = "LN";
            break;

        case ((16 << 16) | 0xFFFF):  // EXP_HEX
            exp = "HEX";
            break;

        case ((17 << 16) | 0xFFFF):  // EXP_BIN
            exp = "BIN";
            break;

        case ((18 << 16) | 0xFFFF):  // EXP_EXP
            exp = "EXP";
            break;

        case ((19 << 16) | 0xFFFF):  // EXP_LEFT
            exp = "LEFT";
            break;

        case ((20 << 16) | 0xFFFF):  // EXP_RIGHT
            exp = "RIGHT";
            break;

        case ((21 << 16) | 0xFFFF):  // EXP_MID
            exp = "MID";
            break;

        case ((22 << 16) | 0xFFFF):  // EXP_LEN
            exp = "LEN";
            break;

        case ((23 << 16) | 0xFFFF):  // EXP_DOUBLE
            exp = "DOUBLE";
            break;

        case ((24 << 16) | 0xFFFF):  // EXP_VARGLONAMED
            exp = "VARGLONAMED";
            break;

        case ((28 << 16) | 0xFFFF):  // EXP_INT
            exp = "INT";
            break;

        case ((29 << 16) | 0xFFFF):  // EXP_ABS
            exp = "ABS";
            break;

        case ((30 << 16) | 0xFFFF):  // EXP_CEIL
            exp = "CEIL";
            break;

        case ((31 << 16) | 0xFFFF):  // EXP_FLOOR
            exp = "FLOOR";
            break;

        case ((32 << 16) | 0xFFFF):  // EXP_ACOS
            exp = "ACOS";
            break;

        case ((33 << 16) | 0xFFFF):  // EXP_ASIN
            exp = "ASIN";
            break;

        case ((34 << 16) | 0xFFFF):  // EXP_ATAN
            exp = "ATAN";
            break;

        case ((35 << 16) | 0xFFFF):  // EXP_NOT
            exp = "NOT";
            break;

        case ((40 << 16) | 0xFFFF):  // EXP_MIN
            exp = "MIN";
            break;

        case ((41 << 16) | 0xFFFF):  // EXP_MAX
            exp = "MAX";
            break;

        case ((42 << 16) | 0xFFFF):  // EXP_GETRGB
            exp = "GETRGB";
            break;

        case ((43 << 16) | 0xFFFF):  // EXP_GETRED
            exp = "GETRED";
            break;

        case ((44 << 16) | 0xFFFF):  // EXP_GETGREEN
            exp = "GETGREEN";
            break;

        case ((45 << 16) | 0xFFFF):  // EXP_GETBLUE
            exp = "GETBLUE";
            break;

        case ((46 << 16) | 0xFFFF):  // EXP_LOOPINDEX
            exp = "LOOPINDEX";
            break;

        case ((47 << 16) | 0xFFFF):  // EXP_NEWLINE
            exp = "NEWLINE";
            break;

        case ((48 << 16) | 0xFFFF):  // EXP_ROUND
            exp = "ROUND";
            break;

        case ((49 << 16) | 0xFFFF):  // EXP_STRINGGLO
            exp = "STRINGGLO";
            break;

        case ((50 << 16) | 0xFFFF):  // EXP_STRINGGLONAMED
            exp = "STRINGGLONAMED";
            break;

        case ((51 << 16) | 0xFFFF):  // EXP_LOWER
            exp = "LOWER";
            break;

        case ((52 << 16) | 0xFFFF):  // EXP_UPPER
            exp = "UPPER";
            break;

        case ((53 << 16) | 0xFFFF):  // EXP_FIND
            exp = "FIND";
            break;

        case ((54 << 16) | 0xFFFF):  // EXP_REVERSEFIND
            exp = "REVERSEFIND";
            break;

        case ((58 << 16) | 0xFFFF):
            exp = "FLOATTOSTRING";
            break;

        case ((59 << 16) | 0xFFFF):
            exp = "ATAN2";
            break;

        case ((60 << 16) | 0xFFFF):
            exp = "ZERO";
            break;

        case ((61 << 16) | 0xFFFF):
            exp = "EMPTY";
            break;

        case ((67 << 16) | 0xFFFF):
            exp = "RUNTIMENAME";
            break;

        case ((-1 << 16) | 0xFFFF):  // EXP_PARENTH1
            exp = "PARENTH1";
            break;

        case ((-2 << 16) | 0xFFFF):  // EXP_PARENTH2
            exp = "PARENTH2";
            break;

        case ((-3 << 16) | 0xFFFF):  // EXP_VIRGULE
            exp = "VIRGULE";
            break;

        case ((0 << 16) | 0xFFFE):  // EXP_GETSAMPLEMAINVOL
            exp = "GETSAMPLEMAINVOL";
            break;

        case ((1 << 16) | 0xFFFE):  // EXP_GETSAMPLEVOL
            exp = "GETSAMPLEVOL";
            break;

        case ((2 << 16) | 0xFFFE):  // EXP_GETCHANNELVOL
            exp = "GETCHANNELVOL";
            break;

        case ((3 << 16) | 0xFFFE):  // EXP_GETSAMPLEMAINPAN
            exp = "GETSAMPLEMAINPAN";
            break;

        case ((4 << 16) | 0xFFFE):  // EXP_GETSAMPLEPAN
            exp = "GETSAMPLEPAN";
            break;

        case ((5 << 16) | 0xFFFE):  // EXP_GETCHANNELPAN
            exp = "GETCHANNELPAN";
            break;

        case ((8 << 16) | 0xFFFE):  // EXP_GETSAMPLEDUR
            exp = "GETSAMPLEDUR";
            break;

        case ((9 << 16) | 0xFFFE):  // EXP_GETCHANNELDUR
            exp = "GETCHANNELDUR";
            break;

        case ((10 << 16) | 0xFFFE):		// EXP_GETSAMPLEFREQ		
            exp = "GETSAMPLEFREQ";
            break;

        case ((11 << 16) | 0xFFFE):		// EXP_GETCHANNELFREQ		
            exp = "GETCHANNELFREQ";
            break;

        case ((0 << 16) | 0xFFFD):  // EXP_GAMLEVEL
            exp = "GAMLEVEL";
            break;

        case ((1 << 16) | 0xFFFD):  // EXP_GAMNPLAYER
            exp = "GAMNPLAYER";
            break;

        case ((2 << 16) | 0xFFFD):  // EXP_PLAYXLEFT
            exp = "PLAYXLEFT";
            break;

        case ((3 << 16) | 0xFFFD):  // EXP_PLAYXRIGHT
            exp = "PLAYXRIGHT";
            break;

        case ((4 << 16) | 0xFFFD):  // EXP_PLAYYTOP
            exp = "PLAYYTOP";
            break;

        case ((5 << 16) | 0xFFFD):  // EXP_PLAYYBOTTOM
            exp = "PLAYYBOTTOM";
            break;

        case ((6 << 16) | 0xFFFD):  // EXP_PLAYWIDTH
            exp = "PLAYWIDTH";
            break;

        case ((7 << 16) | 0xFFFD):  // EXP_PLAYHEIGHT
            exp = "PLAYHEIGHT";
            break;

        case ((8 << 16) | 0xFFFD):  // EXP_GAMLEVELNEW
            exp = "GAMLEVELNEW";
            break;

        case ((9 << 16) | 0xFFFD):  // EXP_GETCOLLISIONMASK
            exp = "GETCOLLISIONMASK";
            break;

        case ((10 << 16) | 0xFFFD):  // EXP_FRAMERATE
            exp = "FRAMERATE";
            break;

        case ((11 << 16) | 0xFFFD):  // EXP_GETVIRTUALWIDTH
            exp = "GETVIRTUALWIDTH";
            break;

        case ((12 << 16) | 0xFFFD):  // EXP_GETVIRTUALHEIGHT
            exp = "GETVIRTUALHEIGHT";
            break;

        case ((13 << 16) | 0xFFFD):  // EXP_GETFRAMEBKDCOLOR
            exp = "GETFRAMEBKDCOLOR";
            break;

        case ((14 << 16) | 0xFFFD):  // EXP_GRAPHICMODE
            exp = "ZERO";
            break;

        case ((15 << 16) | 0xFFFD):  // EXP_PIXELSHADERVERSION
            exp = "ZERO";
            break;

        case ((16 << 16) | 0xFFFD):  // EXP_FRAMEALPHACOEF
            exp = "ZERO";
            break;

        case ((17 << 16) | 0xFFFD):  // EXP_FRAMERGBCOEF
            exp = "FRAMERGBCOEF";
            break;

        case ((18 << 16) | 0xFFFD):  // EXP_FRAMEEFFECTPARAM
            exp = "ZERO";
            break;

        case ((0 << 16) | 0xFFFC):  // EXP_TIMVALUE
            exp = "TIMVALUE";
            break;

        case ((1 << 16) | 0xFFFC):  // EXP_TIMCENT
            exp = "TIMCENT";
            break;

        case ((2 << 16) | 0xFFFC):  // EXP_TIMSECONDS
            exp = "TIMSECONDS";
            break;

        case ((3 << 16) | 0xFFFC):  // EXP_TIMHOURS
            exp = "TIMHOURS";
            break;

        case ((4 << 16) | 0xFFFC):  // EXP_TIMMINITS
            exp = "TIMMINITS";
            break;

        case ((0 << 16) | 0xFFFA):  // EXP_XMOUSE
            exp = "XMOUSE";
            break;

        case ((1 << 16) | 0xFFFA):  // EXP_YMOUSE
            exp = "YMOUSE";
            break;

        case ((2 << 16) | 0xFFFA):  // EXP_YMOUSE
            exp = "MOUSEWHEELDELTA";
            break;

        case ((0 << 16) | 0xFFF9):  // EXP_PLASCORE
            exp = "PLASCORE";
            break;

        case ((1 << 16) | 0xFFF9):  // EXP_PLALIVES
            exp = "PLALIVES";
            break;

        case ((2 << 16) | 0xFFF9):  // EXP_GETINPUT
            exp = "GETINPUT";
            break;

        case ((3 << 16) | 0xFFF9):  // EXP_GETINPUTKEY
            exp = "GETINPUTKEY";
            break;

        case ((4 << 16) | 0xFFF9):  // EXP_GETPLAYERNAME
            exp = "GETPLAYERNAME";
            break;

        case ((0 << 16) | 0xFFFB):  // EXP_CRENUMBERALL
            exp = "CRENUMBERALL";
            break;

        case (((80 + 0) << 16) | 3):  // EXP_STRNUMBER
            exp = "STRNUMBER";
            break;

        case (((80 + 1) << 16) | 3):  // EXP_STRGETCURRENT
            exp = "STRGETCURRENT";
            break;

        case (((80 + 2) << 16) | 3):  // EXP_STRGETNUMBER
            exp = "STRGETNUMBER";
            break;

        case (((80 + 3) << 16) | 3):  // EXP_STRGETNUMERIC
            exp = "STRGETNUMERIC";
            break;

        case (((80 + 4) << 16) | 3):  // EXP_STRGETNPARA
            exp = "STRGETNPARA";
            break;

        case ((80 + 0) << 16 | 2):  // EXP_GETRGBAT
            exp = "GETRGBAT";
            break;

        case ((80 + 1) << 16 | 2):  // EXP_GETSCALEX
            exp = "GETSCALEX";
            break;

        case ((80 + 2) << 16 | 2):  // EXP_GETSCALEY
            exp = "GETSCALEY";
            break;

        case ((80 + 3) << 16 | 2):  // EXP_GETANGLE
            exp = "GETANGLE";
            break;

        case (((80 + 0) << 16) | 7):  // EXP_CVALUE
            exp = "CVALUE";
            break;

        case (((80 + 1) << 16) | 7):  // EXP_CGETMIN
            exp = "CGETMIN";
            break;

        case (((80 + 2) << 16) | 7):  // EXP_CGETMAX
            exp = "CGETMAX";
            break;

        case (((80 + 3) << 16) | 7):  // EXP_CGETCOLOR1
            exp = "CGETCOLOR1";
            break;

        case (((80 + 4) << 16) | 7):  // EXP_CGETCOLOR2
            exp = "CGETCOLOR2";
            break;

        case (((80 + 0) << 16) | 9):  // EXP_CCAGETFRAMENUMBER
            exp = "CCAGETFRAMENUMBER";
            break;

        case (((80 + 1) << 16) | 9):  // EXP_CCAGETGLOBALVALUE
            exp = "CCAGETGLOBALVALUE";
            break;

        case (((80 + 2) << 16) | 9):  // EXP_CCAGETGLOBALSTRING
            exp = "CCAGETGLOBALSTRING";
            break;

        default:
            switch (c & (0xFFFF0000))
            {
                case (1 << 16):  // EXP_EXTYSPR
                    exp = "EXTYSPR";
                    break;

                case (2 << 16):  // EXP_EXTISPR
                    exp = "EXTISPR";
                    break;

                case (3 << 16):  // EXP_EXTSPEED
                    exp = "EXTSPEED";
                    break;

                case (4 << 16):  // EXP_EXTACC
                    exp = "EXTACC";
                    break;

                case (5 << 16):  // EXP_EXTDEC
                    exp = "EXTDEC";
                    break;

                case (6 << 16):  // EXP_EXTDIR
                    exp = "EXTDIR";
                    break;

                case (7 << 16):  // EXP_EXTXLEFT
                    exp = "EXTXLEFT";
                    break;

                case (8 << 16):  // EXP_EXTXRIGHT
                    exp = "EXTXRIGHT";
                    break;

                case (9 << 16):  // EXP_EXTYTOP
                    exp = "EXTYTOP";
                    break;

                case (10 << 16):  // EXP_EXTYBOTTOM
                    exp = "EXTYBOTTOM";
                    break;

                case (11 << 16):  // EXP_EXTXSPR
                    exp = "EXTXSPR";
                    break;

                case (12 << 16):  // EXP_EXTIDENTIFIER
                    exp = "EXTIDENTIFIER";
                    break;

                case (13 << 16):  // EXP_EXTFLAG
                    exp = "EXTFLAG";
                    break;

                case (14 << 16):  // EXP_EXTNANI
                    exp = "EXTNANI";
                    break;

                case (15 << 16):  // EXP_EXTNOBJECTS
                    exp = "EXTNOBJECTS";
                    break;

                case (16 << 16):  // EXP_EXTVAR
                    exp = "EXTVAR";
                    break;

                case (17 << 16):  // EXP_EXTGETSEMITRANSPARENCY
                    exp = "EXTGETSEMITRANSPARENCY";
                    break;

                case (18 << 16):  // EXP_EXTNMOVE
                    exp = "EXTNMOVE";
                    break;

                case (19 << 16):  // EXP_EXTVARSTRING
                    exp = "EXTVARSTRING";
                    break;

                case (20 << 16):  // EXP_EXTGETFONTNAME
                    exp = "EXTGETFONTNAME";
                    break;

                case (21 << 16):  // EXP_EXTGETFONTSIZE
                    exp = "EXTGETFONTSIZE";
                    break;

                case (22 << 16):  // EXP_EXTGETFONTCOLOR
                    exp = "EXTGETFONTCOLOR";
                    break;

                case (23 << 16):  // EXP_EXTGETLAYER
                    exp = "EXTGETLAYER";
                    break;

                case (24 << 16):  // EXP_EXTGETGRAVITY
                    exp = "EXTGETGRAVITY";
                    break;

                case (25 << 16):  // EXP_EXTXAP
                    exp = "EXTXAP";
                    break;

                case (26 << 16):  // EXP_EXTYAP
                    exp = "EXTYAP";
                    break;

                case (27 << 16):  // EXP_EXTALPHACOEF
                    exp = "EXTALPHACOEF";
                    break;

                case (28 << 16):  // EXP_EXTRGBCOEF
                    exp = "EXTRGBCOEF";
                    break;

                case (29 << 16):  // EXP_EXTEFFECTPARAM
                    exp = "ZERO";
                    break;

                case (30 << 16):  // EXP_VARBYINDEX
                    exp = "EXTVARBYINDEX";
                    break;

                case (31 << 16):  // EXP_VARBYINDEX
                    exp = "EXTVARSTRINGBYINDEX";
                    break;

                default:
                    exp = "EXTENSION"; // EXTENSION
                    break;

            }
            break;

    }
    return exp;
}

std::string CExpression::PrettyName() {
    int c = *(int*)expr;
    std::stringstream exp;
    switch (c) {
        case 0x00000000:  // EXPL_END
            exp << ";";
            break;

        case 0x00020000:  // EXPL_PLUS:
            exp << "+";
            break;

        case 0x00040000:  // EXPL_MOINS:
            exp << "-";
            break;

        case 0x00060000:  // EXPL_MULT:
            exp << "*";
            break;

        case 0x00080000:  // EXPL_DIV:
            exp << "/";
            break;

        case 0x000A0000:  // EXPL_MOD
            exp << "%";
            break;

        case 0x000C0000:  // EXPL_POW
            exp << "**";
            break;

        case 0x000E0000:  // EXPL_AND
            exp << "&";
            break;

        case 0x00100000:  // EXPL_OR
            exp << "|";
            break;

        case 0x00120000:  // EXPL_XOR
            exp << "^";
            break;

        case ((0 << 16) | 0xFFFF):  // EXP_LONG
            exp << "(LONG)";
            exp << std::to_string(*(int*)((uintptr_t)expr+6));
            break;

        case ((1 << 16) | 0xFFFF):  // EXP_RANDOM
            exp << "RAND";
            break;

        case ((2 << 16) | 0xFFFF):  // EXP_VARGLO
            exp << "VARGLO";
            break;

        case ((3 << 16) | 0xFFFF):{ // EXP_STRING
            char* curr = (char*)((uintptr_t)expr + 6);
            while (*curr != 0) {
                exp << *curr;
                curr++;
            }
            break;
        }

        case ((4 << 16) | 0xFFFF):  // EXP_STR
            exp << "(STR)";
            break;

        case ((5 << 16) | 0xFFFF):  // EXP_VAL
            exp << "(VAL)";
            break;

        case ((6 << 16) | 0xFFFF):  // EXP_DRIVE
            exp << "PATH";
            break;

        case ((7 << 16) | 0xFFFF):  // EXP_DIR
            exp << "PATH";
            break;

        case ((8 << 16) | 0xFFFF):  // EXP_PATH
            exp << "PATH";
            break;

        case ((10 << 16) | 0xFFFF):  // EXP_SIN
            exp << "SIN";
            break;

        case ((11 << 16) | 0xFFFF):  // EXP_COS
            exp << "COS";
            break;

        case ((12 << 16) | 0xFFFF):  // EXP_TAN
            exp << "TAN";
            break;

        case ((13 << 16) | 0xFFFF):  // EXP_SQR
            exp << "SQR";
            break;

        case ((14 << 16) | 0xFFFF):  // EXP_LOG
            exp << "LOG";
            break;

        case ((15 << 16) | 0xFFFF):  // EXP_LN
            exp << "LN";
            break;

        case ((16 << 16) | 0xFFFF):  // EXP_HEX
            exp << "HEX";
            break;

        case ((17 << 16) | 0xFFFF):  // EXP_BIN
            exp << "BIN";
            break;

        case ((18 << 16) | 0xFFFF):  // EXP_EXP
            exp << "e^";
            break;

        case ((19 << 16) | 0xFFFF):  // EXP_LEFT
            exp << "LEFT";
            break;

        case ((20 << 16) | 0xFFFF):  // EXP_RIGHT
            exp << "RIGHT";
            break;

        case ((21 << 16) | 0xFFFF):  // EXP_MID
            exp << "MID";
            break;

        case ((22 << 16) | 0xFFFF):  // EXP_LEN
            exp << "LEN";
            break;

        case ((23 << 16) | 0xFFFF):  // EXP_DOUBLE
            exp << std::to_string(*(double*)((uintptr_t)expr+6));
            break;

        case ((24 << 16) | 0xFFFF):  // EXP_VARGLONAMED
            exp << "VARGLONAMED";
            // +4 parce que Oi et OIlist qui servent a rien
            exp << std::to_string(*(short*)((uintptr_t)expr+6+4));
            break;

        case ((28 << 16) | 0xFFFF):  // EXP_INT
            exp << "(INT)";
            break;

        case ((29 << 16) | 0xFFFF):  // EXP_ABS
            exp << "ABS";
            break;

        case ((30 << 16) | 0xFFFF):  // EXP_CEIL
            exp << "CEIL";
            break;

        case ((31 << 16) | 0xFFFF):  // EXP_FLOOR
            exp << "FLOOR";
            break;

        case ((32 << 16) | 0xFFFF):  // EXP_ACOS
            exp << "ACOS";
            break;

        case ((33 << 16) | 0xFFFF):  // EXP_ASIN
            exp << "ASIN";
            break;

        case ((34 << 16) | 0xFFFF):  // EXP_ATAN
            exp << "ATAN";
            break;

        case ((35 << 16) | 0xFFFF):  // EXP_NOT
            exp << "!";
            break;

        case ((40 << 16) | 0xFFFF):  // EXP_MIN
            exp << "MIN";
            break;

        case ((41 << 16) | 0xFFFF):  // EXP_MAX
            exp << "MAX";
            break;

        case ((42 << 16) | 0xFFFF):  // EXP_GETRGB
            exp << "GETRGB";
            break;

        case ((43 << 16) | 0xFFFF):  // EXP_GETRED
            exp << "GETRED";
            break;

        case ((44 << 16) | 0xFFFF):  // EXP_GETGREEN
            exp << "GETGREEN";
            break;

        case ((45 << 16) | 0xFFFF):  // EXP_GETBLUE
            exp << "GETBLUE";
            break;

        case ((46 << 16) | 0xFFFF):  // EXP_LOOPINDEX
            exp << "LOOPINDEX";
            break;

        case ((47 << 16) | 0xFFFF):  // EXP_NEWLINE
            exp << "NL\n";
            break;

        case ((48 << 16) | 0xFFFF):  // EXP_ROUND
            exp << "ROUND";
            break;

        case ((49 << 16) | 0xFFFF):  // EXP_STRINGGLO
            exp << "STRINGGLO";
            break;

        case ((50 << 16) | 0xFFFF):  // EXP_STRINGGLONAMED
            exp << "STRINGGLONAMED";
            break;

        case ((51 << 16) | 0xFFFF):  // EXP_LOWER
            exp << "LOWER";
            break;

        case ((52 << 16) | 0xFFFF):  // EXP_UPPER
            exp << "UPPER";
            break;

        case ((53 << 16) | 0xFFFF):  // EXP_FIND
            exp << "FIND";
            break;

        case ((54 << 16) | 0xFFFF):  // EXP_REVERSEFIND
            exp << "REVERSEFIND";
            break;

        case ((58 << 16) | 0xFFFF):
            exp << "FLOATTOSTRING";
            break;

        case ((59 << 16) | 0xFFFF):
            exp << "ATAN2";
            break;

        case ((60 << 16) | 0xFFFF):
            exp << "ZERO";
            break;

        case ((61 << 16) | 0xFFFF):
            exp << "EMPTY";
            break;

        case ((67 << 16) | 0xFFFF):
            exp << "RUNTIMENAME";
            break;

        case ((-1 << 16) | 0xFFFF):  // EXP_PARENTH1
            exp << "(";
            break;

        case ((-2 << 16) | 0xFFFF):  // EXP_PARENTH2
            exp << ")";
            break;

        case ((-3 << 16) | 0xFFFF):  // EXP_VIRGULE
            exp << "VIRGULE";
            break;

        case ((0 << 16) | 0xFFFE):  // EXP_GETSAMPLEMAINVOL
            exp << "GETSAMPLEMAINVOL";
            break;

        case ((1 << 16) | 0xFFFE):  // EXP_GETSAMPLEVOL
            exp << "GETSAMPLEVOL";
            break;

        case ((2 << 16) | 0xFFFE):  // EXP_GETCHANNELVOL
            exp << "GETCHANNELVOL";
            break;

        case ((3 << 16) | 0xFFFE):  // EXP_GETSAMPLEMAINPAN
            exp << "GETSAMPLEMAINPAN";
            break;

        case ((4 << 16) | 0xFFFE):  // EXP_GETSAMPLEPAN
            exp << "GETSAMPLEPAN";
            break;

        case ((5 << 16) | 0xFFFE):  // EXP_GETCHANNELPAN
            exp << "GETCHANNELPAN";
            break;

        case ((8 << 16) | 0xFFFE):  // EXP_GETSAMPLEDUR
            exp << "GETSAMPLEDUR";
            break;

        case ((9 << 16) | 0xFFFE):  // EXP_GETCHANNELDUR
            exp << "GETCHANNELDUR";
            break;

        case ((10 << 16) | 0xFFFE):		// EXP_GETSAMPLEFREQ		
            exp << "GETSAMPLEFREQ";
            break;

        case ((11 << 16) | 0xFFFE):		// EXP_GETCHANNELFREQ		
            exp << "GETCHANNELFREQ";
            break;

        case ((0 << 16) | 0xFFFD):  // EXP_GAMLEVEL
            exp << "GAMLEVEL";
            break;

        case ((1 << 16) | 0xFFFD):  // EXP_GAMNPLAYER
            exp << "GAMNPLAYER";
            break;

        case ((2 << 16) | 0xFFFD):  // EXP_PLAYXLEFT
            exp << "PLAYXLEFT";
            break;

        case ((3 << 16) | 0xFFFD):  // EXP_PLAYXRIGHT
            exp << "PLAYXRIGHT";
            break;

        case ((4 << 16) | 0xFFFD):  // EXP_PLAYYTOP
            exp << "PLAYYTOP";
            break;

        case ((5 << 16) | 0xFFFD):  // EXP_PLAYYBOTTOM
            exp << "PLAYYBOTTOM";
            break;

        case ((6 << 16) | 0xFFFD):  // EXP_PLAYWIDTH
            exp << "PLAYWIDTH";
            break;

        case ((7 << 16) | 0xFFFD):  // EXP_PLAYHEIGHT
            exp << "PLAYHEIGHT";
            break;

        case ((8 << 16) | 0xFFFD):  // EXP_GAMLEVELNEW
            exp << "GAMLEVELNEW";
            break;

        case ((9 << 16) | 0xFFFD):  // EXP_GETCOLLISIONMASK
            exp << "GETCOLLISIONMASK";
            break;

        case ((10 << 16) | 0xFFFD):  // EXP_FRAMERATE
            exp << "FRAMERATE";
            break;

        case ((11 << 16) | 0xFFFD):  // EXP_GETVIRTUALWIDTH
            exp << "GETVIRTUALWIDTH";
            break;

        case ((12 << 16) | 0xFFFD):  // EXP_GETVIRTUALHEIGHT
            exp << "GETVIRTUALHEIGHT";
            break;

        case ((13 << 16) | 0xFFFD):  // EXP_GETFRAMEBKDCOLOR
            exp << "GETFRAMEBKDCOLOR";
            break;

        case ((14 << 16) | 0xFFFD):  // EXP_GRAPHICMODE
            exp << "ZERO";
            break;

        case ((15 << 16) | 0xFFFD):  // EXP_PIXELSHADERVERSION
            exp << "ZERO";
            break;

        case ((16 << 16) | 0xFFFD):  // EXP_FRAMEALPHACOEF
            exp << "ZERO";
            break;

        case ((17 << 16) | 0xFFFD):  // EXP_FRAMERGBCOEF
            exp << "FRAMERGBCOEF";
            break;

        case ((18 << 16) | 0xFFFD):  // EXP_FRAMEEFFECTPARAM
            exp << "ZERO";
            break;

        case ((0 << 16) | 0xFFFC):  // EXP_TIMVALUE
            exp << "TIMVALUE";
            break;

        case ((1 << 16) | 0xFFFC):  // EXP_TIMCENT
            exp << "TIMCENT";
            break;

        case ((2 << 16) | 0xFFFC):  // EXP_TIMSECONDS
            exp << "TIMSECONDS";
            break;

        case ((3 << 16) | 0xFFFC):  // EXP_TIMHOURS
            exp << "TIMHOURS";
            break;

        case ((4 << 16) | 0xFFFC):  // EXP_TIMMINITS
            exp << "TIMMINITS";
            break;

        case ((0 << 16) | 0xFFFA):  // EXP_XMOUSE
            exp << "XMOUSE";
            break;

        case ((1 << 16) | 0xFFFA):  // EXP_YMOUSE
            exp << "YMOUSE";
            break;

        case ((2 << 16) | 0xFFFA):  // EXP_YMOUSE
            exp << "MOUSEWHEELDELTA";
            break;

        case ((0 << 16) | 0xFFF9):  // EXP_PLASCORE
            exp << "PLASCORE";
            break;

        case ((1 << 16) | 0xFFF9):  // EXP_PLALIVES
            exp << "PLALIVES";
            break;

        case ((2 << 16) | 0xFFF9):  // EXP_GETINPUT
            exp << "GETINPUT";
            break;

        case ((3 << 16) | 0xFFF9):  // EXP_GETINPUTKEY
            exp << "GETINPUTKEY";
            break;

        case ((4 << 16) | 0xFFF9):  // EXP_GETPLAYERNAME
            exp << "GETPLAYERNAME";
            break;

        case ((0 << 16) | 0xFFFB):  // EXP_CRENUMBERALL
            exp << "CRENUMBERALL";
            break;

        case (((80 + 0) << 16) | 3):  // EXP_STRNUMBER
            exp << "STRNUMBER";
            break;

        case (((80 + 1) << 16) | 3):  // EXP_STRGETCURRENT
            exp << "STRGETCURRENT";
            break;

        case (((80 + 2) << 16) | 3):  // EXP_STRGETNUMBER
            exp << "STRGETNUMBER";
            break;

        case (((80 + 3) << 16) | 3):  // EXP_STRGETNUMERIC
            exp << "STRGETNUMERIC";
            break;

        case (((80 + 4) << 16) | 3):  // EXP_STRGETNPARA
            exp << "STRGETNPARA";
            break;

        case ((80 + 0) << 16 | 2):  // EXP_GETRGBAT
            exp << "GETRGBAT";
            break;

        case ((80 + 1) << 16 | 2):  // EXP_GETSCALEX
            exp << "GETSCALEX";
            break;

        case ((80 + 2) << 16 | 2):  // EXP_GETSCALEY
            exp << "GETSCALEY";
            break;

        case ((80 + 3) << 16 | 2):  // EXP_GETANGLE
            exp << "GETANGLE";
            break;

        case (((80 + 0) << 16) | 7):  // EXP_CVALUE
            exp << "CVALUE";
            break;

        case (((80 + 1) << 16) | 7):  // EXP_CGETMIN
            exp << "CGETMIN";
            break;

        case (((80 + 2) << 16) | 7):  // EXP_CGETMAX
            exp << "CGETMAX";
            break;

        case (((80 + 3) << 16) | 7):  // EXP_CGETCOLOR1
            exp << "CGETCOLOR1";
            break;

        case (((80 + 4) << 16) | 7):  // EXP_CGETCOLOR2
            exp << "CGETCOLOR2";
            break;

        case (((80 + 0) << 16) | 9):  // EXP_CCAGETFRAMENUMBER
            exp << "CCAGETFRAMENUMBER";
            break;

        case (((80 + 1) << 16) | 9):  // EXP_CCAGETGLOBALVALUE
            exp << "CCAGETGLOBALVALUE";
            break;

        case (((80 + 2) << 16) | 9):  // EXP_CCAGETGLOBALSTRING
            exp << "CCAGETGLOBALSTRING";
            break;

        default:
            switch (c & (0xFFFF0000))
            {
                case (1 << 16):  // EXP_EXTYSPR
                    exp << "EXTYSPR";
                    break;

                case (2 << 16):  // EXP_EXTISPR
                    exp << "EXTISPR";
                    break;

                case (3 << 16):  // EXP_EXTSPEED
                    exp << "EXTSPEED";
                    break;

                case (4 << 16):  // EXP_EXTACC
                    exp << "EXTACC";
                    break;

                case (5 << 16):  // EXP_EXTDEC
                    exp << "EXTDEC";
                    break;

                case (6 << 16):  // EXP_EXTDIR
                    exp << "EXTDIR";
                    break;

                case (7 << 16):  // EXP_EXTXLEFT
                    exp << "EXTXLEFT";
                    break;

                case (8 << 16):  // EXP_EXTXRIGHT
                    exp << "EXTXRIGHT";
                    break;

                case (9 << 16):  // EXP_EXTYTOP
                    exp << "EXTYTOP";
                    break;

                case (10 << 16):  // EXP_EXTYBOTTOM
                    exp << "EXTYBOTTOM";
                    break;

                case (11 << 16):  // EXP_EXTXSPR
                    exp << "EXTXSPR";
                    break;

                case (12 << 16):  // EXP_EXTIDENTIFIER
                    exp << "EXTIDENTIFIER";
                    break;

                case (13 << 16):  // EXP_EXTFLAG
                    exp << "EXTFLAG";
                    break;

                case (14 << 16):  // EXP_EXTNANI
                    exp << "EXTNANI";
                    break;

                case (15 << 16):  // EXP_EXTNOBJECTS
                    exp << "EXTNOBJECTS";
                    break;

                case (16 << 16):  // EXP_EXTVAR
                    exp << "EXTVAR";
                    break;

                case (17 << 16):  // EXP_EXTGETSEMITRANSPARENCY
                    exp << "EXTGETSEMITRANSPARENCY";
                    break;

                case (18 << 16):  // EXP_EXTNMOVE
                    exp << "EXTNMOVE";
                    break;

                case (19 << 16):  // EXP_EXTVARSTRING
                    exp << "EXTVARSTRING";
                    break;

                case (20 << 16):  // EXP_EXTGETFONTNAME
                    exp << "EXTGETFONTNAME";
                    break;

                case (21 << 16):  // EXP_EXTGETFONTSIZE
                    exp << "EXTGETFONTSIZE";
                    break;

                case (22 << 16):  // EXP_EXTGETFONTCOLOR
                    exp << "EXTGETFONTCOLOR";
                    break;

                case (23 << 16):  // EXP_EXTGETLAYER
                    exp << "EXTGETLAYER";
                    break;

                case (24 << 16):  // EXP_EXTGETGRAVITY
                    exp << "EXTGETGRAVITY";
                    break;

                case (25 << 16):  // EXP_EXTXAP
                    exp << "EXTXAP";
                    break;

                case (26 << 16):  // EXP_EXTYAP
                    exp << "EXTYAP";
                    break;

                case (27 << 16):  // EXP_EXTALPHACOEF
                    exp << "EXTALPHACOEF";
                    break;

                case (28 << 16):  // EXP_EXTRGBCOEF
                    exp << "EXTRGBCOEF";
                    break;

                case (29 << 16):  // EXP_EXTEFFECTPARAM
                    exp << "ZERO";
                    break;

                case (30 << 16):  // EXP_VARBYINDEX
                    exp << "EXTVARBYINDEX";
                    break;

                case (31 << 16):  // EXP_VARBYINDEX
                    exp << "EXTVARSTRINGBYINDEX";
                    break;

                default:
                    exp << "EXTENSION"; // EXTENSION
                    break;

            }
            break;
    }
    short type = (short)c;

    if (type >= 2 || type == 7) {
        exp << "(";
        exp << "oi:" << std::to_string(*(short*)((uintptr_t)expr + 6));
        exp << "," << "oiList:" << std::to_string(*(short*)((uintptr_t)expr + 8));
        switch (c & ((int)0xFFFF0000))
        {
            case (16 << 16):  // EXP_EXTVAR
            case (19 << 16):  // EXP_EXTVARSTRING
                exp << "," << "num:" << std::to_string(*(short*)((uintptr_t)expr + 10));
                break;

            default:
                break;

        }
        exp << ")";
    }
    return exp.str();
}

CExpressionParameter::CExpressionParameter(ExpressionParameter* exprParam) {
    this->exprParam = exprParam;
}

std::vector<CExpression> CExpressionParameter::GetExpressions() {
    std::vector<CExpression> exprs;
    Expression* curr = &exprParam->expression;
    CExpression cCurr = CExpression(curr);

    while (!cCurr.IsEnd()) {
        exprs.push_back(cCurr);
        cCurr = cCurr.Next();
    }

    return exprs;
}
