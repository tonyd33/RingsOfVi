#pragma once
#include <Windows.h>
#include <map>
#include <list>
#include <string>
#include "action.h"

typedef void(*ActionHookFunc)(CAction* action);
typedef uintptr_t HookAddr;


struct ActionHook {
    enum ActionHookWhen{
        ACTIONHOOK_RUNBEFORE,
        ACTIONHOOK_RUNAFTER
    };
    ActionHookFunc hookFunc;
    ActionHookWhen when;
};

class Hookloader {
public:
    uintptr_t modBaseAddr;

    enum HLStatus {
        HL_OK,
        HL_ERR_UNKNOWN,
        HL_ERR_NOTFOUND,
    };

    Hookloader(uintptr_t modBaseAddr);

    HLStatus RegisterActionHook(ActionHook hook);

    HLStatus UnregisterActionHook(ActionHook hook);

private:
    std::map<std::string, HookAddr> actionHookNames;

    /* map from hook addresses in the ctf runtime to a list of callbacks to be run. */
    std::map<HookAddr, std::list<ActionHook>> actionHookMap;

    /* finds jumptables for actions */
    void InitActionHookAddrs();

    /* this is what first intercepts a hooked function. it then executes the callbacks sequentially. */
    void __cdecl HandleActionHook(Action* action);
};

namespace Event {
    enum ACTION_TYPE {
        ACTION_TYPE_PLAYER = -7,
        ACTION_TYPE_KEYBOARD = -6,
        ACTION_TYPE_CREATE = -5,
        ACTION_TYPE_TIMER = -4,
        ACTION_TYPE_GAME = -3,
        ACTION_TYPE_SPEAKER = -2,
        ACTION_TYPE_SYSTEM = -1,
        ACTION_TYPE_ACTIVE = 2,
        ACTION_TYPE_TEXT = 3,
        ACTION_TYPE_QUESTION = 4,
        ACTION_TYPE_SCORE = 5,
        ACTION_TYPE_LIVES = 6,
        ACTION_TYPE_COUNTER = 7,
        ACTION_TYPE_RTF = 8,
        ACTION_TYPE_SUBAPPLICATION = 9,
        /* arbitrary value. how the game actually runs extensions is by checking if num is in some range. if not, uses
           num to index into ACTION_EXT */
        ACTION_TYPE_EXT = 1390874,
    };

    enum ACTION_PLAYER {
        ACTION_PLAYER_SETSCORE = 0,
        ACTION_PLAYER_SETLIVES = 1,
        ACTION_PLAYER_IGNORECONTROLS = 2,
        ACTION_PLAYER_RESTORECONTROLS = 3,
        ACTION_PLAYER_ADDSCORE = 4,
        ACTION_PLAYER_ADDLIVES = 5,
        ACTION_PLAYER_SUBTRACTSCORE = 6,
        ACTION_PLAYER_SUBTRACTLIVES = 7,
        ACTION_PLAYER_CHANGECONTROLTYPE = 8,
        ACTION_PLAYER_CHANGEINPUTKEY = 9,
        ACTION_PLAYER_SETPLAYERNAME = 10,
    };

