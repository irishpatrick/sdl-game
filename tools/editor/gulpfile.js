var gulp = require("gulp");
var browserify = require("browserify");
var source = require('vinyl-source-stream');
var watchify = require("watchify");
var tsify = require("tsify");
var gutil = require("gulp-util");

var watchedBrowserify = watchify(browserify({
    basedir: './src',
    debug: true,
    entries: ['asset.ts', 'index.ts', 'util.ts', 'viewport.ts'],
    cache: {},
    packageCache: {}
}).plugin(tsify, {
    target: 'es6',
    noImplicitAny: true,
    module: 'commonjs',
    sourceMap: true
}));

function bundle() {
    return watchedBrowserify
        .bundle()
        .pipe(source('bundle.js'))
        .pipe(gulp.dest('dist/js'));
}

gulp.task("default", bundle);
watchedBrowserify.on("update", bundle);
watchedBrowserify.on("log", gutil.log);