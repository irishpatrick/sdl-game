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
canvas.addEventListener('mousemove', (e) => {
    mouse.x = e.x;
    mouse.y = e.y;
    document.getElementById('mousepos').innerHTML = mouse.x + ',' + mouse.y;
});
canvas.addEventListener('mousedown', (e) => {
});
canvas.addEventListener('mouseup', (e) => {
});
function init() {
    util_1.Util.setClearColor(100, 100, 100);
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
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIi4uL25vZGVfbW9kdWxlcy9icm93c2VyLXBhY2svX3ByZWx1ZGUuanMiLCJhc3NldC50cyIsImluZGV4LnRzIiwidXRpbC50cyIsInZpZXdwb3J0LnRzIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBOzs7QUNBQTtJQU9JO1FBQ0ksSUFBSSxDQUFDLENBQUMsR0FBRyxDQUFDLENBQUM7UUFDWCxJQUFJLENBQUMsQ0FBQyxHQUFHLENBQUMsQ0FBQztRQUNYLElBQUksQ0FBQyxLQUFLLEdBQUcsS0FBSyxDQUFDO1FBQ25CLElBQUksQ0FBQyxLQUFLLEdBQUcsSUFBSSxDQUFDO0lBQ3RCLENBQUM7SUFFTyxRQUFRO1FBQ1osSUFBSSxDQUFDLEtBQUssR0FBRyxJQUFJLENBQUM7SUFDdEIsQ0FBQztJQUVNLFNBQVMsQ0FBQyxFQUFVO1FBQ3ZCLElBQUksQ0FBQyxLQUFLLEdBQUcsSUFBSSxLQUFLLEVBQUUsQ0FBQztRQUN6QixJQUFJLENBQUMsS0FBSyxDQUFDLE1BQU0sR0FBRyxJQUFJLENBQUMsUUFBUSxDQUFDO1FBQ2xDLElBQUksQ0FBQyxLQUFLLENBQUMsR0FBRyxHQUFHLEVBQUUsQ0FBQztJQUN4QixDQUFDO0lBRU0sT0FBTztRQUNWLE9BQU8sSUFBSSxDQUFDLEtBQUssQ0FBQztJQUN0QixDQUFDO0NBQ0o7QUFFTyxzQkFBSzs7OztBQzdCYixpQ0FBNEI7QUFDNUIseUNBQW9DO0FBRXBDLElBQUksUUFBUSxHQUFhLElBQUksbUJBQVEsRUFBRSxDQUFDO0FBQ3hDLElBQUksTUFBTSxHQUFRLFFBQVEsQ0FBQyxjQUFjLENBQUMsUUFBUSxDQUFDLENBQUM7QUFDcEQsSUFBSSxHQUFHLEdBQUcsTUFBTSxDQUFDLFVBQVUsQ0FBQyxJQUFJLENBQUMsQ0FBQztBQUNsQyxJQUFJLEdBQVcsRUFBRSxJQUFZLEVBQUUsS0FBYSxDQUFDO0FBQzdDLElBQUksS0FBSyxHQUFRLEVBQUMsQ0FBQyxFQUFFLENBQUMsRUFBRSxDQUFDLEVBQUUsQ0FBQyxFQUFDLENB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UUFDSSxJQUFJLENBQUMsQ0FBQyxHQUFHLENBQUMsQ0FBQztRQUNYLElBQUksQ0FBQyxDQUFDLEdBQUcsQ0FBQyxDQUFDO1FBQ1gsSUFBSSxDQUFDLEtBQUssR0FBRyxDQUFDLENBQUM7SUFDbkIsQ0FBQztDQUNKO0FBRU8sNEJBQVEiLCJmaWxlIjoiZ2VuZXJhdGVkLmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXNDb250ZW50IjpbIihmdW5jdGlvbigpe2Z1bmN0aW9uIHIoZSxuLHQpe2Z1bmN0aW9uIG8oaSxmKXtpZighbltpXSl7aWYoIWVbaV0pe3ZhciBjPVwiZnVuY3Rpb25cIj09dHlwZW9mIHJlcXVpcmUmJnJlcXVpcmU7aWYoIWYmJmMpcmV0dXJuIGMoaSwhMCk7aWYodSlyZXR1cm4gdShpLCEwKTt2YXIgYT1uZXcgRXJyb3IoXCJDYW5ub3QgZmluZCBtb2R1bGUgJ1wiK2krXCInXCIpO3Rocm93IGEuY29kZT1cIk1PRFVMRV9OT1RfRk9VTkRcIixhfXZhciBwPW5baV09e2V4cG9ydHM6e319O2VbaV1bMF0uY2FsbChwLmV4cG9ydHMsZnVuY3Rpb24ocil7dmFyIG49ZVtpXVsxXVtyXTtyZXR1cm4gbyhufHxyKX0scCxwLmV4cG9ydHMscixlLG4sdCl9cmV0dXJuIG5baV0uZXhwb3J0c31mb3IodmFyIHU9XCJmdW5jdGlvblwiPT10eXBlb2YgcmVxdWlyZSYmcmVxdWlyZSxpPTA7aTx0Lmxlbmd0aDtpKyspbyh0W2ldKTtyZXR1cm4gb31yZXR1cm4gcn0pKCkiLCJjbGFzcyBBc3NldCB7XHJcblxyXG4gICAgcHVibGljIHg6IG51bWJlcjtcclxuICAgIHB1YmxpYyB5OiBudW1iZXI7XHJcbiAgICBwcml2YXRlIGltYWdlOiBhbnk7XHJcbiAgICBwcml2YXRlIHJlYWR5OiBib29sZWFuO1xyXG5cclxuICAgIHB1YmxpYyBjb25zdHJ1Y3RvcigpIHtcclxuICAgICAgICB0aGlzLnggPSAwO1xyXG4gICAgICAgIHRoaXMueSA9IDA7XHJcbiAgICAgICAgdGhpcy5yZWFkeSA9IGZhbHNlO1xyXG4gICAgICAgIHRoaXMuaW1hZ2UgPSBudWxsO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgY2FsbGJhY2soKTogdm9pZCB7XHJcbiAgICAgICAgdGhpcy5yZWFkeSA9IHRydWU7XHJcbiAgICB9XHJcblxyXG4gICAgcHVibGljIGxvYWRJbWFnZShmbjogc3RyaW5nKTogdm9pZCB7XHJcbiAgICAgICAgdGhpcy5pbWFnZSA9IG5ldyBJbWFnZSgpO1xyXG4gICAgICAgIHRoaXMuaW1hZ2Uub25sb2FkID0gdGhpcy5jYWxsYmFjaztcclxuICAgICAgICB0aGlzLmltYWdlLnNyYyA9IGZuO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyBpc1JlYWR5KCk6IGJvb2xlYW4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLnJlYWR5O1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQge0Fzc2V0fTsiLCJpbXBvcnQge1V0aWx9IGZyb20gXCIuL3V0aWxcIjtcclxuaW1wb3J0IHtWaWV3cG9ydH0gZnJvbSBcIi4vdmlld3BvcnRcIjtcclxuXHJcbmxldCB2aWV3cG9ydDogVmlld3BvcnQgPSBuZXcgVmlld3BvcnQoKTtcclxubGV0IGNhbnZhczogYW55ID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoJ2NhbnZhcycpO1xyXG5sZXQgY3R4ID0gY2FudmFzLmdldENvbnRleHQoJzJkJyk7XHJcbmxldCBub3c6IG51bWJlciwgdGhlbjogbnVtYmVyLCBkZWx0YTogbnVtYmVyO1xyXG5sZXQgbW91c2U6IGFueSA9IHt4OiAwLCB5OiAwfTtcclxuXHJcbmNhbnZhcy5hZGRFdmVudExpc3RlbmVyKCdtb3VzZW1vdmUnLCAoZTogYW55KSA9PiB7XHJcbiAgICBtb3VzZS54ID0gZS54O1xyXG4gICAgbW91c2UueSA9IGUueTtcclxuICAgIGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCdtb3VzZXBvcycpLmlubmVySFRNTCA9IG1vdXNlLnggKyAnLCcgKyBtb3VzZS55O1xyXG59KTtcclxuXHJcbmNhbnZhcy5hZGRFdmVudExpc3RlbmVyKCdtb3VzZWRvd24nLCAoZTogYW55KSA9PiB7XHJcblxyXG59KTtcclxuXHJcbmNhbnZhcy5hZGRFdmVudExpc3RlbmVyKCdtb3VzZXVwJywgKGU6IGFueSkgPT4ge1xyXG5cclxufSk7XHJcblxyXG5mdW5jdGlvbiBpbml0KCkge1xyXG4gICAgVXRpbC5zZXRDbGVhckNvbG9yKDEwMCwxMDAsMTAwKTtcclxuXHJcbiAgICB0aGVuID0gRGF0ZS5ub3coKTtcclxufVxyXG5cclxuZnVuY3Rpb24gdXBkYXRlKCkge1xyXG4gICAgbm93ID0gRGF0ZS5ub3coKTtcclxuICAgIGRlbHRhID0gKG5vdyAtIHRoZW4pIC8gMTAwMC4wO1xyXG4gICAgdGhlbiA9IG5vdztcclxuXHJcblxyXG59XHJcblxyXG5mdW5jdGlvbiBkcmF3KCkge1xyXG4gICAgcmVxdWVzdEFuaW1hdGlvbkZyYW1lKGRyYXcpO1xyXG5cclxuICAgIFV0aWwuY2xlYXIoY3R4KTtcclxuICAgIHVwZGF0ZSgpO1xyXG59XHJcblxyXG5pbml0KCk7XHJcbmRyYXcoKTsiLCJpbXBvcnQge1ZpZXdwb3J0fSBmcm9tIFwiLi92aWV3cG9ydFwiO1xyXG5pbXBvcnQge0Fzc2V0fSBmcm9tIFwiLi9hc3NldFwiO1xyXG5cclxuY2xhc3MgVXRpbCB7XHJcblxyXG4gICAgcHJpdmF0ZSBzdGF0aWMgY2xlYXJDb2xvcjogbnVtYmVyW10gPSBbMCwgMCwgMF07XHJcblxyXG4gICAgcHVibGljIHN0YXRpYyBzZXRDbGVhckNvbG9yKHI6IG51bWJlciwgZzogbnVtYmVyLCBiOiBudW1iZXIpOiB2b2lkIHtcclxuICAgICAgICB0aGlzLmNsZWFyQ29sb3IgPSBbciwgZywgYl07XHJcbiAgICB9XHJcblxyXG4gICAgcHVibGljIHN0YXRpYyBjbGVhcihjdHg6IGFueSk6IHZvaWQge1xyXG4gICAgICAgIGN0eC5maWxsU3R5bGUgPSAncmdiKCcgKyBcclxuICAgICAgICAgICAgdGhpcy5jbGVhckNvbG9yWzBdICsgJywnICsgXHJcbiAgICAgICAgICAgIHRoaXMuY2xlYXJDb2xvclsxXSArICcsJyArIFxyXG4gICAgICAgICAgICB0aGlzLmNsZWFyQ29sb3JbMl0gKyAnKSc7XHJcbiAgICAgICAgY3R4LmZpbGxSZWN0KDAsIDAsIGN0eC5jYW52YXMuY2xpZW50V2lkdGgsIGN0eC5jYW52YXMuY2xpZW50SGVpZ2h0KTtcclxuICAgIH1cclxuXHJcbiAgICBwdWJsaWMgc3RhdGljIGRyYXcoY3R4OiBhbnksIGFzc2V0OiBBc3NldCwgdmlldz86IFZpZXdwb3J0KTogdm9pZCB7XHJcbiAgICAgICAgbGV0IHN4OiBudW1iZXIgPSAwO1xyXG4gICAgICAgIGxldCBzeTogbnVtYmVyID0gMDtcclxuICAgICAgICBpZiAodmlldykge1xyXG4gICAgICAgICAgICBzeCA9IChhc3NldC54ICsgdmlldy54KSAqIHZpZXcuc2NhbGU7XHJcbiAgICAgICAgICAgIHN5ID0gKGFzc2V0LnkgKyB2aWV3LnkpICogdmlldy5zY2FsZTtcclxuICAgICAgICB9XHJcblxyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyBzdGF0aWMgZHJhd0dyaWQoY3R4OiBhbnksIHZpZXc6IFZpZXdwb3J0KTogdm9pZCB7XHJcbiAgICAgICAgbGV0IHNwYWNpbmc6IG51bWJlciA9IDMyICogdmlldy5zY2FsZTtcclxuICAgIH1cclxuXHJcbn1cclxuXHJcbmV4cG9ydCB7VXRpbH07IiwiY2xhc3MgVmlld3BvcnQge1xyXG4gICAgcHVibGljIHg6IG51bWJlcjtcclxuICAgIHB1YmxpYyB5OiBudW1iZXI7XHJcbiAgICBwdWJsaWMgc2NhbGU6IG51bWJlcjtcclxuICAgIFxyXG4gICAgcHVibGljIGNvbnN0cnVjdG9yKCkge1xyXG4gICAgICAgIHRoaXMueCA9IDA7XHJcbiAgICAgICAgdGhpcy55ID0gMDtcclxuICAgICAgICB0aGlzLnNjYWxlID0gMTtcclxuICAgIH1cclxufVxyXG5cclxuZXhwb3J0IHtWaWV3cG9ydH07Il19
