package = "lui"
version = "0.1-1"
source = {
  url = "git+https://github.com/code-nuage/lui.git",
  tag = "v0.1.1"
}
description = {
  summary = "Terminal User Interface for Lua",
  detailed = [[
    lui is a C module to easily interact with a terminal.
  ]],
  homepage = "https://github.com/code-nuage/lui",
  license = "MIT"
}
supported_platforms = {"linux", "macosx"}

build = {
  type = "builtin",
  modules = {
    lui = {
      sources = {
        "lui/lui.c",
        "lui/run.c",
        "lui/exit.c",
        "lui/graphics.c",
        "lui/colors.c",
        "lui/keyboard.c"
      },
      incdirs = { "." }
    }
  }
}
