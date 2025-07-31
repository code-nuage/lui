local term = require("lui.term")
local buffer = require("lui.buffer")

local graphics = {}

graphics.draw = function(text, x, y)
    buffer.register(buffer.back, text, x, y)
end

graphics.get_window_size = function()
    local w, h = term.get_size()
    if w and h then
        return w, h
    end
end

graphics.clear = function()
    buffer.clear(buffer.back)
    buffer.clear(buffer.front)
    term.clear()
end

return graphics