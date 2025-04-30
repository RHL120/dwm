/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 7};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Droid Sans Mono Slashed:size=8.5" };
static const char dmenufont[]       = "Droid Sans Mono Slashed:size=14";


static const char nord0[]  =  "#2E3440";
static const char nord3[]  =  "#4C566A";
static const char nord4[]  =  "#D8DEE9";
static const char nord6[]  =  "#ECEFF4";
static const char nord11[] =  "#BF616A";
static const char nord7[]  =  "#8FBCBB";

static const char *colors[][3]      = {
	/*               fg     bg    border   */
	[SchemeNorm] = { nord4, nord0, nord0 },
	[SchemeSel]  = { nord4, nord3,  nord7  },
	[SchemeKill]  = { nord4, nord11,  nord11  },
};

/* tagging */
static const char *tags[] = {"1:  ", "2:  ", "3:  ", "4:  ", "5:  ", "6:  ", "  7  ", "  8  ", "  9  "};

static const char *dock_title = "Onboard";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                            instance     title     tags mask   isfloating   monitor */
	{ "Gimp",                            NULL,       NULL,         0,          1,           -1 },
	{ "Zathura",                         NULL,	 NULL,       1 << 3,	   0,	        -1 },
	{ "mpv",                             NULL,       NULL,	     1 << 5,       1,	        -1 },
	{ "Brave-browser",                   NULL,       NULL,       1 << 1,       0,           -1 },
	{ "tor-browser-default",             NULL,       NULL,       1 << 1,       0,           -1 },
	{ "firefox",                         NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Onboard",                         NULL,       NULL,     0xFFFFFFFF,     1,           -1 },
	{ "Com.github.xournalpp.xournalpp",  NULL,       NULL,       1 << 4,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *lib_command[] = { "/home/rhl120/.local/bin/read_dox.sh", NULL };
static const char *vid_command[] = { "/home/rhl120/.local/bin/watch_vids.sh", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *youtube[] = { "watch_youtube.py" , NULL };
static const char *raisev[] = { "sh", "-c", "amixer set Master 5%+;echo refresh |nc localhost 6666", NULL};
static const char *lowerv[] = { "sh", "-c", "amixer set Master 5%-;echo refresh |nc localhost 6666", NULL};
static const char *lowerb[] = { "sh", "-c", "xbacklight -dec 5; echo refresh |nc localhost 6666", NULL};
static const char *raiseb[] = { "sh", "-c", "xbacklight -inc 5; echo refresh |nc localhost 6666", NULL};
static const char *screenboard[] = {"onboard", NULL};
static const char *xournalpp[] = {"xournalpp", NULL};
static const char *screencopysel[] = {"/home/rhl120/.local/bin/screenshot.sh", "copy", "-s", NULL};
static const char *screencopy[] = {"/home/rhl120/.local/bin/screenshot.sh", "copy", NULL};
static const char *screensel[] = {"/home/rhl120/.local/bin/screenshot.sh", "save", "-s", NULL};
static const char *screenshot[] = {"/home/rhl120/.local/bin/screenshot.sh", "save", NULL};
static const char *start[] = {"/home/rhl120/.local/bin/start.sh", NULL};
static const char *statusbutton4[] = {"sh", "-c", "echo button4 | nc localhost 6666", NULL};
static const char *statusbutton5[] = {"sh", "-c", "echo button5 | nc localhost 6666", NULL};
static const char *statusbutton6[] = {"sh", "-c", "echo button6 | nc localhost 6666", NULL};
static const char *statusbutton7[] = {"sh", "-c", "echo button7 | nc localhost 6666", NULL};

	


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XF86XK_AudioLowerVolume,      spawn,          {.v = lowerv } },
	{ 0,                            XF86XK_AudioRaiseVolume,      spawn,          {.v = raisev } },
	{ 0,                            XF86XK_MonBrightnessUp,       spawn,          {.v = raiseb } },
	{ 0,                            XF86XK_MonBrightnessDown,     spawn,          {.v = lowerb } },
	{ MODKEY|ShiftMask,             XK_x,                         spawn,          {.v = screencopysel } },
	{ MODKEY,                       XK_x,                         spawn,          {.v = screencopy } },
	{ MODKEY|ShiftMask,             XK_s,                         spawn,          {.v = screensel } },
	{ MODKEY,                       XK_s,                         spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,             XK_f,                         spawn,          {.v = browser } },
	{ MODKEY,                       XK_p,                         spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,                         spawn,          {.v = youtube } },
	{ MODKEY|ShiftMask,             XK_Return,                    spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,                         spawn,          {.v = lib_command } },
	{ MODKEY,                       XK_w,                         spawn,          {.v = vid_command } },
	{ MODKEY,                       XK_b,                         togglebar,      {0} },
	{ MODKEY,                       XK_j,                         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                    zoom,           {0} },
	{ MODKEY,                       XK_Tab,                       view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                         killclient,     {0} },
	{ MODKEY,                       XK_t,                         setlayout,      {.i = 0} },
	{ MODKEY,                       XK_f,                         setlayout,      {.i = 1} },
	{ MODKEY,                       XK_m,                         setlayout,      {.i = 2} },
	{ MODKEY,                       XK_space,                     setlayout,      {.i = -1} },
	{ MODKEY|ShiftMask,             XK_space,                     togglefloating, {0} },
	{ MODKEY,                       XK_0,                         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                    tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,                     setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,                     setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,                     setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,                     setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,                      quit,              {0} },
};

static unsigned int killer_button = Button1;

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function                    argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,                   {.i = -1} },
	{ ClkWinTitle,          0,              Button2,        zoom,                        {0} },
	{ ClkWinTitle,          0,              Button1,        toggle_clickkills,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,                       {.v = xournalpp } },
	{ ClkStatusText,        0,              Button4,        spawn,                       {.v = statusbutton4 } },
	{ ClkStatusText,        0,              Button5,        spawn,                       {.v = statusbutton5 } },
	{ ClkStatusText,        0,              6,              spawn,                       {.v = statusbutton6 } },
	{ ClkStatusText,        0,              7,              spawn,                       {.v = statusbutton7 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,                   {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,              {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,                 {0} },
	{ ClkTagBar,            0,              Button1,        view,                        {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,                  {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,                         {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,                   {0} },
};

static HotCorner hotcorners[] = {
	/* corner            width  height function     argument */ 
	{ CornerLowerRight,    10,     10,    spawn,   { .v = start } },
	{ CornerLowerLeft,     10,     10,    spawn,   { .v = screenboard }  },
};

//could be concatenated into  1 string seprated by ;s but that wouldn't look good
const char *cmds_auto_start[] = {
	"sxhkd &",
	"rhstatus &",
	"xwallpaper --stretch /home/rhl120/.local/share/wallpapers/wp.png &",
	"picom --no-fading-openclose &"
	"firefox &",
	"ibus-daemon -rxRd",
	"alacritty &",
	"alacritty &"
};
