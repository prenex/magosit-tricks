#!/bin/sh
# log2obj: Filter log messages containing *.obj data.
# 
# It greps lines to contain your "prefix" and keeps only those, then removes everyting until prefix.
# Also adds a simple mtl file as some 3D apps need it.
#
# Useful to create *.obj files from debug log messages containing *.obj for 3D debugging.
#
# Shared to you by: MagosIT Kft
#
# Rights open-shared as we use this for other projects and purposes, but might be added to your codebase.
# All we did is to change the "prefix" to comply with your case if necessary.
# 
#                                                         `:   .---------         
#                        ``-:`-        : .  `           ::o-.:-.        `--:.     
#                        -:/.::        +`+ /.`        -//:.:.               ./.   
#                        .+-//::      -///:::`       /-o:-.              .+++:-   
#                         :o+y:.`     -+/+/..      -/`                       .-:` 
#                         -: -o-       sss.--.  `o.m-                           /`
#                        ./   -o     :o+-:-:`   +-y.                             +
#                        +     ./ .:+/` -::-`  /` /              .-----.         +
#                       +------.:o-:-   .s-`   +                /.     `::      .:
#                   ----.`     `...------h.  ` /`              `/        o+-   `+ 
#                 ::`                   .o.  .h--              `/        ` +  -:  
#               ./`     ..-:..            +`  so:               -:         +.:`   
#              `/      :+/:/+/            `+  .+                 :-       :+.     
#              +      .dh`  +`             +   +                  +               
#             .:      ./+:--`              + .s:+                `.:              
#            .o`                           +  +`/.               /+:              
#         `::``/                          `/  `/                  -/              
#         o`   +                          +    :.                ://o             
#          ---/-      .--    .::          -:  `:o                 ./-`            
#   :----.    .------/:----os` .:          ----s.                 :::             
#  `/    `--:`            :/+ `-+--             .---.              +              
#  /`        -/``..` `--:+:-:-.                     .::            :.             
#  +          .o.`.:y/---`     ``.--`                 `/`           +             
#  +        .:ysshso/-:---:/++y.`+` `                   +         /-y             
#  ./  `--:o./ooo++``/`       o`  +` ./++++/-.          `/       -: `             
#  .o::/`-s:-+o   -/-       -/-+   o/-`      `           +       +                
# --.+/:./.   -//:`        -/  `/.::`                    +      /.                
# +`+   :--.-:+:+          +`    +.                      +    -:                  
#  -:------.    -          .+    +                       + ``/.                   
#                   `:::/:-:+:   /.                    `/-:h/`                    
#                  `so++/` `.-----/++/:-            `--/-.                        
#                   ://--/os///-     .---.    .-/+/-.`                            
#                      ``.+:/.````.-------------`                                 
#                          `.---..``                                              

# default prefix
PREFIX="objconsolog: "

if [ $# -lt 2 ]; then
	# --help (or bad number of parameters)
	# Print usage
	echo "Usage examples:"
	echo ""
	echo "$0 log.txt out.obj # prefix will be '$PREFIX'"
	echo "$0 log.txt out.obj 'my_prefix'"
else
	# Handle custom prefix
	if [ $# -gt 2 ]; then
		PREFIX="$3"
	fi

	# Get filename without extension
	infile="$1"
	outfilename="${2%.*}"

	# (Re-)creation mtl file
	echo "# Blender MTL File: 'None'" > $outfilename.mtl
	echo "# Material Count: 0" >> $outfilename.mtl

	# Fix log contents and create *.obj
	echo "mtllib $outfilename.mtl" > $outfilename.obj
	cat $infile | grep "$PREFIX" | sed "s/.*$PREFIX//" >> $outfilename.obj
fi
