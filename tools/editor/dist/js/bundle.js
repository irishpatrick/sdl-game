(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Asset {
    constructor() {
        this.x = 0;
        this.y = 0;
        this.ready = false;
        this.image = null;
    }
    callback() {
        this.ready = true;
    }
    loadImage(fn) {
        this.image = new Image();
        this.image.onload = this.callback;
        this.image.src = fn;
    }
    isReady() {
        return this.ready;
    }
}
exports.Asset = Asset;
},{}],2:[function(require,module,exports){
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const util_1 = require("./util");
const viewport_1 = require("./viewport");
let viewport = new viewport_1.Viewport();
let canvas = document.getElementById('canvas');
let ctx = canvas.getContext('2d');
let now, then, delta;
let mouse = { x: 0, y: 0 };
canvas.height = window.innerHeight;
window.addEventListener('resize', () => {
    canvas.height = window.innerHeight;
});
canvas.addEventListener('mousemove', (e) => {
    mouse.x = e.offsetX;
    mouse.y = e.offsetY;
    document.getElementById('mousepos').innerHTML = mouse.x + ',' + mouse.y;
});
canvas.addEventListener('mousedown', (e) => {
});
canvas.addEventListener('mouseup', (e) => {
});
function init() {
    util_1.Util.setClearColor(180, 180, 180);
    then = Date.now();
}
function update() {
    now = Date.now();
    delta = (now - then) / 1000.0;
    then = now;
}
function draw() {
    requestAnimationFrame(draw);
    util_1.Util.clear(ctx);
    update();
}
init();
draw();
},{"./util":3,"./viewport":4}],3:[function(require,module,exports){
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Util {
    static setClearColor(r, g, b) {
        this.clearColor = [r, g, b];
    }
    static clear(ctx) {
        ctx.fillStyle = 'rgb(' +
            this.clearColor[0] + ',' +
            this.clearColor[1] + ',' +
            this.clearColor[2] + ')';
        ctx.fillRect(0, 0, ctx.canvas.clientWidth, ctx.canvas.clientHeight);
    }
    static draw(ctx, asset, view) {
        let sx = 0;
        let sy = 0;
        if (view) {
            sx = (asset.x + view.x) * view.scale;
            sy = (asset.y + view.y) * view.scale;
        }
    }
    static drawGrid(ctx, view) {
        let spacing = 32 * view.scale;
    }
}
Util.clearColor = [0, 0, 0];
exports.Util = Util;
},{}],4:[function(require,module,exports){
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Viewport {
    constructor() {
        this.x = 0;
        this.y = 0;
        this.scale = 1;
    }
}
exports.Viewport = Viewport;
},{}]},{},[1,2,3,4])
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIi4uL25vZGVfbW9kdWxlcy9icm93c2VyLXBhY2svX3ByZWx1ZGUuanMiLCJhc3NldC50cyIsImluZGV4LnRzIiwidXRpbC50cyIsInZpZXdwb3J0LnRzIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBOzs7QUNBQTtJQU9JO1FBQ0ksSUFBSSxDQUFDLENBQUMsR0FBRyxDQUFDLENBQUM7UUFDWCxJQUFJLENBQUMsQ0FBQyxHQUFHLENBQUMsQ0FBQztRQUNYLElBQUksQ0FBQyxLQUFLLEdBQUcsS0FBSyxDQUFDO1FBQ25CLElBQUksQ0FBQyxLQUFLLEdBQUcsSUFBSSxDQUFDO0lBQ3RCLENBQUM7SUFFTyxRQUFRO1FBQ1osSUFBSSxDQUFDLEtBQUssR0FBRyxJQUFJLENBQUM7SUFDdEIsQ0FBQztJQUVNLFNBQVMsQ0FBQyxFQUFVO1FBQ3ZCLElBQUksQ0FBQyxLQUFLLEdBQUcsSUFBSSxLQUFLLEVBQUUsQ0FBQztRQUN6QixJQUFJLENBQUMsS0FBSyxDQUFDLE1BQU0sR0FBRyxJQUFJLENBQUMsUUFBUSxDQUFDO1FBQ2xDLElBQUksQ0FBQyxLQUFLLENBQUMsR0FBRyxHQUFHLEVBQUUsQ0FBQztJQUN4QixDQUFDO0lBRU0sT0FBTztRQUNWLE9BQU8sSUFBSSxDQUFDLEtBQUssQ0FBQztJQUN0QixDQUFDO0NBQ0o7QUFFTyxzQkFBSzs7OztBQzdCYixpQ0FBNEI7QUFDNUIseUNBQW9DO0FBRXBDLElBQUksUUFBUSxHQUFhLElBQUksbUJBQVEsRUFBRSxDQUFDO0FBQ3hDLElBQUksTUFBTSxHQUFRLFFBQVEsQ0FBQyxjQUFjLENBQUMsUUFBUSxDQUFDLENBQUM7QUFDcEQsSUFBSSxHQUFHLEdBQUcsTUFBTSxDQUFDLFVBQVUsQ0FBQyxJQUFJLENBQUMsQ0FBQztBQUNsQyxJQUFJLEdBQVcsRUFBRSxJQUFZLEVBQUUsS0FBYSxDQUFDO0FBQzdDLElBQUksS0FBSyxHQUFRLEVBQUMsQ0FBQyxFQUFFLENBQUMsRUFBRSxDQUFDLEVBQUUsQ0FBQyxFQUFDLENB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LEdBQVEsRUFBRSxJQUFjO1FBQzNDLElBQUksT0FBTyxHQUFXLEVBQUUsR0FBRyxJQUFJLENBQUMsS0FBSyxDQUFDO0lBQzFDLENBQUM7O0FBMUJjLGVBQVUsR0FBYSxDQUFDLENBQUMsRUFBRSxDQUFDLEVBQUUsQ0FBQyxDQUFDLENBQUM7QUE4QjVDLG9CQUFJOzs7O0FDbkNaO0lBS0k7UUFDSSxJQUFJLENBQUMsQ0FBQyxHQUFHLENBQUMsQ0FBQztRQUNYLElBQUksQ0FBQyxDQUFDLEdBQUcsQ0FBQyxDQUFDO1FBQ1gsSUFBSSxDQUFDLEtBQUssR0FBRyxDQUFDLENBQUM7SUFDbkIsQ0FBQztDQUNKO0FBRU8sNEJBQVEiLCJmaWxlIjoiZ2VuZXJhdGVkLmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXNDb250ZW50IjpbIihmdW5jdGlvbigpe2Z1bmN0aW9uIHIoZSxuLHQpe2Z1bmN0aW9uIG8oaSxmKXtpZighbltpXSl7aWYoIWVbaV0pe3ZhciBjPVwiZnVuY3Rpb25cIj09dHlwZW9mIHJlcXVpcmUmJnJlcXVpcmU7aWYoIWYmJmMpcmV0dXJuIGMoaSwhMCk7aWYodSlyZXR1cm4gdShpLCEwKTt2YXIgYT1uZXcgRXJyb3IoXCJDYW5ub3QgZmluZCBtb2R1bGUgJ1wiK2krXCInXCIpO3Rocm93IGEuY29kZT1cIk1PRFVMRV9OT1RfRk9VTkRcIixhfXZhciBwPW5baV09e2V4cG9ydHM6e319O2VbaV1bMF0uY2FsbChwLmV4cG9ydHMsZnVuY3Rpb24ocil7dmFyIG49ZVtpXVsxXVtyXTtyZXR1cm4gbyhufHxyKX0scCxwLmV4cG9ydHMscixlLG4sdCl9cmV0dXJuIG5baV0uZXhwb3J0c31mb3IodmFyIHU9XCJmdW5jdGlvblwiPT10eXBlb2YgcmVxdWlyZSYmcmVxdWlyZSxpPTA7aTx0Lmxlbmd0aDtpKyspbyh0W2ldKTtyZXR1cm4gb31yZXR1cm4gcn0pKCkiLCJjbGFzcyBBc3NldCB7XHJcblxyXG4gICAgcHVibGljIHg6IG51bWJlcjtcclxuICAgIHB1YmxpYyB5OiBudW1iZXI7XHJcbiAgICBwcml2YXRlIGltYWdlOiBhbnk7XHJcbiAgICBwcml2YXRlIHJlYWR5OiBib29sZWFuO1xyXG5cclxuICAgIHB1YmxpYyBjb25zdHJ1Y3RvcigpIHtcclxuICAgICAgICB0aGlzLnggPSAwO1xyXG4gICAgICAgIHRoaXMueSA9IDA7XHJcbiAgICAgICAgdGhpcy5yZWFkeSA9IGZhbHNlO1xyXG4gICAgICAgIHRoaXMuaW1hZ2UgPSBudWxsO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgY2FsbGJhY2soKTogdm9pZCB7XHJcbiAgICAgICAgdGhpcy5yZWFkeSA9IHRydWU7XHJcbiAgICB9XHJcblxyXG4gICAgcHVibGljIGxvYWRJbWFnZShmbjogc3RyaW5nKTogdm9pZCB7XHJcbiAgICAgICAgdGhpcy5pbWFnZSA9IG5ldyBJbWFnZSgpO1xyXG4gICAgICAgIHRoaXMuaW1hZ2Uub25sb2FkID0gdGhpcy5jYWxsYmFjaztcclxuICAgICAgICB0aGlzLmltYWdlLnNyYyA9IGZuO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyBpc1JlYWR5KCk6IGJvb2xlYW4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLnJlYWR5O1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQge0Fzc2V0fTsiLCJpbXBvcnQge1V0aWx9IGZyb20gXCIuL3V0aWxcIjtcclxuaW1wb3J0IHtWaWV3cG9ydH0gZnJvbSBcIi4vdmlld3BvcnRcIjtcclxuXHJcbmxldCB2aWV3cG9ydDogVmlld3BvcnQgPSBuZXcgVmlld3BvcnQoKTtcclxubGV0IGNhbnZhczogYW55ID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoJ2NhbnZhcycpO1xyXG5sZXQgY3R4ID0gY2FudmFzLmdldENvbnRleHQoJzJkJyk7XHJcbmxldCBub3c6IG51bWJlciwgdGhlbjogbnVtYmVyLCBkZWx0YTogbnVtYmVyO1xyXG5sZXQgbW91c2U6IGFueSA9IHt4OiAwLCB5OiAwfTtcclxuXHJcbmNhbnZhcy5oZWlnaHQgPSB3aW5kb3cuaW5uZXJIZWlnaHQ7XHJcblxyXG53aW5kb3cuYWRkRXZlbnRMaXN0ZW5lcigncmVzaXplJywgKCkgPT4ge1xyXG4gICAgY2FudmFzLmhlaWdodCA9IHdpbmRvdy5pbm5lckhlaWdodDtcclxufSk7XHJcblxyXG5jYW52YXMuYWRkRXZlbnRMaXN0ZW5lcignbW91c2Vtb3ZlJywgKGU6IGFueSkgPT4ge1xyXG4gICAgbW91c2UueCA9IGUub2Zmc2V0WDtcclxuICAgIG1vdXNlLnkgPSBlLm9mZnNldFk7XHJcbiAgICBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgnbW91c2Vwb3MnKS5pbm5lckhUTUwgPSBtb3VzZS54ICsgJywnICsgbW91c2UueTtcclxufSk7XHJcblxyXG5jYW52YXMuYWRkRXZlbnRMaXN0ZW5lcignbW91c2Vkb3duJywgKGU6IGFueSkgPT4ge1xyXG5cclxufSk7XHJcblxyXG5jYW52YXMuYWRkRXZlbnRMaXN0ZW5lcignbW91c2V1cCcsIChlOiBhbnkpID0+IHtcclxuXHJcbn0pO1xyXG5cclxuZnVuY3Rpb24gaW5pdCgpIHtcclxuICAgIFV0aWwuc2V0Q2xlYXJDb2xvcigxODAsMTgwLDE4MCk7XHJcblxyXG4gICAgdGhlbiA9IERhdGUubm93KCk7XHJcbn1cclxuXHJcbmZ1bmN0aW9uIHVwZGF0ZSgpIHtcclxuICAgIG5vdyA9IERhdGUubm93KCk7XHJcbiAgICBkZWx0YSA9IChub3cgLSB0aGVuKSAvIDEwMDAuMDtcclxuICAgIHRoZW4gPSBub3c7XHJcblxyXG5cclxufVxyXG5cclxuZnVuY3Rpb24gZHJhdygpIHtcclxuICAgIHJlcXVlc3RBbmltYXRpb25GcmFtZShkcmF3KTtcclxuXHJcbiAgICBVdGlsLmNsZWFyKGN0eCk7XHJcbiAgICB1cGRhdGUoKTtcclxufVxyXG5cclxuaW5pdCgpO1xyXG5kcmF3KCk7IiwiaW1wb3J0IHtWaWV3cG9ydH0gZnJvbSBcIi4vdmlld3BvcnRcIjtcclxuaW1wb3J0IHtBc3NldH0gZnJvbSBcIi4vYXNzZXRcIjtcclxuXHJcbmNsYXNzIFV0aWwge1xyXG5cclxuICAgIHByaXZhdGUgc3RhdGljIGNsZWFyQ29sb3I6IG51bWJlcltdID0gWzAsIDAsIDBdO1xyXG5cclxuICAgIHB1YmxpYyBzdGF0aWMgc2V0Q2xlYXJDb2xvcihyOiBudW1iZXIsIGc6IG51bWJlciwgYjogbnVtYmVyKTogdm9pZCB7XHJcbiAgICAgICAgdGhpcy5jbGVhckNvbG9yID0gW3IsIGcsIGJdO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyBzdGF0aWMgY2xlYXIoY3R4OiBhbnkpOiB2b2lkIHtcclxuICAgICAgICBjdHguZmlsbFN0eWxlID0gJ3JnYignICsgXHJcbiAgICAgICAgICAgIHRoaXMuY2xlYXJDb2xvclswXSArICcsJyArIFxyXG4gICAgICAgICAgICB0aGlzLmNsZWFyQ29sb3JbMV0gKyAnLCcgKyBcclxuICAgICAgICAgICAgdGhpcy5jbGVhckNvbG9yWzJdICsgJyknO1xyXG4gICAgICAgIGN0eC5maWxsUmVjdCgwLCAwLCBjdHguY2FudmFzLmNsaWVudFdpZHRoLCBjdHguY2FudmFzLmNsaWVudEhlaWdodCk7XHJcbiAgICB9XHJcblxyXG4gICAgcHVibGljIHN0YXRpYyBkcmF3KGN0eDogYW55LCBhc3NldDogQXNzZXQsIHZpZXc/OiBWaWV3cG9ydCk6IHZvaWQge1xyXG4gICAgICAgIGxldCBzeDogbnVtYmVyID0gMDtcclxuICAgICAgICBsZXQgc3k6IG51bWJlciA9IDA7XHJcbiAgICAgICAgaWYgKHZpZXcpIHtcclxuICAgICAgICAgICAgc3ggPSAoYXNzZXQueCArIHZpZXcueCkgKiB2aWV3LnNjYWxlO1xyXG4gICAgICAgICAgICBzeSA9IChhc3NldC55ICsgdmlldy55KSAqIHZpZXcuc2NhbGU7XHJcbiAgICAgICAgfVxyXG5cclxuICAgIH1cclxuXHJcbiAgICBwdWJsaWMgc3RhdGljIGRyYXdHcmlkKGN0eDogYW55LCB2aWV3OiBWaWV3cG9ydCk6IHZvaWQge1xyXG4gICAgICAgIGxldCBzcGFjaW5nOiBudW1iZXIgPSAzMiAqIHZpZXcuc2NhbGU7XHJcbiAgICB9XHJcblxyXG59XHJcblxyXG5leHBvcnQge1V0aWx9OyIsImNsYXNzIFZpZXdwb3J0IHtcclxuICAgIHB1YmxpYyB4OiBudW1iZXI7XHJcbiAgICBwdWJsaWMgeTogbnVtYmVyO1xyXG4gICAgcHVibGljIHNjYWxlOiBudW1iZXI7XHJcbiAgICBcclxuICAgIHB1YmxpYyBjb25zdHJ1Y3RvcigpIHtcclxuICAgICAgICB0aGlzLnggPSAwO1xyXG4gICAgICAgIHRoaXMueSA9IDA7XHJcbiAgICAgICAgdGhpcy5zY2FsZSA9IDE7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCB7Vmlld3BvcnR9OyJdfQ==