    enum ACTION_EXT {
        ACT_EXT_SETPOSITION = 1,
        ACT_EXT_SETX = 2,
        ACT_EXT_SETY = 3,
        ACT_EXT_STOP = 4,
        ACT_EXT_START = 5,
        ACT_EXT_SETSPEED = 6,
        ACT_EXT_SETMAXIMUMSPEED = 7,
        ACT_EXT_WRAP = 8,
        ACT_EXT_BOUNCE = 9,
        ACT_EXT_REVERSE = 10,
        ACT_EXT_NEXTMOVEMENT = 11,
        ACT_EXT_PREVIOUSMOVEMENT = 12,
        ACT_EXT_SELECTMOVEMENT = 13,
        ACT_EXT_LOOKAT = 14,
        ACT_EXT_STOPANIMATION = 15,
        ACT_EXT_STARTANIMATION = 16,
        ACT_EXT_FORCEANIMATION = 17,
        ACT_EXT_FORCEDIRECTION = 18,
        ACT_EXT_FORCESPEED = 19,
        ACT_EXT_RESTOREANIMATION = 20,
        ACT_EXT_RESTOREDIRECTION = 21,
        ACT_EXT_RESTORESPEED = 22,
        ACT_EXT_SETDIRECTION = 23,
        ACT_EXT_DESTROY = 24,
        ACT_EXT_SWAPPOSITION = 25,
        ACT_EXT_HIDE = 26,
        ACT_EXT_SHOW = 27,
        ACT_EXT_FLASHDURING = 28,
        ACT_EXT_SHOOT = 29,
        ACT_EXT_SHOOTTOWARD = 30,
        ACT_EXT_SETALTERABLEVALUE = 31,
        ACT_EXT_ADDTOALTERABLE = 32,
        ACT_EXT_SUBTRACTFROMALTERABLE = 33,
        ACT_EXT_SPREADVALUE = 34,
        ACT_EXT_ENABLEFLAG = 35,
        ACT_EXT_DISABLEFLAG = 36,
        ACT_EXT_TOGGLEFLAG = 37,
        ACT_EXT_SETINKEFFECT = 38,
        ACT_EXT_SETSEMITRANSPARENCY = 39,
        ACT_EXT_FORCEFRAME = 40,
        ACT_EXT_RESTOREFRAME = 41,
        ACT_EXT_SETACCELERATION = 42,
        ACT_EXT_SETDECELERATION = 43,
        ACT_EXT_SETROTATINGSPEED = 44,
        ACT_EXT_SETDIRECTIONS = 45,
        ACT_EXT_BRANCHNODE = 46,
        ACT_EXT_SETGRAVITY = 47,
        ACT_EXT_GOTONODE = 48,
        ACT_EXT_SETALTERABLESTRING = 49,
        ACT_EXT_SETFONTNAME = 50,
        ACT_EXT_SETFONTSIZE = 51,
        ACT_EXT_SETBOLD = 52,
        ACT_EXT_SETITALIC = 53,
        ACT_EXT_SETUNDERLINE = 54,
        ACT_EXT_SETSTRIKEOUT = 55,
        ACT_EXT_SETTEXTCOLOR = 56,
        ACT_EXT_BRINGTOFRONT = 57,
        ACT_EXT_BRINGTOBACK = 58,
        ACT_EXT_MOVEBEHIND = 59,
        ACT_EXT_MOVEINFRONT = 60,
        ACT_EXT_MOVETOLAYER = 61,
        ACT_EXT_ADDTODEBUGGER = 62,
        ACT_EXT_SETEFFECT = 63,
        ACT_EXT_SETEFFECTPARAMETER = 64,
        ACT_EXT_SETALPHACOEFFICIENT = 65,
        ACT_EXT_SETRGBCOEFFICIENT = 66,
        ACT_EXT_SETEFFECTIMAGE = 67,
        ACT_EXT_SETFRICTION = 68,
        ACT_EXT_SETELASTICITY = 69,
        ACT_EXT_APPLYIMPULSE = 70,
        ACT_EXT_APPLYANGULARIMPULSE = 71,
        ACT_EXT_APPLYFORCE = 72,
        ACT_EXT_APPLYTORQUE = 73,
        ACT_EXT_SETLINEARVELOCITY = 74,
        ACT_EXT_SETANGULARVELOCITY = 75,
        ACT_EXT_FOREACH = 76,
        ACT_EXT_FOREACHTWOOBJECTS = 77,
        ACT_EXT_STOPFORCE = 78,
        ACT_EXT_STOPTORQUE = 79,
        ACT_EXT_SETDENSITY = 80,
        ACT_EXT_SETGRAVITYSCALE = 81
    };
}