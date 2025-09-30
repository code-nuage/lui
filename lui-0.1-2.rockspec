package = "lui"
version = "0.1-2"

source = {
    url = "git+https://www.github.com/code-nuage/lui",
    tag = "0.1-2"
}

description = {
    summary = "A terminal rendering engine",
    homepage = "https://www.github.com/code-nuage/lui", 
    license = "MIT" 
}

dependencies = {
    "lua >= 5.1",
    "luaposix >= 36.3-1",
    "luabitop >= 1.0.2-3",
    "utf8 >= 1.3-0"
}

build = {
    type = "builtin",
    modules = {
        ["lui"] = "src/lui.lua",
        ["lui.term"] = "src/term.lua",
        ["lui.buffer"] = "src/buffer.lua",
        ["lui.luierr"] = "src/luierr.lua",
        ["lui.run"] = "src/run.lua",
        ["lui.graphics"] = "src/graphics.lua",
        ["lui.keyboard"] = "src/keyboard.lua"
    }
}