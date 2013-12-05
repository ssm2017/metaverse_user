// @version metaverseUser
// @package metaverse_user
// @copyright Copyright wene / ssm2017 Binder (C) 2013. All rights reserved.
// @license http://www.gnu.org/licenses/gpl-2.0.html GNU/GPL, see LICENSE.php
// metaverse_user is free software and parts of it may contain or be derived from the
// GNU General Public License or other free or open source software licenses.

integer reset_channel = 777;
// *********************************
//      STRINGS
// *********************************
// symbols
string _SYMBOL_RIGHT = "✔";
string _SYMBOL_WRONG = "✖";
string _SYMBOL_WARNING = "⚠";
string _SYMBOL_RESTART = "⟲";
string _SYMBOL_HOR_BAR_1 = "⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌⚌";
string _SYMBOL_HOR_BAR_2 = "⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊⚊";
string _SYMBOL_ARROW = "⤷";
// common
string _RESET = "Reset";
string _THE_SCRIPT_WILL_STOP = "The script will stop";
string _STOPPED = "Stopped";
string _READY = "Ready";
string _PLEASE_WAIT = "Please wait";
string _BUSY = "Busy";
string _TIME_ELAPSED =  "Time elapsed";
// check user
string _CHECKING_WEBSITE = "Checking the website";
string _YOU_HAVE_30_SECONDS_TO_ENTER_YOUR_CODE = "You have 30 seconds to enter your code";
// ============================================================
//      NOTHING SHOULD BE MODIFIED UNDER THIS LINE
// ============================================================
key owner;
key actual_user;
integer reset_listen_handler;
integer check_user_listen_handler;
// ********************
//      Constants
// ********************
// common
integer RESET = 70000;
integer SET_ERROR = 70016;
// http
integer HTTP_REQUEST_GET_URL = 70204;
integer HTTP_REQUEST_URL_SUCCESS = 70205;
// terminal
integer TERMINAL_SAVE = 70101;
integer TERMINAL_SAVED = 70102;
// user
integer CHECK_USER = 70305;
integer USER_VALID = 70306;
integer USER_NOT_VALID = 70307;
// *********************
//      FUNCTIONS
// *********************
// reset
reset() {
    llOwnerSay(_SYMBOL_HOR_BAR_2);
    llOwnerSay(_SYMBOL_RESTART+ " "+ _RESET);
    llMessageLinked(LINK_SET, RESET, "", NULL_KEY);
    llResetScript();
}
// error
error(string message) {
    llOwnerSay(_SYMBOL_WARNING+ " "+ message + "."+ _THE_SCRIPT_WILL_STOP);
    llSetText(message, <1.0,0.0,0.0>,1);
    llMessageLinked(LINK_SET, SET_ERROR, "", NULL_KEY);
}
// ***********************
//  INIT PROGRAM
// ***********************
default {
    on_rez(integer number) {
        reset();
    }

    state_entry() {
        owner = llGetOwner();
        llMessageLinked(LINK_THIS, HTTP_REQUEST_GET_URL, "", NULL_KEY);
        reset_listen_handler = llListen(reset_channel, "", llGetOwner(), "reset");
    }

    link_message(integer sender_num, integer num, string str, key id) {
        if (num == RESET) {
            llResetScript();
        }
        else if (num == HTTP_REQUEST_URL_SUCCESS) {
            llMessageLinked(LINK_THIS, TERMINAL_SAVE, "", NULL_KEY);
        }
        else if (num == TERMINAL_SAVED) {
            state run;
        }
        else if (num == SET_ERROR) {
            state idle;
        }
    }

    listen(integer channel, string name, key id, string message) {
        if (id == owner && message == "reset") {
            reset();
        }
    }

    changed(integer change) {
        if (change & CHANGED_REGION_START) {
          reset();
        }
        else if (change & 256) {
          reset();
        }
    }
}

// ************
//      RUN
// ************
state run {
    on_rez(integer change) {
        reset();
    }

    state_entry() {
        llSetText(_READY, <0.0,1.0,0.0>,1);
        reset_listen_handler = llListen(reset_channel, "", llGetOwner(), "reset");
    }

    touch_start(integer number) {
        actual_user = llDetectedKey(0);
        state check_user;
    }

    link_message(integer sender_num, integer num, string str, key id) {
        if (num == RESET) {
            llResetScript();
        }
        else if (num == SET_ERROR) {
            state idle;
        }
    }
    
    listen(integer channel, string name, key id, string message) {
        if (id == owner && message == "reset") {
            reset();
        }
    }

    changed(integer change) {
        if (change & CHANGED_REGION_START) {
          reset();
        }
        else if (change & 256) {
          reset();
        }
    }
}
// **************
//   Check user
// **************
state check_user {
    on_rez(integer change) {
        reset();
    }

    state_entry() {
        llSetText(_BUSY, <1.0,1.0,0.0>,1);
        reset_listen_handler = llListen(reset_channel, "", llGetOwner(), "reset");
        llWhisper(0, _YOU_HAVE_30_SECONDS_TO_ENTER_YOUR_CODE);
        check_user_listen_handler = llListen(0, "", actual_user, "");
        llSetTimerEvent(30);
    }

    link_message(integer sender_num, integer num, string str, key id) {
        if (num == RESET) {
            llResetScript();
        }
        else if (num == SET_ERROR) {
            state idle;
        }
        else if (num == USER_VALID || num == USER_NOT_VALID) {
            llWhisper(0, str);
            state run;
        }
    }

    listen(integer channel, string name, key id, string message) {
        if (id == owner && message == "reset") {
            reset();
        }
        else if (id == actual_user) {
            llListenRemove(check_user_listen_handler);
            llMessageLinked(LINK_THIS, CHECK_USER, message, actual_user);
            llWhisper(0, _CHECKING_WEBSITE);
            llWhisper(0, _PLEASE_WAIT);
        }
    }

    timer() {
        llWhisper(0, _TIME_ELAPSED);
        state run;
    }

    changed(integer change) {
        if (change & CHANGED_REGION_START) {
          reset();
        }
        else if (change & 256) {
          reset();
        }
    }
}
// **************
//      Error
// **************
state idle {
    on_rez(integer change) {
        reset();
    }

    state_entry() {
        llSetText(_STOPPED, <1.0,0.0,0.0>,1);
        reset_listen_handler = llListen(reset_channel, "", llGetOwner(), "reset");
    }

    link_message(integer sender_num, integer num, string str, key id) {
        if (num == RESET) {
            llResetScript();
        }
    }

    listen(integer channel, string name, key id, string message) {
        if (id == owner && message == "reset") {
            reset();
        }
    }

    changed(integer change) {
        if (change & CHANGED_REGION_START) {
          reset();
        }
        else if (change & 256) {
          reset();
        }
    }
}
