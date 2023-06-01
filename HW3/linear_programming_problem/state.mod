var A, >= 0, <= 1;
var B, >= 0, <= 1;
var C, >= 0, <= 1;
var D, >= 0, <= 1;

minimize value: A + B + C + D;
subject to
final: A + B + C + D = 1;
aa: A = 0.25 * A + 0.25 * B;
bb: B = 0.75 * A + 0.5 * D;
cc: C = 0.75 * B + 0.25 * C + 0.5 * D;
dd: D = 0.75 * C;
end;
