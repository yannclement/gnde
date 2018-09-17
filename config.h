/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=7", "symbola:size=7" };
static const char dmenufont[]       = "monospace:size=7";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
  { NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },     /* first entry is default */
	{ "[]=",      tile },    /* no layout function means floating behavior */
	{ "><>",      NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define FUNCKEY Mod5Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "/usr/bin/konsole", NULL };
static const char *pulseup[] = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *pulsedown[] = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *mute[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *brightup[] = { ".dwm/backlight.sh", "up", NULL };
static const char *brightdown[] = { ".dwm/backlight.sh", "down", NULL };
static const char *shutdown[] = { "sudo", "shutdown", "-h", "now", NULL };
static const char *reboot[] = { "sudo", "shutdown", "-r", "now", NULL };
static const char *www[] = { "/usr/bin/chromium", NULL };
static const char *mixer[] = { "/usr/bin/pavucontrol-qt", NULL };
static const char *calc[] = { "/usr/bin/gnumeric", NULL };
static const char *writer[] = { "/usr/bin/abiword", NULL };
static const char *image[] = { "/usr/bin/lximage-qt", NULL };
static const char *screenshot[] = { "/usr/bin/lximage-qt", "--screenshot", NULL };
static const char *file[] = { "/usr/bin/pcmanfm-qt", NULL };
static const char *player[] = { "/usr/bin/smplayer", NULL };
static const char *wifi[] = { "/usr/bin/cmst", NULL };
static const char *edit[] = { "/usr/bin/kwrite", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },


        TAGKEYS(                      XK_1,                      0)
        TAGKEYS(                      XK_2,                      1)
        TAGKEYS(                      XK_3,                      2)
        TAGKEYS(                      XK_4,                      3)
        TAGKEYS(                      XK_5,                      4)
        TAGKEYS(                      XK_6,                      5)
        TAGKEYS(                      XK_7,                      6)
        TAGKEYS(                      XK_8,                      7)
        TAGKEYS(                      XK_9,                      8)


/* Pour les Français, remplacez les lignes de codes précédentes par celles-ci pour avoir un fonctionnement correcte des touches 1 à 9
	TAGKEYS(                        0x26,                      0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0xf5,                      7)
	TAGKEYS(                        0xe7,                      8)
*/


  { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  { FUNCKEY,                      XK_v,      spawn,          {.v = pulseup } },
  { FUNCKEY,                      XK_c,      spawn,          {.v = pulsedown } },
  { MODKEY|ControlMask,           XK_m,      spawn,          {.v = mute } },
  { FUNCKEY,                      XK_b,      spawn,          {.v = brightdown } },
  { FUNCKEY,                      XK_n,      spawn,          {.v = brightup } },
  { FUNCKEY,                      XK_Escape, spawn,          {.v = shutdown } },
  { MODKEY|ControlMask,           XK_r,      spawn,          {.v = reboot } },
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = www } },
  { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mixer } },
  { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = calc } },
  { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = writer } },
  { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshot } },
  { MODKEY|ShiftMask,             XK_i,      spawn,          {.v = image } },
  { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = file } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = player } },
  { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = wifi } },
  { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = edit } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask          button          function        argument */
	{ ClkLtSymbol,          0,                  Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                  Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                  Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                  Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,             Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ControlMask, Button1,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,   Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                  Button1,        view,           {0} },
	{ ClkTagBar,            0,                  Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,             Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,             Button3,        toggletag,      {0} },
};
