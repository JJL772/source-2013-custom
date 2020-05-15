
pushd $(dirname $0) 

export LD_LIBRARY_PATH="$PWD/bin:$LD_LIBRARY_PATH"

if [ ! -z $GAME_DEBUGGER]; then
	"$GAME_DEBUGGER" ./hl2_linux -dev -windowed -w 1920 -h 1080 -game mod_hl2mp
else
	./hl2_linux -dev -windowed -w 1920 -h 1080 -game mod_hl2mp 
fi 


