/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "NotoSansMono:size=10","JoyPixels:size=10" };
static const char dmenufont[]       = "NotoSansMono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#ff0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  iscentered isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,         0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,         0,          0,           1,        -1 }, /* xev */
        { "st-256color",   NULL,     "/home/aarnar/Programs/scripts/snipshot.sh", 0, 0, 1, 0, 1,        -1 }, 
        { "st-256color",   NULL,     "/home/aarnar/Programs/scripts/scrshot.sh",  0, 0, 1, 0, 1,        -1 },        
    /*  { "st-256color",   NULL,     "ranger", 0,         0,         1,          0,           1,        -1 }, */
    /*  { "st-256color",   NULL,     "tremc",  0,         0,         1,          0,           1,        -1,}, */
    /*  { "st-256color",   NULL,     "ncmpcpp",0,         0,         1,          0,           1,        -1,}, */
        { "st-256color",   NULL,     "nmtui",  0,         0,         1,          0,           1,        -1,},
	{ "tabbed",        "tabbed",  NULL,    0,         0,         0,          1,           0,        -1 },
	{ NULL,            NULL,     "sxiv",   0,         0,         0,          0,           1,        -1 }, 
	{ "feh",           NULL,      NULL,    0,         0,         0,          0,           1,        -1 }, 

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
 	{ 0,            XF86XK_MonBrightnessDown,  spawn,          SHCMD("xbacklight -dec 5; kill -44 $(pidof dwmblocks)") },
 	{ 0,              XF86XK_MonBrightnessUp,  spawn,          SHCMD("xbacklight -inc 5; kill -44 $(pidof dwmblocks)") },
        { 0,                    XF86XK_AudioMute,  spawn,          SHCMD("pactl set-sink-mute 0 toggle; kill -44 $(pidof dwmblocks)") },
        { 0,              XF86XK_AudioLowerVolume, spawn,          SHCMD("pactl set-sink-mute 0 false ; pactl set-sink-volume 0 -1%; kill -44 $(pidof dwmblocks)") },
        { 0,              XF86XK_AudioRaiseVolume, spawn,          SHCMD("pactl set-sink-mute 0 false ; pactl set-sink-volume 0 +1%; kill -44 $(pidof dwmblocks)") },
 	{ ControlMask|ShiftMask,         XK_p,     spawn,          SHCMD("/home/aarnar/Programs/scripts/demoji.sh")},
        { 0,                            XK_Print,  spawn,          SHCMD("~/Programs/scripts/scrshot.sh") }, 
        { ShiftMask,                    XK_Print,  spawn,          SHCMD("~/Programs/scripts/snipshot.sh") }, 
        { MODKEY,                       XK_n,      spawn,          SHCMD("st -g =70x16 nmtui") }, 
        { MODKEY,                       XK_r,      spawn,          SHCMD("st -e ranger") }, 
        { MODKEY,                       XK_z,      spawn,          SHCMD("st -e ncmpcpp") }, 
        { MODKEY,                       XK_slash,  spawn,          SHCMD("st -g =90x28 -e tremc") }, 
 	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run -x 500 -y 70 -w 200") }, 
 	{ MODKEY,                       XK_period, spawn,          SHCMD("passmenu") }, 
	{ Mod4Mask,                     XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Return, spawn,          SHCMD("tabbed -c -r 2 st -w ''") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ Mod4Mask|ShiftMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ Mod4Mask|ShiftMask,           XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ Mod4Mask,                     XK_comma,  tagmon,         {.i = -1 } },
	{ Mod4Mask,                     XK_period, tagmon,         {.i = +1 } },
	{ Mod4Mask,                     XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Mod4Mask,                     XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Mod4Mask,                     XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Mod4Mask,                     XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ Mod4Mask,                     XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Mod4Mask,                     XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod4Mask,                     XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod4Mask,                     XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,    	Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

