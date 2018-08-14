<h1>GNDE: Gemini New Debian Experience</h1>

<h2>Description:</h2>
This procedure is for install LightDM and DWM on Planet Gemini computer (tested on wifi only model) for a new user experience, namely:
<ul>
  <li>auto login as gemini user;</li>
  <li>no task bar;</li>
  <li>by default, windows are managed in monocle mode, they are displayed on totality on the screen same as a mobile device;</li>
  <li>easy control with keyboard;</li>
  <li>Rofi application launcher;</li>
  <li>preconfigured shortkeys:<br />
    ALT + SHIFT + ENTER : Terminal with konsole<br />
    ALT + SHIFT + W : Chromium<br />
    ALT + SHIFT + M : PulseAudio Volume Control<br />
    ALT + SHIFT + C : Libre Office Calc<br />
    ALT + SHIFT + T : Libre Office Writer<br />
    ALT + SHIFT + L : Connman UI Setup<br />
    ALT + SHIFT + P : SMPlayer<br />
    ALT + SHIFT + F : PCManFM File Manager<br />
    ALT + SHIFT + I : LXImage<br />
    ALT + SHIFT + S : Screenshot<br />
    ALT + SHIFT + E : Kwrite<br />
    ALT + P : Rofi applications launcher</li>
</ul>

Here you can see the desktop, on top at left, you have 2 workspaces; at right the status bar with lan, battery, audio and time informations.
![desktop](https://raw.githubusercontent.com/yannclement/gnde/master/dwm_desktop.png)

Here you can see Chromium on worksape 2:
![chrome](https://raw.githubusercontent.com/yannclement/gnde/master/dwm_chrome.png)

Here it's the terminal Konsole with application launcher Rofi:
![terminal and rofi](https://raw.githubusercontent.com/yannclement/gnde/master/dwm_terminal_rofi.png)

In bonus:
<ul>
  <li>battery level works;</li>
  <li>wifi works;</li>
  <li>brightness keys works:<br />
  ALT + CTRL +  B : brightness -<br />
  ALT + CTRL +  N : brightness +</li>
  <li>audio volume keys works;<br />
  ALT + CTRL +  X : mute<br />
  ALT + CTRL +  C : volume -<br />
  ALT + CTRL +  V : volume +</li>
  <li>shortkeys to reboot and shutdown (imediately):<br />
  ALT + CTRL +  S : shutdown<br />
  ALT + CTRL +  R : reboot</li>
</ul>

For bad things:
Special functions (volume, brightness and other) with FN key not works but special characters works with no problem.

Various information:
All commands prefixed by a $ can be launched in user;
All commands prefixed by a # must be launched in root.

Sorry for my english, it's not my native language.


<h2>Reflash:</h2>
We start from a fresh install of Gemini Debian Linux.
If you have used the online partition tool (http://support.planetcom.co.uk/partitionTool.html), you can reflash your Debian OS without touch other OS with this method :
<pre>
$ cd FlashToolLinux/
$ ./flash_tool.sh
</pre>
Select scatter-loading-file.
Select Download tab.
Select download only.
Unset all lines and select only linux.
Plug USB.
Click on Download.
Turn off Gemini whith long press on ESC key.

Flashing processus will normaly start and you can unplug USB when download will be OK.


<h2>Prepare:</h2>
Connect to Wifi.

<pre>
# apt update
# apt upgrade
</pre>

If LibreOffice is broken:
<pre>
# cd /var/cache/apt/archives/
# dpkg -i --force-overwrite libreoffice*
# apt install -f
# apt upgrade

# dpkg-reconfigure locales
# dpkg-reconfigure tzdata

# apt install git
</pre>

Download there necessary file:
<pre>
$ cd ~
$ git clone https://github.com/yannclement.com/gnde.git
</pre>


<h2>Install LightDM:</h2>
First, remove SDDM:
<pre>
# apt remove --purge sddm*
</pre>

Now install LightDM:
<pre>
# apt install lightdm
</pre>

If Connman loose Wifi:
<pre>
# dpkg-reconfigure connman
</pre>


<h2>Install DWM:</h2>
<pre>
# apt install make gcc libx11-dev libxft-dev libxinerama-dev
$ git clone git://git.suckless.org/dwm
$ cp gnde/config.h dwm
$ cd dwm
</pre>

> Si vous êtes Français avec un clavier AZERTY, modifiez le fichier config.h tel qu'indiqué dans celui-ci pour bénéficier d'un fonctionnement correcte des touches 1 à 9.

Add autostart patch:
<pre>
$ wget https://dwm.suckless.org/patches/autostart/dwm-autostart-20161205-bb3bd6f.diff
$ patch -p1 < dwm-autostart-20161205-bb3bd6f.diff
</pre>

Compile DWM:
<pre>
# make clean install
</pre>


<h2>Configure all that:</h2>
<pre>
$ cd ~
$ mkdir .dwm
</pre>

Configure autostart:
<pre>
$ cp gnde/autostart_blocking.sh .dwm
$ chroot +x .dwm/autostart_blocking.sh
</pre>

Configure backlight:
<pre>
$ cp gnde/backlight.sh .dwm
$ chroot +x .dwm/backlight.sh
</pre>

Configure status:
<pre>
$ cp gnde/status.sh .dwm
$ chroot +x .dwm/status.sh
</pre>

Modify your Xsession for LightDM by creating a new .xsession file:
<pre>
$ nano .xsession
</pre>

And copy and paste these two lines of code:
<pre>
while true; do xsetroot -name "$(.dwm/status.sh)"; done &
exec /usr/local/bin/dwm
</pre>

Modify sudo to shutdown and reboot without password:
<pre>
# nano /etc/sudoers
</pre>

Add these two lines of code:
<pre>
# Allow user to shutdown with no password
gemini ALL=NOPASSWD: /sbin/shutdown
</pre>

Add some applications to complete:
<pre>
# apt install konsole
# apt install alsa-utils
# apt install rofi
# apt install fonts-symbola
# apt install feh
</pre>

Create a subdirectory wallpapers in ~/Pictures and copy there your favorite wallpapers:
<pre>
$ mkdir Pictures/wallpapers
$ cp gnde/moon.jpg Pictures/wallpapers
</pre>

Reboot


<h2>Testing:</h2>
In lightDM, select Default Xsession and log in.

Other things to know with DWM:
<ul>
  <li>ALT + SHIFT + K: close application</li>
  <li>ALT + SHIFT + SPACE: toggle floating / Monocle</li>
  <li>ALT + click and move mouse: move floating windows</li>
  <li>ALT + SHIFT + Q: quit DWM</li>
</ul>

For PCManFM File Manager et LXImage, if icons missing, select Breeze in Edit, Preferences.


<h2>Finishes:</h2>
If DWM work correctly, you can active auto login in LightDM:
<pre>
# nano /etc/lightdm/lightdm.conf
</pre>

Set autologin-user variable to gemini:
<pre>
autologin-user=gemini
</pre>

Set autologin-user-timeout variable to 0:
<pre>
autologin-user-timeout=0
</pre>


<h2>Facultatif:</h2>
If you want to remove LXDE:
<pre>
# apt remove --purge lxappearance lxde lxde-* lxinput lxmenu-data lxpanel lxpolkit lxrandr lxsession* lxsession lxshortcut lxtask lxterminal
</pre>
