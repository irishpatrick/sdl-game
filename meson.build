project('sdl-game', 'cpp')
add_global_arguments(['-DBOOST_LOG_DYN_LINK', '-std=c++11', '-g', '-Wall', '-Og'], language: 'cpp')

sdl2 = dependency('sdl2')
sdl2_image = dependency('SDL2_image')
threads = dependency('threads')

inc = include_directories('include')

#engine
main = 'src/main.cc'
sprite = 'src/sprite.cc'
group = 'src/group.cc'
groupmanager = 'src/groupmanager.cc'
assets = 'src/assets.cc'
state = 'src/state.cc'
util = 'src/util.cc'
line = 'src/line.cc'
texture = 'src/texture.cc'
camera = 'src/camera.cc'
config = 'src/config.cc'
light = 'src/light.cc'

#game
game = 'src/game.cc'

executable(
    'a',
    main,
    sprite,
    group,
    groupmanager,
    assets,
    util,
    state,
    line,
    texture,
    camera,
    config,
    light,

    game,

    dependencies: [sdl2, sdl2_image, threads],
    include_directories: [inc])
