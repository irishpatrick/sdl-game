class Util {

    static clear(ctx: any) {
        ctx.fillStyle = 'rgb(0,0,0)';
        ctx.fillRect(0, 0, ctx.canvas.clientWidth, ctx.canvas.clientHeight);
    }

}

export {Util};