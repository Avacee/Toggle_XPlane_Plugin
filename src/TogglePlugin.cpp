/*
	For more information on developing X-Plane plugins: https://developer.x-plane.com/article/developing-plugins/
	and https://developer.x-plane.com/sdk/plugin-sdk-documents/

	The lifecycle for a plugin is:
	XPluginStart
	XPluginEnable
	XPluginReceiveMessage
	FlightLoopCallBacks
	XPluginDisable
	XPluginStop
*/

#include <string.h>

#include "XPLMDefs.h"
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMUtilities.h"

float FlightLoopCallback(float inElapsedSinceLastCall, float inElapsedSinceLastFlightLoop, int inCounter, void* inRefCon);

XPLMCommandRef cmndref_ToggleSkyscapes = NULL;
XPLMCommandRef cmndref_ToggleCloudscapes = NULL;
XPLMPluginID idSkyscapes = XPLM_NO_PLUGIN_ID;
XPLMPluginID idCloudscapes = XPLM_NO_PLUGIN_ID;
int DoToggleSkyscapes(XPLMCommandRef commandRef, XPLMCommandPhase phase, void* refCon);
int DoToggleCloudscapes(XPLMCommandRef commandRef, XPLMCommandPhase phase, void* refCon);

/*
 *  XPluginStart() is called when the plugin is first loaded. Do any initialisation here.
 *	Maximum of 256 chars for outName, outSig, outDesc.
 *
 *	Return:
 *	1 for successful initialisation.
 *	0 for failed to initialise. X-Plane will unload the plugin and populate outDesc with a failure description if possible.
 */
PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc)
{
	strcpy(outName, "ToggleSkyscapes");
	strcpy(outSig, "com.Marci353.ToggleScapes");
	strcpy(outDesc, "Enable/Disable Skyscapes+Cloudscapes");

	// You probably want this on https://developer.x-plane.com/sdk/XPLMPlugin/#XPLMEnableFeature
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	//See https://developer.x-plane.com/sdk/XPLMProcessing/#XPLMRegisterFlightLoopCallback
	XPLMRegisterFlightLoopCallback(FlightLoopCallback, -1.0, NULL);

	cmndref_ToggleSkyscapes = XPLMCreateCommand("Marci353/ToggleSkyscapes", "Enable or Disable Enhanced Skyscapes.");
	XPLMRegisterCommandHandler(cmndref_ToggleSkyscapes, DoToggleSkyscapes, 1, NULL);

	cmndref_ToggleCloudscapes = XPLMCreateCommand("Marci353/ToggleCloudscapes", "Enable or Disable Enhanced Cloudscapes.");
	XPLMRegisterCommandHandler(cmndref_ToggleCloudscapes, DoToggleCloudscapes, 1, NULL);

	return 1;
}

/*
 * Called by X-Plane before the plugin is stopped and unloaded.
 * Unregister any callbacks, free any resources, close any files, unload any windows or widgets.
 * If the plugin was enabled XPluginDisable will be called first.
 */
PLUGIN_API void XPluginStop(void)
{
	XPLMUnregisterFlightLoopCallback(FlightLoopCallback, NULL);
	XPLMUnregisterCommandHandler(cmndref_ToggleCloudscapes, DoToggleCloudscapes, 1, NULL);
	XPLMUnregisterCommandHandler(cmndref_ToggleSkyscapes, DoToggleSkyscapes, 1, NULL);
}

/*
 * Until the plugin is enabled, it will not receive any callbacks and its UI will be hidden and/or disabled.
 * Do plugin-lifetime initialisation in XPluginStart() and enabled-lifetime initialisation here.
 *
 * Return:
 *	1 for success. 0 for fail.
 */
PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

/*
 * The XPluginDisable function is called by X-Plane right before the plugin is disabled.
 * When the plugin is disabled it will not receive any other callbacks and its UI will be hidden and/or disabled.
 * Free/disable any enabled-lifetime resources here
 */
PLUGIN_API void XPluginDisable(void)
{
}

/*
 * X-Plane calls this function whenever there's a message for the Plugin Manager to pass.
 * Messages may be raised by X-Plane (inFrom = 0) or a separate plugin.
 * Do not use one of the existing definitions for your messages.
 *
*/
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMessage, void* inParam)
{
	switch (inMessage)
	{
	case XPLM_MSG_AIRPLANE_COUNT_CHANGED: {break; }
	case XPLM_MSG_AIRPORT_LOADED: {break; }
	case XPLM_MSG_ENTERED_VR: {break; }
	case XPLM_MSG_EXITING_VR: {break; }
	case XPLM_MSG_LIVERY_LOADED: {break; }
	case XPLM_MSG_PLANE_CRASHED: {break; }
	case XPLM_MSG_PLANE_LOADED: {break; }
	case XPLM_MSG_PLANE_UNLOADED: {break; }
	case XPLM_MSG_RELEASE_PLANES: {break; }
	case XPLM_MSG_SCENERY_LOADED: {break; }
	case XPLM_MSG_WILL_WRITE_PREFS: {break; }
	}
}

/*
 * A Flightloop callback registered with XPLMRegisterFlightLoopCallback().
 * See https://developer.x-plane.com/sdk/XPLMFlightLoop_f/ for what to return.
*/

float FlightLoopCallback(float inElapsedSinceLastCall, float inElapsedSinceLastFlightLoop, int inCounter, void* inRefCon)
{
	return -1.0;
}

int DoToggleSkyscapes(XPLMCommandRef commandRef, XPLMCommandPhase phase, void* refCon)
{
	// Only run once when the command is begun - Will require another KeyPress to run again.
	if (phase != xplm_CommandBegin)
		return 1;

	if (idSkyscapes == XPLM_NO_PLUGIN_ID)
	{
		//TODO: Enter the signature for Enhanced Skyscapes below
		idSkyscapes = XPLMFindPluginBySignature("BiologicalNanobot.enhanced_skyscapes");
		//eg idSkyscapes = XPLMFindPluginBySignature("com.leecbaker.datareftool");
	}
	if (idSkyscapes != XPLM_NO_PLUGIN_ID)
	{
		if (XPLMIsPluginEnabled(idSkyscapes))
			XPLMDisablePlugin(idSkyscapes);
		else
			XPLMEnablePlugin(idSkyscapes);
	}
	return 1;
}

int DoToggleCloudscapes(XPLMCommandRef commandRef, XPLMCommandPhase phase, void* refCon)
{
	// Only run once when the command is begun - Will require another KeyPress to run again.
	if (phase != xplm_CommandBegin)
		return 1;

	if (idCloudscapes == XPLM_NO_PLUGIN_ID)
	{
		//TODO: Enter the signature for Enhanced Cloudscapes below
		idCloudscapes = XPLMFindPluginBySignature("FarukEroglu2048.enhanced_cloudscapes");
		//eg idCloudscapes = XPLMFindPluginBySignature("com.leecbaker.datareftool");
	}
	if (idCloudscapes != XPLM_NO_PLUGIN_ID)
	{
		if (XPLMIsPluginEnabled(idCloudscapes))
			XPLMDisablePlugin(idCloudscapes);
		else
			XPLMEnablePlugin(idCloudscapes);
	}
	return 1;
}
