// Debugging macros for Arudino
// Todo: Move to devices/Arduino

#ifndef debug_h
#define debug_h

#ifdef DEBUG
#define MOD_DEBUG(...) Serial.print(__VA_ARGS__)
#else
#define MOD_DEBUG(...)
#endif

#ifdef DEBUG
#define MOD_DEBUG_LN(...); Serial.println(__VA_ARGS__)
#else
#define MOD_DEBUG_LN(...)
#endif

#endif

