"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Util {
    static test() {
    }
    static clear(ctx) {
        ctx.fillStyle = 'rgb(0,0,0)';
        ctx.fillRect(0, 0, ctx.canvas.clientWidth, ctx.canvas.clientHeight);
    }
}
exports.Util = Util;
//# sourceMappingURL=util.js.map