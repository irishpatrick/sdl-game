#!/usr/bin/python3

import sys
import os.path
import json

help_page = """
usage: <command> [args]
commands (genmap):
q(uit)
d(ir) <directory>
h(elp), ?
n(ew)
w(rite) <file>
o(pen) <file>
s(prite)
e(dit) <field> <name>
l(ist) [field]
"""

sprite_editor_help_page = """
commands (sprite-editor)
q(uit)
n(ew)
t(ype)
x
y
i(mage)
m(anual)
"""

def new_map():
    return {"entry": {}, "sprites": []}

def edit_sprite(sprite):
    running = True
    while running:
        command = input("(sprite-editor) ")

        # quit
        if command.startswith("q"):
            return

        elif command.startswith("h"):
            print(sprite_editor_help_page)

        # new
        elif command.startswith("n"):
            sprite["name"] = command.split(" ")[1]

        # type
        elif command.startswith("t"):
            sprite["type"] = command.split(" ")[1]

        # x
        elif command.startswith("x"):
            sprite["x"] = int(command.split(" ")[1])

        # y
        elif command.startswith("y"):
            sprite["y"] = int(command.split(" ")[1])

        # image
        elif command.startswith("i"):
            sprite["texture"] = command.split(" ")[1]

        # manual
        elif command.startswith("m"):
            fmt = command.split(" ")[1]
            args = command.split(" ")[2:]
            if fmt == "str":
                sprite[args[0]] = args[1]
            elif fmt == "int":
                sprite[args[0]] = int(args[1])
            elif fmt == "json":
                sprite[args[0]] = json.loads(" ".join(args[1:]))

def new_sprite(current):
    sprite = {"name": "", "type": "", "x": 0, "y": 0, "texture": ""}
    edit_sprite(sprite)
    current["sprites"].append(sprite)

def run():
    running = True
    current = None
    workingdir = os.getcwd()

    while running:
        command = input("(genmap) ")

        # quit
        if command.startswith("q"):
            return

        # dir
        elif command.startswith("d"):
            workingdir = os.path.abspath(command.split(" ")[1])
            print("working directory is now {}\n".format(workingdir))

        # help
        elif command.startswith("h") or command.startswith("?"):
            print(help_page)

        # new
        elif command.startswith("n"):
            current = new_map()

        # write
        elif command.startswith("w"):
            fn = os.path.join(*command.split(" ")[1].split("/"))
            fp = open(os.path.join(workingdir, fn), "w")
            fp.write(json.dumps(current, indent=4))
            fp.close()

        # open
        elif command.startswith("o"):
            fn = os.path.join(*command.split(" ")[1].split("/"))
            fp = open(os.path.join(workingdir, fn), "r")
            current = json.loads(fp.read())
            fp.close()

        # sprite
        elif command.startswith("s"):
            if not current == None:
                new_sprite(current)
            else:
                print("error: create new map first!")

        # edit
        elif command.startswith("e"):
            args = command.split(" ")[1:]
            field = args[0]
            name = arg
            found = None
            for item in current[field]:
                if item["name"] == name:
                    found = item
            if field == "sprites":
                edit_sprite(found)

        # list
        elif command.startswith("l"):
            args = command.split(" ")[1:]
            if len(args) == 0:
                print(json.dumps(current, indent=4))
            else:
                json.dumps(current[args[0]], indent=4)

        elif len(command) == 0:
            pass

        else:
            print("unknown command, type help to see list of commands\n")


if __name__ == "__main__":
    run()
