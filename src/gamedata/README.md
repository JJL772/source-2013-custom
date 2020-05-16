## gamedata

Everything in this folder will be installed to the root of your Source SDK 2013 directory.

The idea here is to create master copies in your main repo, and copy them over to the SDK base dir when necessary. In general, your mod's mod directory (e.g. mod_hl2mp) will be under source control,
meaning that any work done in there will be saved. Work done in the SDK's root is not going to be under source control, so you will need to either copy over your FGDs a lot or risk losing your work by keeping them in there.

This gamedata/ directory just contains copies of everything you might want to install and installs it for you.

### entities

Everything in here is going to be an FGD. These will be copied to `Source SDK 2013/bin` directory for use in hammer

### scripts

These will be copied to the root of the SDK, e.g. `Source SDK 2013/` and can be used to launch tools, etc.
On linux, you'll need a launch script, so you can put it in there
