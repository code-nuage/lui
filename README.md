# lui
`lui` is a TUI library written in C with the Lua C API to write easily a TUI application with Lua.

## Modules
### lui
`lui` has natively a bunch of functions to interact with the library itself.

#### load
`load` hook function is useful to setup variables or to call `lui` functions before entering the `lui` loop
```lua
function lui.load()
    lui.graphics.clear()
end
```

#### update
`update` hook function is the main update function that trigger the update of every variables in the function
```lua
local i
function lui.update()
    i = i + 1
end
```

#### draw
`draw` hook function is the main draw function that stores the "to draw" characters in the screen buffer
```lua
function lui.draw()
    lui.graphics.draw(i, 1, 1)
end
```

#### exit
`exit` function helps you to close `lui` nicely and to restore terminal state as it was before using the application
```lua
lui.exit()
```

#### input
`input` is a variable that stores the current keyboard input, it shouldn't be rewrite but you can read it anytime

```lua
print(lui.input)
```

### graphics
`graphics` module helps you to interact with the screen

#### clear
`clear` function clear the screen
```lua
lui.graphics.clear()
```

#### draw
`draw` function write a character or a string at a x and y positions on the screen
```lua
lui.graphics.draw(text, x, y)
```

#### dimensions
`get_dimensions`, `get_width` and `get_height` functions get the global dimensions of the screen
```lua
local screen_width, screen_height = lui.graphics.get_dimensions()
local screen_width_2 = lui.graphics.get_width()
local screen_height_2 = lui.graphics.get_height()
```

### keyboard
`keyboard` module helps you to interact with the keyboard inputs

#### is_down
`is_down` function check if an input is down
```lua
if lui.keyboard.is_down("q") then
    lui.exit()
end
```