local utf8 = require("utf8")

local term = require("lui.term")
local buffer = require("lui.buffer")

local graphics = {}

graphics.draw = function(text, x, y)
    local lines = {}
    local cy = 0
    for line in text:gmatch("([^\r\n]+)") do
        cy = cy + 1
        for cx = 1, utf8.len(line), 1 do
            local char = utf8.sub(line, cx, cx)
            buffer.register(buffer.back, char, cx + x - 1, cy + y - 1)
        end
    end
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