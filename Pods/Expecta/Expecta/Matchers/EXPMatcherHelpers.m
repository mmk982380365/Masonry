#import "EXPMatcherHelpers.h"

BOOL EXPIsValuePointer(NSValue *value) {
  return [value objCType][0] == @encode(void *)[0];
}

BOOL EXPIsNumberFloat(NSNumber *number) {
  return strncmp([number objCType], @encode(float), 1000) == 0;
}
