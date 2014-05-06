QtWebKit plugins
----------------------------------------------------------------------------------------
Set of QtWebKit platform plugins for the latest QtWebKit 2.3 version.

**SpellCheck**  
QtWebKit plugin that provides support for spell checking using the 
[Hunspell](http://hunspell.sourceforge.net/) library.  

**Notifications**  
QtWebKit plugin that provides support for showing HTML5 Notifications through DBus
`org.freedesktop.Notifications`.  

Although this plugin was written for QupZilla web browser, it has no dependency on it and
can be used with every QtWebKit based application.  
  
**NOTE:** This plugin is only useful for other QtWebKit applications. It is already
included in QupZilla Web Browser.

Requirements
----------------------------------------------------------------------------------------

 * Qt 4.8 and higher or Qt 5.0 and higher
 * QtWebKit 2.3 or version from Qt 5
 * Hunspell library + dictionaries (any recent version will do fine)

Building
----------------------------------------------------------------------------------------

    $ qmake
    $ make && make install

Plugin will then be installed into `$QTDIR/plugins/webkit` directory. 

Settings
----------------------------------------------------------------------------------------
In order to provide spell checking, dictionaries needs to be found and loaded.  
This plugin is looking for possible directories by parsing `DICTIONARY` and `DICPATH` environment
variables. If those variables are not set, the plugin will look for dictionaries in
`/usr/share/hunspell/`.

Example:

    export DICTIONARY=en_US
    export DICPATH=/home/user/hunspell/
    
    Will try to load:
    /home/user/hunspell/en_US.dic
    /home/user/hunspell/en_US.aff
