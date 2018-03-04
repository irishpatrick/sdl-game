#!/usr/bin/python3

import sys
import os.path
import json

def new_map():
    return {"entry": {}, "sprites": []}

def edit_sprite(sprite):
    running = True
    while running:
        command = input("(genmap) (sprite editor) ")

        if command.startswith("q"):
            return

        elif command.startswith("n"):
            sprite["name"] = command.split(" ")[1]

        elif command.startswith("t"):
            sprite["type"] = command.split(" ")[1]

        elif command.startswith("x"):
            sprite["x"] = int(command.split(" ")[1])

        elif command.startswith("y"):
            sprite["y"] = int(command.split(" ")[1])

        elif command.startswith("i"):
            sprite["texture"] = command.split(" ")[1]

        elif command.startswith("f"):
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

def find_sprite(name):
    pass

def run():
    running = True
    current = None
    while running:
        command = input("(genmap) ")

        if command.startswith("q"):
            return

        elif command.startswith("h") or command.startswith("?"):
            fp = open("help.txt", "r")
            print(fp.read())
            fp.close()

        elif command.startswith("n"):
            current = new_map()

        elif command.startswith("w"):
            fn = os.path.join(*command.split(" ")[1].split("/"))
            fp = open(fn, "w")
            fp.write(json.dumps(current, indent=4))
            fp.close()

        elif command.startswith("o"):
            fn = os.path.join(*command.split(" ")[1].split("/"))
            fp = open(fn, "r")
            current = json.loads(fp.read())
            fp.close()

        elif command.startswith("s"):
            if not current == None:
                new_sprite(current)
            else:
                print("error: create new map first!")

        elif command.startswith("e"):
            pass

        elif command.startswith(""):
            pass

        else:
            print("unknown command, type help to see list of commands\n")


if __name__ == "__main__":
    run()
