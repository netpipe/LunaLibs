#!/bin/bash
#testing still



#itarget=emscripten
#itarget=Linux64
#itarget=Linux32
#itarget=windows
#debug=true

if ( $debug )
then
	debugf=debug
	debugf=""
fi

codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libogg-1.1.4/libogg_static.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libvorbis-1.2.3/libvorbis_dynamic.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libvorbis-1.2.3/libvorbisfile_dynamic.cbp"
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libtheora-1.1.1/libtheora.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libtheoraplayer/libtheoraplayer_2008.cbp"
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./freetype-2.3.9/freetype.cbp"
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./net/enet-1.2.1/enet.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./zlib-1.2.3/zlib.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./libIrrOpenSteer_10-02-15/libIrrOpenSteer.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./net/irrNetLite22/irrNetLite.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./OIS/LinuxCB/OIS.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./irrlicht-1.8.4/source/Irrlicht/Irrlicht-gcc.cbp" 
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./assimp-3.3.1/Assimp.cbp"
codeblocks --build ./prefix="$prefix" -v --target=$itarget$debugf "./cAudio23/cAudio/cAudio.cbp"

