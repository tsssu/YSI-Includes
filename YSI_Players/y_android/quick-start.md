# y_android

Detects when a player is using the illegal Android client:

```pawn
#include <YSI_Server\y_colors>
#include <YSI_Players\y_android>

public OnAndroidCheck(playerid, bool:success)
{
	if (success)
	{
		SendClientMessage(playerid, X11_WHITE, "The player is on mobile client!");
	}
}
```

Also provides `bool:IsAndroidPlayer(playerid);` and `bool:IsPCPlayer(playerid);`.  These functions will BOTH return `false` before the `OnAndroidCheck` callback has fired, so they are unreliable in places like `OnPlayerConnect`.  This is because of how the checks request data after the player has joined.
