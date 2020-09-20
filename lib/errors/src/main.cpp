#include <iostream>
#include "errors.h"
/*
 * go ish errors
 * return struct<bool,type T>
 *
 * TODO: Create functions that check error and runs a lambda ass error handler
 * or fails progam. NOTE: Mabye Raise?
 */

err::Error<int> ret_int() { return err::Error<int>{true, 1}; }

int main() {}
