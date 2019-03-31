
meta:
	ADDON_NAME = np-luavg
	ADDON_DESCRIPTION = lua nanovg very opinionated sandbox
	ADDON_AUTHOR = Nicola Pisanti
	ADDON_TAGS = 
	ADDON_URL = http://github.com/npisanti/np-luavg

common:
	#ADDON_SOURCES_EXCLUDE += libs/ofxLua
	#ADDON_INCLUDES_EXCLUDE += libs/ofxLua
	
	
linux64:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
linux:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
msys2:
	ADDON_CFLAGS += -DLUA_USE_WINDOWS
	
vs:
	ADDON_CFLAGS += -DLUA_USE_WINDOWS

linuxarmv6l:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
linuxarmv7l:
	ADDON_PKG_CONFIG_LIBRARIES += luajit

android/armeabi:
	# not tested, probably works :)

android/armeabi-v7a:	
	# not tested, probably works :)

osx:
	ADDON_CFLAGS += -DLUA_USE_MACOSX

ios:


