# log2Obj

Simple bash script that consume a log file and filter out prefixed messages 
that contain an embedded .obj file. Also removing their prefixes too.

Also creates an empty mtl file because some apps need it.

## Usage

	./log2Obj.sh <from> <to>            # Default prefix: "objconsolog: "
	./log2Obj.sh <from> <to> <prefix>   # The prefix you provide

## Workings

- It greps lines to contain your "prefix" and keeps only those
- then removes everything until the prefix.

This is useful because it might be not your prefix that is in the log messages, 
but timestamps, varios data for an app server / framework or whatever.

The idea is that you just log with your favourite tool - let it be `cout`, 
`System.out.println`, `console.log` or a simle good old `printf` vertices
or lines or simple data for a .obj file - then run this script on it to 
"extract" the obj file and view it in blender.

This is really easy and helps debugging 3D/2D graphical apps without adding 
any kind of sophisticated code to them just to check where a point cloud is.
