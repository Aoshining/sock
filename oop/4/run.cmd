@echo off
mingw32-make 
(
	echo 20231111
	echo Let's go shopping!
) > input.txt
.\pdadd < input.txt
del input.txt
echo=
.\pdlist
echo=
.\pdlist 20231030 20231111
echo=
.\pdshow
echo=
.\pdremove 20231111
echo=
.\pdshow 20231111